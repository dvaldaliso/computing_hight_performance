// --------------------------------------------------------------
// 
// GestorDeTrabajos.go
//
// @version     1.02 
// @since       2022-12-13
// @autor       Jordi Bataller Mascarell
//
// @see         tests, mainly test5 and test4
//
// @see         github.com/confluentinc/confluent-kafka-go
// @see         redis "github.com/go-redis/redis/v8"
//
// A server gets jobs from clients. The jobs are to be performed
// by a swarm of workers/executors. Once a job is done, its
// executor stores the results, so the client may retrieve them
// at a later time.
//
// This class is an interface to manage this asynchronous schema.
// Upon arrival, a job is anounced under the topic "TRABAJOS_ENCARGOS"
// to which a set of workers in the same "consumer group" is subscribed.
// One of the workers takes the job. Once done it advertises and
// saves the result.
//
// How to use:
//
//  NewGestorDeTrabajos(), Conectar(), ......., Descoonectar()
//
//  ..... for a client:
//    
//    NuevoEncargo(), asynchronous wait, ObtenerRespuestaAEncargo()
//
//    It may read announcements of jobs done with
//      while (true) RecibirMensajesDeRespuestas()
//
//  ..... for a worker:
//    DameTrabajo(), do work, ResponderAEncargo()
// 
// --------------------------------------------------------------

package gestorDeTrabajos

// --------------------------------------------------------------
// imports
// --------------------------------------------------------------
import (
  //"fmt"
  "errors"
  "log" 
  //"log/ioutil" //log.SetOutput( ioutil.Discard )  log.SetFlags( 0 )


  "time"

  kafka "github.com/confluentinc/confluent-kafka-go/kafka"

  "context"
  redis "github.com/go-redis/redis/v8"

)

// --------------------------------------------------------------
// struct defining the answer to a Job
// --------------------------------------------------------------
type RespuestaEncargo struct {
  IdEncargo     string
  Estado        string  // 200=OK, 400=BadRequest, ...
  Respuesta     string  // to be interpreted by client
  Timestamp     time.Time
} // type

// --------------------------------------------------------------
// GestorDeTrabajos "class"
// --------------------------------------------------------------

// --------------------------------------------------------------
// struct with the data fields we need to interact
// with Kafka and Redis
// --------------------------------------------------------------
type GestorDeTrabajos struct {
  //kafkaURLs             []string
  //redisURL              string
  configuracion           Configuracion

  lectorEncargos         * kafka.Consumer
  lectorRespuestas       * kafka.Consumer

  escritorTodo           * kafka.Producer

  conexionRedis          * redis.Client
} // type GestorDeTrabajos 

// --------------------------------------------------------------
// constructor
//
// kafkaUrl: URL, redisUrL: URL --> f() -->
//             GestorDeTrabajos <--
// --------------------------------------------------------------
func NewGestorDeTrabajos( config_ Configuracion ) GestorDeTrabajos {

  log.Println( " =============================" )
  log.Println( " Configuracion: " )
  log.Println( PasarStructATextoJson( config_ ) )

  return GestorDeTrabajos{  configuracion: config_ }

} // ()

// --------------------------------------------------------------
//
// Connects to the Kafka and Redis servers
//
//                f() --> 
// 0 | Error <--
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) Conectar() error {

  JordiLog( 1, " ====================== " )
  JordiLog( 1, "GestorDeTrabajos.conectar(): %s ", "conectando" )
  JordiLog( 1, "kafka url = %s", this.configuracion.KafkaURLs )
  JordiLog( 1, "redis url = %s", this.configuracion.RedisURL )

  // ............................................................
  // redis
  // ............................................................
  this.conexionRedis = redis.NewClient( & redis.Options {
    Addr:       this.configuracion.RedisURL,
    Password:   "", //  sin password 
    DB:         0, // bd por defecto
  })

  ctx := context.Background()

  //
  // comprobemos que hemos conectado con redis
  //
  errR := this.conexionRedis.Set( ctx, "hola-clave", "mundo-valor", 0 ).Err()
  if errR != nil {
    return  errors.New( "no pude conectar con redis" )
  }

  val, errR := this.conexionRedis.Get( ctx, "hola-clave").Result()
  if errR != nil || val != "mundo-valor" {
    return  errors.New( "no pude conectar con redis" )
  }

  JordiLog( 2, " conectado con redis " )

  // ............................................................
  // kafka
  // ............................................................

  // worker: necesita escritor y lectorTrabajos
  // no worker:necesita escritor y lectorRespuesas
  
  //
  // creo el escritor de todo
  //
  var err error

  this.escritorTodo, err = kafka.NewProducer( & kafka.ConfigMap {
    "bootstrap.servers":  this.configuracion.KafkaURLs[0],
  } )

  if err != nil {
    log.Println( " hubo un error en NewProducer 1" )
    log.Println( err )
    return  errors.New( "no pude crear escritorTodo" )
  }

  //
  // creo topcis con varias particiones 
  // AQUI: revisar: ¿hay que crear esto cada vez?  Solo
  // debería hacerlo uno de los que se conectan, no todos.
  // AQUI: revisar la cantidad de particiones por topic
  //crearTopic( this.escritorTodo, TEMA_TRABAJOS_ENCARGOS, 3 )
  crearTopic( this.escritorTodo, TEMA_TRABAJOS_ENCARGOS, this.configuracion.NumParticionesTrabajos )
  crearTopic( this.escritorTodo, TEMA_TRABAJOS_RESPUESTAS, 1 )

  // cliente: necesita escritor y lectorRespuesas
  if this.configuracion.EsCliente {
    //
    // creo el lector de respuestas
    //
    this.lectorRespuestas = nuevoConsumidor( this.configuracion.KafkaURLs, GRUPO_RESPUESTAS, TEMA_TRABAJOS_RESPUESTAS )

    if this.lectorRespuestas == nil {
      return  errors.New( "no pude crear lectorRespuestas" )
    }
  }

  // worker: necesita escritor y lectorTrabajos
  if this.configuracion.EsWorker {
    // worker: necesita escritor y lectorTrabajos
    //
    // creo el lector de encargos
    //
    this.lectorEncargos = nuevoConsumidor( this.configuracion.KafkaURLs, GRUPO_WORKERS, TEMA_TRABAJOS_ENCARGOS )

    if this.lectorEncargos == nil {
      return  errors.New( "no pude crear lectorEncargos" )
    }
  }

  JordiLog( 1, " conectado !!!" )
  JordiLog( 1, " ====================== " )

  return nil
} //()

// --------------------------------------------------------------
// 
// Disconnects from Kafka and Redis servers
// 
// f() -->
// 
// --------------------------------------------------------------
func (this *GestorDeTrabajos) Desconectar() {
  JordiLog( 1, " ====================== " )
  JordiLog( 1, " GestorDeTrabajos.Desconectar(): desconectando " ) 

  const nivelLog = 2

  if this.conexionRedis != nil {
    this.conexionRedis.Close()
  }

  if this.escritorTodo != nil {
    this.escritorTodo.Flush( 1000 ) // AQUI: revisar este timeout
    this.escritorTodo.Close()
  }

  if this.lectorEncargos != nil {
    this.lectorEncargos.Close()
  }

  if this.lectorRespuestas != nil {
    this.lectorRespuestas.Close()
  }

  //JordiLog( nivelLog, " 1 " )

  JordiLog( 1, " ====================== " )
} //()

// --------------------------------------------------------------
//
// Sends a message to the Topic "Encargos"
//
// clave: Texto, valor: texto 
//  --> f() -->
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) enviarMensajeAEncargos( clave string, valor string ) {
  enviarMensajeA( this.escritorTodo, TEMA_TRABAJOS_ENCARGOS, clave, valor )
} // ()

// --------------------------------------------------------------
//
// Sends a message to the Topic "Respuestas"
//
// clave: Texto, valor: texto 
//  --> f() -->
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) enviarMensajeARespuestas( clave string, valor string ) {
  enviarMensajeA( this.escritorTodo, TEMA_TRABAJOS_RESPUESTAS, clave, valor )
} // ()

// --------------------------------------------------------------
// Sends a new Job
//
// Trabajo 
//         --> 
//                  f() -->
//         <--
// idEncargo: Texto
//
// @return    the job id
// --------------------------------------------------------------
func (this *GestorDeTrabajos) NuevoEncargo( trabajo Trabajo ) (idEncargo string) {

  JordiLog( 2, " GestorDeTrabajos.NuevoEncargo nombreFuncion=%s\n", trabajo.NombreFuncion )

  //
  // genero numero de encargo
  //
  idEncargo = GetRandomString() 

  //
  // compongo el encargo
  //
  var encargo = Encargo {
    IdEncargo: idEncargo,
    ElTrabajo: trabajo,
    Timestamp: time.Now(),
  }

  //
  // lo paso a texto
  //
  var encargoComoTexto = PasarStructATextoJson( encargo )

  JordiLog( 2, " encargo en texto=%s", encargoComoTexto )

  //
  // lo envio a Kafka
  //
  this.enviarMensajeAEncargos( encargo.IdEncargo, encargoComoTexto )

  return idEncargo
} // ()

// --------------------------------------------------------------
//
// Requests a Job
//
//          f() <--
//    <--
// Encargo | Error
//
// @return an error if timeout (i.e. No pending job exists)
// --------------------------------------------------------------
func (this *GestorDeTrabajos) DameTrabajo( ) (Encargo, error) {

  const nivelLog = 2

  JordiLog( nivelLog, "=============================" )

  //
  // Ojo: esto es para suscribirse, pillar un encargo
  // y desuscribirse para que a otros consumers les lleguen
  // mensajes de encargos en el Topic
  // Hay que recordar que en Kafka cuando un consumir
  // le asignan un Topic-Partition: se la merienda sin 
  // compartir
  //
  //this.lectorEncargos.Subscribe( TEMA_TRABAJOS_ENCARGOS, nil )
  //defer this.lectorEncargos.Unsubscribe()

  //
  // pido un mensaje de la cola de encargos
  //
  var mensaje, err = this.recibirMensajeDeEncargos()

  //JordiLog( nivelLog, "GestorDeTrabajos.DameTrabajo: mensaje= >%s<", mensaje )
  JordiLog( nivelLog, "GestorDeTrabajos.DameTrabajo: mensaje= >%s<", mensaje.Valor )
  if err != nil {
    JordiLog( nivelLog, "GestorDeTrabajos.DameTrabajo: error al recibir ")
    JordiLog( nivelLog, "%s", err )
    return Encargo{}, err
  }

  JordiLog( nivelLog, "*****************************" )

  //
  // el encargo, como texto, está en el campo Valor
  //
  /*
  var encargoComoBytes = []byte( mensaje.Valor )

  var encargo Encargo

  //err := json.Unmarshal( encargoComoTexto, & encargo )
  json.Unmarshal( encargoComoBytes, & encargo )
  */

  var encargo Encargo

  // añado el timestamp del mensaje en que venia el encargo
  // no va bien? encargo.Timestamp = mensaje.Timestamp

  PasarTextoJsonAStruct( mensaje.Valor, &encargo ) 

  JordiLog( nivelLog, "=============================" )

  return encargo, nil
} // ()

// --------------------------------------------------------------
// Gives the answer/solution of Job
//
// RespuetaAEncargo --> f() -->
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) ResponderAEncargo( respuesta RespuestaEncargo ) {

  const nivelLog = 2

  JordiLog( nivelLog, " ====================== " )
  //
  // pongo timestamp (¿sería mejor preguntar la hora a Kafka?)
  //
  respuesta.Timestamp = time.Now()

  //
  // lo paso a texto
  //
  var respuestaComoTexto = PasarStructATextoJson( respuesta )

  JordiLog( nivelLog,  "GestorDeTrabajos.ResponderAEncargo: respuesta en texto=%s", respuestaComoTexto )

  //
  // lo pongo en Redis
  //
  //err := this.conexionRedis.Set( ctx, respuesta.IdEncargo, respuestaComoTexto, 0 ).Err()
  this.conexionRedis.Set( context.Background(), respuesta.IdEncargo, respuestaComoTexto, 0 )

  //
  // lo envio a Kafka
  //
  this.enviarMensajeARespuestas( respuesta.IdEncargo, respuestaComoTexto )

  JordiLog( nivelLog, " ====================== " )
} // ()

// --------------------------------------------------------------
//
// Requests a message from the Job's Topic 
//
//                             f() <-->
// MensajeRecibido | Error <--
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) recibirMensajeDeEncargos( ) (MensajeRecibido, error) {

  return recibirMensajeDeConTimeout( this.lectorEncargos, time.Second * time.Duration( this.configuracion.ReadTimeout ) )

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
func (this *GestorDeTrabajos) ObtenerAsignacionTopicPartition( ) []kafka.TopicPartition {
  return obtenerAsignacionTopicPartition( this.lectorEncargos )
} // ()

// --------------------------------------------------------------
//
// Requests a message from the Answers's Topic 
//
//                             f() <-->
// MensajeRecibido | Error <--
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) recibirMensajeDeRespuestas( ) (MensajeRecibido, error) {

  return recibirMensajeDeConTimeout( this.lectorRespuestas, time.Second * time.Duration( this.configuracion.ReadTimeout ) )

} // ()

// --------------------------------------------------------------
//
// Requests the answer to a previous Job
//
// idEncargo: Texto         --> f()
// RepuestaEncargo | Error  <--       
//
// --------------------------------------------------------------
func (this *GestorDeTrabajos) ObtenerRespuestaAEncargo( idEncargo string) (RespuestaEncargo, error) {

  //
  // Veamos: de momento no sé buscar en el log de Kafka.
  // De hecho no estoy seguro que se pueda: parece ser que no se puede
  // La única posibilidad sería
  // nos leamos entero un Topic para filtrar la respuesta
  // a idEncargo. Pero esto no parece muy eficiente
  // Así pues: se puede estar pendiente de lo que se publique
  // en el Topic de respuestas usando RecibirMensajeDeRespuestas
  // (ver test5)
  //
  // La otra alternativa es dejar la respuesta *también* en redis
  // e ir a buscarla allí.
  //
  //return RespuestaEncargo{}, errors.New( "NO_ESTOY_IMPLEMENTADO: ObtenerRespuestaAEncargo" )

  //
  // busco en Redis la respuesta
  //
  respuestaTxt, err := this.conexionRedis.Get( context.Background(), idEncargo ).Result()

  //
  // fallo algo'
  //
  if err != nil {
    return RespuestaEncargo{}, errors.New( "404 redis" )
  }

  //
  // descongelo y devuelvo
  //
  /*
  var respuestaComoBytes = []byte( respuestaTxt )


  json.Unmarshal( respuestaComoBytes, & respuesta )
  */

  var respuesta RespuestaEncargo

  PasarTextoJsonAStruct( respuestaTxt, &respuesta ) 

  return respuesta, nil

} // ()
// --------------------------------------------------------------
// fin GestorDeTrabajos
// --------------------------------------------------------------

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
