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
	"context"
	"fmt"
	"os"

	kafka "github.com/segmentio/kafka-go"
)

var i int = 0

// --------------------------------------------------------------------
// --------------------------------------------------------------------
func enviarMensage(w *kafka.Writer) {

	texto := fmt.Sprintf("Hello World! %d", i)
	fmt.Printf("envio: %s\n", texto)
	w.WriteMessages(
		context.Background(),
		kafka.Message{
			Key:   []byte("Clave A"),
			Value: []byte(texto),
		},
	)
	i++
	if i == 10 {
		w.Close()
		os.Exit(0)
	}
}

func recibiRespuesta(lector *kafka.Reader, w *kafka.Writer) {

	for {
		msg, err := lector.ReadMessage(context.Background())

		if err != nil {
			fmt.Println(" *** ERROR *** ")
			fmt.Println(err)
		}

		fmt.Println(" --> recibo: ")
		fmt.Println(msg.Topic)
		fmt.Println(string(msg.Key))
		fmt.Println(string(msg.Value))

		enviarMensage(w)
	}

}
func main() {
	fmt.Print("productor empieza\n")
	w := &kafka.Writer{
		Addr:  kafka.TCP("localhost:9092"),
		Topic: "trabajos",
	}

	lector := kafka.NewReader(kafka.ReaderConfig{
		Brokers: []string{"localhost:9092"},
		Topic:   "respuesta",
	})

	//for i:=0; i<=10; i++ {
	enviarMensage(w)
	//} // for

	//respuesta
	recibiRespuesta(lector, w)

} // ()

// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
