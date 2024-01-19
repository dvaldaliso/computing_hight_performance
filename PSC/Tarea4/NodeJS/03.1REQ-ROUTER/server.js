const zmq = require('zeromq');

// Crear socket del enrutador
const router = zmq.socket('router');

// Configurar el enrutador para escuchar en el puerto 5555
router.bindSync('tcp://127.0.0.1:5555');

console.log('Router listening on port 5555');

// Manejar solicitudes
router.on('message', (identity, message) => {
  console.log(`Received request from ${identity.toString("hex")}: ${message.toString()}`);

  // Simular un procesamiento
  setTimeout(() => {
    // Enviar la respuesta de vuelta al cliente
    enviarMensaje(identity,'Response from router')
  }, 1000);
});

// Manejar interrupciones
process.on('SIGINT', () => {
  console.log('Shutting down...');
  router.close();
  process.exit();
});


function enviarMensaje (identity,mesg) {
    router.send([identity, '', mesg]);
}
