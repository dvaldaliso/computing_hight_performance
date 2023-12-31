// --------------------------------------------------------------------
// --------------------------------------------------------------------
// $    go mod tidy
// $    go build main.go       or      $   go run main.go

// --------------------------------------------------------------------
// --------------------------------------------------------------------
package main

// --------------------------------------------------------------------
// --------------------------------------------------------------------
import (
  "fmt"
  "context"

  kafka "github.com/segmentio/kafka-go"
)

// --------------------------------------------------------------------
// --------------------------------------------------------------------
func main() {
  fmt.Println( "consumidor empieza\n" )

  lector := kafka.NewReader( kafka.ReaderConfig {
    Brokers: []string {"localhost:9092"},
    Topic: "topicazo1",
  })

  defer lector.Close()

  fmt.Println( " espero mensajes ... " )
  for {
    msg, err := lector.ReadMessage( context.Background() )
    if err != nil {
      fmt.Println( " *** ERROR *** " )
      fmt.Println( err )
    }

    fmt.Println( " --> recibo: " )
    fmt.Println( msg.Topic )
    fmt.Println( string( msg.Key ) )
    fmt.Println( string( msg.Value ) )
  } // for

  fmt.Println( " FIN " )

} // ()

// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
