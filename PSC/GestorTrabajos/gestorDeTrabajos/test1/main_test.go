// --------------------------------------------------------------
// --------------------------------------------------------------

package main

// --------------------------------------------------------------
// --------------------------------------------------------------

//import "gestorDeTrabajos"

import "testing"
//import "fmt"
import "fmt"

import ( 
  gdt "gestorDeTrabajos" // con alias
)

// --------------------------------------------------------------
// --------------------------------------------------------------
//func TestMain( tester *testing.M ) {
func Test( tester *testing.T ) {

  fmt.Println( "***********************************************" )
  fmt.Println( "TEST: nuevoEncargo + DameTrabajo " )
  fmt.Println( "***********************************************" )

//  var elGestor = gdt.NewGestorDeTrabajos( []string {"localhost:9091"}, "localhost:6379" )
  
  var texto = `{"redisURL": "localhost:6379", "kafkaURLs":["localhost:9091", "localhost:9092", "localhost:9093"], "readTimeout": 10, "NumParticionesTrabajos": 3 }`
  // "EsWorker": true, "EsCliente": true <== esta ya por defecto

  var elGestor = gdt.NewGestorDeTrabajos( gdt.ConfiguracionDesdeTextoJson( texto ) )


  elGestor.Conectar()
  defer elGestor.Desconectar() 

  test3( elGestor, tester )

} /// ()

// --------------------------------------------------------------
// --------------------------------------------------------------
func test3( gestor gdt.GestorDeTrabajos, tester *testing.T ) {

  //
  // envío encargo
  //
  var trabajillo = gdt.Trabajo {
    IdExterno:        "trabajillo-1",
    NombreFuncion:    "f1",
    Parametros:       "{ x: 12, y: 34}",
  }

  var idEncargo = gestor.NuevoEncargo( trabajillo )
  
  fmt.Printf( "** enviado idEncargo = %s", idEncargo )

  //
  // pido trabajo
  //
  var encargo, _ = gestor.DameTrabajo()

  fmt.Println( "** encargo recibido: " )
  fmt.Println( encargo )

  //
  // compruebo
  //
  if idEncargo != encargo.IdEncargo {
    tester.Errorf( " el numero de encargo no concuerda. Esperaba: %s, Recibi: %s", 
    idEncargo, encargo.IdEncargo )
  }

  if encargo.ElTrabajo.Parametros != trabajillo.Parametros {
    tester.Errorf( " los parametros del encargo no concuerda. Esperaba: %s, Recibi: %s", 
    trabajillo.Parametros, encargo.ElTrabajo.Parametros )
  }

} // ()

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
