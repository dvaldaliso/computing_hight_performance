// --------------------------------------------------------------
// 
// --------------------------------------------------------------

package gestorDeTrabajos

// --------------------------------------------------------------
// imports
// --------------------------------------------------------------
import (
  //"fmt"

  "log" 
  //"log/ioutil" //log.SetOutput( ioutil.Discard )  log.SetFlags( 0 )

  "os"
  "os/signal"
  "syscall"

  "math/rand"
  "time"
  "strconv"
  "encoding/json"

  kafka "github.com/confluentinc/confluent-kafka-go/kafka"

  "context"

)

// --------------------------------------------------------------
//
// nivel: N, msg: Texto, resto: Objet --> f()
//
// Helper to log.
// --------------------------------------------------------------
func JordiLog( nivel int32, msg string, resto ...any ) {

  const DEBUG_LEVEL = 1

  if  nivel <= DEBUG_LEVEL {
    log.Printf( msg, resto... )
  }

} // ()

// --------------------------------------------------------------
// struct defining a Job as a client sends to us
// --------------------------------------------------------------
type Trabajo struct {
  IdExterno       string
  NombreFuncion   string
  Parametros      string    // to be interpreted by Function
} // type

// --------------------------------------------------------------
// struct defining a Job as a we store here
// --------------------------------------------------------------
type Encargo struct {
  IdEncargo     string
  ElTrabajo     Trabajo
  Timestamp     time.Time
} // type

// --------------------------------------------------------------
// struct defining a message got from Kafka
// --------------------------------------------------------------
type MensajeRecibido struct {
  Tema        string
  Clave       string
  Valor       string
  Particion   int32
  Offset      int64
  Cabecera0   string
  Timestamp   time.Time
} // type

// --------------------------------------------------------------
// Configuracion
// --------------------------------------------------------------
type Configuracion struct {
  RedisURL                string
  KafkaURLs               []string
  ReadTimeout             int
  NumParticionesTrabajos  int
  EsWorker                bool // true => puede pedir trabajos y enviar respuestas
  EsCliente               bool // true => puede enviar trabajos y pedir respuestas
}

// --------------------------------------------------------------
// --------------------------------------------------------------
func ConfiguracionDesdeTextoJson( texto string ) Configuracion {
  // valores por defecto
  var config = Configuracion{
    RedisURL:         "localhost:6379",
    KafkaURLs:        []string{ "localhost:9091", "localhost:9092", "localhost:9093" },
    ReadTimeout:            20,
    NumParticionesTrabajos: 3,
    EsWorker: true,
    EsCliente: true,
  }

  /*
  if texto == nil {
    return config
  }
  */

  // volcamos el texto recibido a config
  // de esta manera, las propiedades
  // no recibidas, tendrán un valor por defecto
  PasarTextoJsonAStruct( texto, & config ) 

  // comprobaciones 
  /*
  err := PasarTextoJsonAStruct( texto, & config ) 
  if err != nil {
    log.Println( " +++++++++++++++++++ " )
    log.Println( err )
  log.Printf( ">%s<\n", texto )
  }

  log.Println( " +++++++++++++++++++ " )
  log.Println( " ANTES " )
  log.Println( texto )
  log.Println( " +++++++++++++++++++ " )
  log.Println( " DESPUES " )
  log.Println( config )
  log.Println( " +++++++++++++++++++ " )
  */

  return config
}

// --------------------------------------------------------------
// constans for groups and topics we use in Kafka
// --------------------------------------------------------------
const GRUPO_WORKERS             = "GRUPO_WORKERS"

const GRUPO_RESPUESTAS          = "GRUPO_RESPUESTAS"

const GRUPO_OBSERVADOR_RESPUESTAS        = "GRUPO_OBSERVADOR_RESPUESTAS"
const GRUPO_OBSERVADOR_ENCARGOS          = "GRUPO_OBSERVADOR_ENCARGOS"

const TEMA_TRABAJOS_ENCARGOS    = "TRABAJOS-ENCARGOS"

const TEMA_TRABAJOS_RESPUESTAS  = "TRABAJOS-RESPUESTAS"

// --------------------------------------------------------------
// --------------------------------------------------------------

// --------------------------------------------------------------
// private
//
// helper to create a Kafka Consumer
//
// servidorKafka: Texto 
// grupoConsumidor: Texto 
/// tema: Texto
//      -->
//          f()
//      <--
// Consumer
//
// --------------------------------------------------------------
func nuevoConsumidor( servidores []string, grupo string, tema string ) (* kafka.Consumer) {

  const nivelLog = 2

  JordiLog( nivelLog, " ------------------------------- " )
  JordiLog( nivelLog, " GestorDeTrabajos.nuevoConsumidor: servidor %s  %s tema %s \n", servidores[0], grupo, tema )

  //
  // aquí se crea el consumidor
  // loos tres primeros parmetros son obligatorios
  //
  consumidor, err := kafka.NewConsumer( & kafka.ConfigMap { 
    "bootstrap.servers":  servidores[0],
    "group.id":           grupo, 
    "auto.offset.reset": "earliest", // consumir desde el principio, alternativa: latest

    // nuevo en pruebas:
  })

  JordiLog( nivelLog, " NewConsumer hecho ------------- " )

  if err != nil {
    log.Printf( " oooooooooooooooooooooooooooooooooooo " )
    log.Printf( " hubo un error en NewConsumer: grupo %s tema %s \n",
    grupo, tema )
    log.Println( err )
    return nil
  }

  JordiLog( nivelLog, " ahora subscribeTopics --------- " )

  err = consumidor.SubscribeTopics( []string{ tema }, nil )

  if err != nil {
    log.Printf( " oooooooooooooooooooooooooooooooooooo " )
    log.Printf( " hubo un error en SubscribeTopics: grupo %s tema %s \n",
    grupo, tema )
    log.Println( err )
    return nil
  }

  JordiLog( nivelLog, " suscrito a %s FIN -------------\n", tema )

  return consumidor

} // ()

// --------------------------------------------------------------
// private
// --------------------------------------------------------------
func crearAdministrador( escritor * kafka.Producer) (*kafka.AdminClient, error) {
  client, err := kafka.NewAdminClientFromProducer( escritor )

  return client, err
} // ()

// --------------------------------------------------------------
// private
// --------------------------------------------------------------
func crearTopic( escritor  * kafka.Producer, tema string, particiones int ) error {

  const nivelLog = 2

  JordiLog( nivelLog, " =============================" )
  JordiLog( nivelLog, " creando TOPIC %s con %d particiones", tema, particiones )

  administrador, err := crearAdministrador( escritor )

  if err != nil {
    JordiLog( nivelLog, " no he podido crear Administrador " )
    return err
  }

  defer administrador.Close()

  topicSpec := kafka.TopicSpecification { 
    Topic: tema,
    NumPartitions: particiones,
  }

  JordiLog( nivelLog, " ***************************** "  )
  JordiLog( nivelLog, PasarStructATextoJson ( topicSpec ) )
  JordiLog( nivelLog, " ***************************** "  )

  resultado, err1 := administrador.CreateTopics( context.Background(), []kafka.TopicSpecification{ topicSpec } , kafka.SetAdminValidateOnly( false ))

  if err1 != nil {
    JordiLog( nivelLog, " no he podido crear topic %s", err1 );
    return err1
  }

  for _, res := range resultado {
    JordiLog( nivelLog, " topic -> %s", res )
  } // for

  JordiLog( nivelLog, " topic creado ")
  JordiLog( nivelLog, " =============================" )

  //return  errors.New( "no pude crear topic" )
  return nil
} // ()

// --------------------------------------------------------------
// private
//
// Helper to send a message to Kafka
// 
// escritor: Producer, topic: Texto, 
// clave: Texto, valor: texto
//  --> f()
// 
// --------------------------------------------------------------
func enviarMensajeA( 
  escritor  * kafka.Producer, 
  topic     string,
  clave     string, 
  valor string,
) {

  JordiLog( 2, " ====================== " )
  JordiLog( 2, "GesgorDeTrabajos.EnviarMensaje : empiezo" )
  JordiLog( 2, " voy a enviar topic>%s<, clave>%s<, valor>%s< \n", topic, clave, valor )

  //
  // creo mensaje
  //
  elMensaje := kafka.Message {
    TopicPartition: kafka.TopicPartition{Topic: &topic, Partition: kafka.PartitionAny},
    Value:          []byte(valor),
    Key:            []byte( clave ),
    Headers:        []kafka.Header{ kafka.Header{ Key: clave, 
    Value: []byte("no-se-que-poner") } },
  }

  JordiLog( 2, " mensaje que envío: " )
  JordiLog( 2, "%s\n", PasarStructATextoJson( elMensaje ) )

  //
  // envío mensaje 
  //
  escritor.Produce( & elMensaje, nil )

  escritor.Flush( 0.5 * 1000 ) // AQUI: revisar este timeout
  //escritor.Flush( 4000 ) // AQUI: revisar este timeout

  JordiLog( 2, "GesgorDeTrabajos.EnviarMensaje: termino tras hacer Flush() " )

  JordiLog( 2, " ====================== " )
} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
func obtenerAsignacionTopicPartition( consumidor *kafka.Consumer ) []kafka.TopicPartition {
  /* GET INFORMATION !!!! OK !!!!
  JordiLog( 1, " ********************** " )
  //JordiLog( 1, lector.GetRebalanceProtocol() ) 
  aux, _ :=  lector.GetMetadata( nil, true, 10000 ) 
  JordiLog( 1, string( aux.Brokers[0].ID ) )
  JordiLog( 1, aux.Topics[TEMA_TRABAJOS_ENCARGOS].Topic )
  for pa, _ := range aux.Topics[TEMA_TRABAJOS_ENCARGOS].Partitions {
    JordiLog( 1, PasarStructATextoJson( pa ) )
  }
  */

  asignacion, _ := consumidor.Assignment()

  /* OK
  /// OK !!! 
  JordiLog( 1, PasarStructATextoJson( asignacion ) )
  for _, as := range asignacion {
    JordiLog( 1, " Topic: " )
    JordiLog( 1, * as.Topic ) 
    JordiLog( 1, " Topic: %s, particion asignada: %d\n", *as.Topic, as.Partition )
    //JordiLog( 1, PasarStructATextoJson( as ) )
    //JordiLog( 1, as.TopicPartition  )
  }
  JordiLog( 1, " ********************** " )
  */

  return asignacion

} // ()

// --------------------------------------------------------------
//
// Requests a message from Kakfa through a Consumer (already
// configured to be in a consumer group and subscribed to a topic)
// A timeout is used to wait for a message.
//
// Consumer, Duration      --> f() <-->
// MensajeRecibido | Error <--
//
// --------------------------------------------------------------
func recibirMensajeDeConTimeout( lector *kafka.Consumer, duracion time.Duration ) (MensajeRecibido, error) {
  const nivelLog = 2

  JordiLog( nivelLog, " ###################### " )
  JordiLog( nivelLog, " GestorDeTrabajos.RecibirMensajeDeConTimeout: empiezo ! " )


  //
  // intento leer, supongo que con 1 seg de timeout
  //
  msg, err := lector.ReadMessage( duracion )

  JordiLog( nivelLog, " ###################### " )
  //
  //
  //
  if err != nil {
    JordiLog( nivelLog, " %%%%%%%%%%%%%%%%%%%%%% " )
    JordiLog( nivelLog, "RecibirMensajdeDeConTimeout: error: %v (%v)\n", err, msg)
    return MensajeRecibido{}, err
  }

  JordiLog( nivelLog, " ********************** " )

  //
  // lo paso a texto
  //
  var msgComoTexto = PasarStructATextoJson( msg )

  JordiLog( nivelLog, "mensaje recibido como texto" )
  JordiLog( nivelLog, msgComoTexto )

  //
  //
  //
  var resultado = MensajeRecibido { 
    Tema:        (* msg.TopicPartition.Topic) ,
    Valor:       string( msg.Value ),
    Particion:   msg.TopicPartition.Partition,
    Offset:      int64( msg.TopicPartition.Offset ),
    Clave:       string( msg.Key ),
    //Cabecera0:   string( msg.Headers[0].Key ), a veces NO hay
    Timestamp:   msg.Timestamp,
  }

  JordiLog( nivelLog, "RecibirMensajeConTimeout. Recibo: " )
  JordiLog( nivelLog, "    topic>%s< ", resultado.Tema )
  JordiLog( nivelLog, "    particion>%d< ", resultado.Particion )
  JordiLog( nivelLog, "    offset>%d< ", resultado.Offset )
  JordiLog( nivelLog, "    valor>%s< ", resultado.Valor )
  JordiLog( nivelLog, "timestamp>%s< ", resultado.Timestamp )

  if msg.Headers != nil {
    resultado.Cabecera0 = string( msg.Headers[0].Key )
  }

  JordiLog( nivelLog, " ====================== " )

  return resultado, nil
} // ()

// --------------------------------------------------------------
// Helper
//   f() --> Texto
// --------------------------------------------------------------
func GetRandomString() string {
  var aux = ( time.Now().UnixMilli() * int64(rand.Int()) )  % 31415926535 
  if aux < 0 {
    aux = -aux
  }
  return strconv.FormatInt( aux, 10 )
} // ()

// --------------------------------------------------------------
// Helper
// Object --> f() --> TextoJson
// --------------------------------------------------------------
func PasarStructATextoJson( obj interface{} ) string {

  comoBytes, _  := json.Marshal( obj )

  return string( comoBytes )

} // ()

// --------------------------------------------------------------
// Helper
// TextoJson --> f() --> Object
//
// with generics
// --------------------------------------------------------------
func PasarTextoJsonAStruct[T any]( textoJson string, p * T )  error {

  var comoBytes = []byte( textoJson )

  return json.Unmarshal( comoBytes, p )
} // ()

// ---------------------------------------------
// ---------------------------------------------
type CallbackCtrlC func()
func InstalaEscuchadorCtrlC( callback CallbackCtrlC ) {

  //
  // preparo para captura ctrl-c y terminar
  //
  c := make( chan os.Signal )
  // signal.Notify( c, os.Interrupt, syscall.SIGTERM )
  signal.Notify( c, os.Interrupt, syscall.SIGSEGV, syscall.SIGTERM )


  //signal.Notify( c, os.Interrupt )
  go func() { // nuevo thread o go routina que espera
    <- c // espera algo en el canal
    callback()
    //   elGestor.Desconectar()
    //  os.Exit( 0 )
  } () // llamando
} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
