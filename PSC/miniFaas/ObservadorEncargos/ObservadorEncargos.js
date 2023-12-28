// ============================================================
// ObservadorEncargos.js
// 2023-12-14
// ============================================================

const redis = require( "redis" )

// ------------------------------------------------------------
// ------------------------------------------------------------
class ObservadorEncargos {

  // ..........................................................
  // ..........................................................
  constructor( urlRedis, el_observador ) {
    const self = this
    
    this.el_observador = el_observador

    
    return new Promise( async function( resolver, rechazar ) {

      self.cliente = redis.createClient(
        {
          url: urlRedis
        }
      )

      await self.cliente.connect()

      if ( self.cliente.isReady == false ) {
        rechazar( "error en conexion con redis" )
      }

      self.instalar_callback_encargos()
      self.instalar_callback_resultados()

      resolver( self )

    }) // new Promise

  } // constructor

  // ..........................................................
  // ..........................................................
  async cerrar() {
    await this.cliente.disconnect()
  } // ()
  
  // ..........................................................
  // ..........................................................
  instalar_callback_encargos() {
    
    const self = this

    this.espera_nuevo_encargo( function( encargo ) {
      // Me avisan que hay un nuevo encargo: llamo
      // al callback del observador y
      // reinstalo el callback 
      self.el_observador.nuevo_encargo( encargo )

      // Si reinstalo recursivamente, no daría
      // problemas si es recursión final. Si no podríamos
      // acabar saturando la pila, con las llamadas recursivas))
      //// self.instalar_callback_encargos()
      
      // pruebo a hacerlo con nextTick(). Ponemos en la cola
      // del loop de node que nos llame
      process.nextTick( function() {
        self.instalar_callback_encargos() }
      )
      
    })
  } // ()

  // ..........................................................
  // ..........................................................
  espera_nuevo_encargo( cb ) {
    // no hago await para recibir la promesa
    // y poner un callback con el then
    var promesa = this.cliente.xRead(
      redis.commandOptions( { isolated: true} ),
      //[ {key: "ENCARGOS", id: "0" } ], // 0 lee el stream/log desde el principio
      [ {key: "ENCARGOS", id: "$" } ], // $ lee lo nuevo que se añada desde ahora
      { COUNT: 1, BLOCK: 0 } // quiero 1 registro, espero 0: hasta que haya: bloqueante
    )

    promesa
      .then( function( res ) {
        // aquí es donde aviso, cuando se añade un encargo
        cb( JSON.parse( res[0].messages[0].message.encargo ) )
      })

  } // ()

  // ..........................................................
  // ..........................................................
  instalar_callback_resultados() {
    
    const self = this

    this.espera_nuevo_resultado( function( resultado ) {
      self.el_observador.nuevo_resultado( resultado )
      self.instalar_callback_resultados()
    })
  } // ()

  // ..........................................................
  // ..........................................................
  espera_nuevo_resultado( cb ) {
    var promesa = this.cliente.xRead(
      redis.commandOptions( { isolated: true} ),
      [ {key: "RESULTADOS", id: "$" } ], // $ lee lo nuevo que se añada desde ahora
      { COUNT: 1, BLOCK: 0 } // quiero 1 registro, espero 0: hasta que haya: bloqueante
    )

    promesa
      .then( function( res ) {
        cb( JSON.parse( res[0].messages[0].message.resultado ) )
      })

  } // ()

} // class 

// ------------------------------------------------------------
// ------------------------------------------------------------
module.exports = {
  ObservadorEncargos,
}


// ============================================================
// ============================================================
// ============================================================
// ============================================================
