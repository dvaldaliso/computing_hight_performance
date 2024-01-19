const zmq = require('zeromq');
var n=0;
// Crear socket del cliente
const client = zmq.socket('req');

// Conectar el cliente al enrutador en el puerto 5555
client.connect('tcp://127.0.0.1:5555');

// Enviar solicitud al enrutador
setTimeout(() => {
    // Enviar la respuesta de vuelta al cliente
    n++;
    enviarMensaje("iniciall")
  }, 2000);
    


// Manejar respuestas del enrutador
client.on('message', (response) => {
  console.log(`Received response from router: ${response.toString()}`);
  // Cerrar el socket del cliente después de recibir la respuesta
  
});
var stdin = process.openStdin()
stdin.addListener ("data", 
						   function (datos) {
                            enviarMensaje(datos)
						   }
						  );



function enviarMensaje(msg){
    console.log(msg)
    client.send(msg);
}                          

// Manejar interrupciones
process.on('SIGINT', () => {
    console.log('Shutting down...');
    client.close();
    process.exit();
  });
    