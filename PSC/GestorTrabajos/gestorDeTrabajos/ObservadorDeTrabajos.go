// --------------------------------------------------------------
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

)

// --------------------------------------------------------------
// ObservadoObservadorrDeTrabajos "class"
// --------------------------------------------------------------

// --------------------------------------------------------------
// struct with the data fields we need to interact
// with Kafka and Redis
// --------------------------------------------------------------
type ObservadorDeTrabajos struct {

  configuracion           Configuracion

  observadorRespuestas   * kafka.Consumer
  observadorEncargos     * kafka.Consumer

} // type 

// --------------------------------------------------------------
// constructor
//
// kafkaUrl: URL, redisUrL: URL --> f() -->
//             ObservadorDeTrabajos <--
// --------------------------------------------------------------
func NewObservadorDeTrabajos( config_ Configuracion ) ObservadorDeTrabajos {

  log.Println( " =============================" )
  log.Println( " Configuracion: " )
  log.Println( PasarStructATextoJson( config_ ) )

  return ObservadorDeTrabajos{  configuracion: config_ }

} // ()

// --------------------------------------------------------------
//
// Connects to the Kafka 
//
//                f() --> 
// 0 | Error <--
//
// --------------------------------------------------------------
func (this *ObservadorDeTrabajos) Conectar() error {

  JordiLog( 1, " ====================== " )
  JordiLog( 1, "ObservadorDeTrabajos.conectar(): %s ", "conectando" )
  JordiLog( 1, "kafka url = %s", this.configuracion.KafkaURLs )

  // ............................................................
  // kafka
  // ............................................................

  //
  // creo el observador de encargos
  //
  this.observadorEncargos = nuevoConsumidor( this.configuracion.KafkaURLs, GRUPO_OBSERVADOR_ENCARGOS, TEMA_TRABAJOS_ENCARGOS )

  if this.observadorEncargos == nil {
    return  errors.New( "no pude crear observadorEncargos" )
  }

  //
  // creo el observador de respuestas
  //
  this.observadorRespuestas = nuevoConsumidor( this.configuracion.KafkaURLs, GRUPO_OBSERVADOR_RESPUESTAS, TEMA_TRABAJOS_RESPUESTAS )

  if this.observadorRespuestas == nil {
    return  errors.New( "no pude crear observadorRespuestas" )
  }

  //
  // no errors
  //
  return nil
} //()

// --------------------------------------------------------------
// 
// Disconnects from Kafka 
// 
// f() -->
// 
// --------------------------------------------------------------
func (this *ObservadorDeTrabajos) Desconectar() {
  JordiLog( 1, " ====================== " )
  JordiLog( 1, " ObservadorDeTrabajos.Desconectar(): desconectando " ) 

  const nivelLog = 2
  
  this.observadorEncargos.Close()
  this.observadorRespuestas.Close()

  //JordiLog( nivelLog, " 1 " )

  JordiLog( 1, " ====================== " )
} //()

// --------------------------------------------------------------
// --------------------------------------------------------------
func (this *ObservadorDeTrabajos) ObservarMensajeDeEncargos( ) (MensajeRecibido, error) {

  return recibirMensajeDeConTimeout( this.observadorEncargos, time.Second * time.Duration( this.configuracion.ReadTimeout ) )

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
func (this *ObservadorDeTrabajos) ObservarMensajeDeRespuestas( ) (MensajeRecibido, error) {

  return recibirMensajeDeConTimeout( this.observadorRespuestas, time.Second * time.Duration( this.configuracion.ReadTimeout ) )

} // ()

// --------------------------------------------------------------
// fin ObservadorDeTrabajos
// --------------------------------------------------------------

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
