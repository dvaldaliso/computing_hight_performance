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
	"reflect"

	kafka "github.com/segmentio/kafka-go"
)

// --------------------------------------------------------------------
// --------------------------------------------------------------------
func readMessage(lector *kafka.Reader, w *kafka.Writer) {
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

		rt := reflect.TypeOf(msg.Key)
		if rt.Kind() != reflect.Array {
			continue
		}
		responder(w, msg)

	}
}

func responder(w *kafka.Writer, msg kafka.Message) {
	fmt.Println("responder")
	texto := fmt.Sprintf("Hello World! %d", msg.Key)
	fmt.Printf("envio: %s\n", texto)
	w.WriteMessages(
		context.Background(),
		kafka.Message{
			Key:   []byte(msg.Key),
			Value: []byte(texto),
		},
	)
}
func main() {
	fmt.Println("consumidor empieza\n")

	lector := kafka.NewReader(kafka.ReaderConfig{
		Brokers: []string{"localhost:9092"},
		Topic:   "trabajos",
	})
	// Inicializar writer
	w := &kafka.Writer{
		Addr:  kafka.TCP("localhost:9092"),
		Topic: "respuesta",
	}

	defer lector.Close()

	fmt.Println(" espero mensajes ... ")

	readMessage(lector, w)

	fmt.Println(" FIN ")

} // ()

// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
