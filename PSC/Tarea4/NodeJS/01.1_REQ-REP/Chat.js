import * as zmq from "zeromq"
export class Chat{
    #socketParaResponder
    #cont
    constructor(url)
    {
        this.url = url
        this.cont = 0
        this.socketParaResponder = zmq.socket('rep')
        this.bind()
        this.espera()
        this.close()
    }
    
    //
	// bind = vincular numero con socket = anuncio que mi
	// socket está disponible
	// en el puerto 5555 (al cuál se puede conectar cualquiera
	// por tcp)
	//
	// Se le da también un callback para que cuando
	// efectivamente el bind()  haya ocurrido
	// se ejecuta la función
	//
    bind (){
        
        this.socketParaResponder.bind(this.url, function(err) {
            if (err) {
                console.log(err)
            } else {
                console.log("Listening ..."+this.url)
            }
	    }.bind(this))
    }
    //
	// función que debe ejecutarse cuando
	// llegue un mensaje al socket
	//
    espera() {
        
        this.socketParaResponder.on('message', function(peticionQueRecibo) {
            //
            // función  que se ejecuta cuando llega un mensaje
            //
            this.cont++
            // sumo 1 al contador de mensajes llegados
            
            // informo por pantalla
            console.log("servidor recibo petición: "+this.cont
                        + " [", peticionQueRecibo.toString(), "]")
    
            // hago algo de "trabajo": esperar algunos segundos
            // y entonces ejecutar el callback, en el cuál respondemos
            // 
            // setTimeout = encargar algo para dentro de un tiempo
            setTimeout(() => {
                console.log("servidor respondo petición: " )
                this.distribuir(peticionQueRecibo)
                
              }, 1000);
        }.bind(this)) // socketParaResponder.on()
    }
    
    distribuir(mensaje){
        if (this.socketParaResponder) 
                    this.socketParaResponder.send(
                        " respuesta desde servidor, "
                            + " echo de "
                            + mensaje.toString())
    }
    close(){
        process.on('SIGINT', function() {
            console.log (" sigint capturada ! ")
            console.log (" hasta luego Lucas! ")
            this.socketParaResponder.close()
            // socketParaResponder = null
        }.bind(this))
    }
}