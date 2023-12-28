// ============================================================
// ConsultasEncargos.js
// 2023-12-17
// ============================================================

const redis = require( "redis" )

// ------------------------------------------------------------
// ------------------------------------------------------------
class ConsultasEncargos {

  // ..........................................................
  // ..........................................................
  constructor( urlRedis ) {
    const self = this

    
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
  async cuantos_encargos() {
    return await this.cliente.sendCommand( ["XLEN", "ENCARGOS"])
  } // ()

  // ..........................................................
  // ..........................................................
  async cuantos_resultados() {
    return await this.cliente.sendCommand( ["XLEN", "RESULTADOS"])
  }

  // ..........................................................
  // ..........................................................
  async cuantos_encargos_pendientes() {
    // encargos leídos que no tienen ACK como resueltos
    // (en el grupo de TRABAJADORES)
    const res = await this.cliente.sendCommand( ["XPENDING", "ENCARGOS", "TRABAJADORES"])
    return res[0]
  } // ()

} // class 

// ------------------------------------------------------------
// ------------------------------------------------------------
module.exports = {
  ConsultasEncargos,
}


// ============================================================
// ============================================================
// ============================================================
// ============================================================
