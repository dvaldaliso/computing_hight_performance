// "importamos biblioteca zeromq"
import * as zmq from "zeromq"
export class Cliente{
    
    constructor(url, nombre)
    {
        this.url = url
        this.N=10
        this.cont = 0
        this.socketParaPedir = zmq.socket('req')
        this.MI_NOMBRE=nombre
        this.connect()
        this.recibirMensaje()
        this.enviarMensaje(0, this.MI_NOMBRE)
        this.close()
    }
    
     /**
     * Connects to the server.
     *
     * @return {undefined} No return value.
     */
    connect (){
       console.log("Connecting to hello world server...")
       this.socketParaPedir.connect(this.url)
    }
    // ....................................................
    // cuando reciba respuestas
    recibirMensaje(){
        this.socketParaPedir.on("message", function(respuesta) {
            this.cont++
            console.log("cliente ", this.MI_NOMBRE + ": recibo respuesta " , this.cont, ": [", respuesta.toString(), ']')
            // Check if all responses have been received
            if (this.cont === this.N) {
                // Close the socket
                this.socketParaPedir.close()
                // Exit the process
                process.exit(0)
            }

            this.enviarMensaje (this.cont, this.MI_NOMBRE)
            
        }.bind(this))
    }
    
    // ....................................................
    //
    // envío 10 mensajes (función recursiva)
    // seguidos cada 0.8 segundos (sin esperar respuesta. 
    // Atención: no debería ser así. Debería esperar respuesta.
    // Sin embargo, la biblioteca para JS parece que lo tolera
    //
    enviarMensaje (n,origen){
        if (n <= this.N) {
                console.log("enviando petición ", n, '...')
                this.socketParaPedir.send("Hello " + n + " desde " + origen)
                
                
        }
    }
    close(){
        process.on('SIGINT', function() {
            console.log ( " ** SIGINT capturada: cerrando !! ** ")
	        this.socketParaPedir.close()
        }.bind(this))
    }
}