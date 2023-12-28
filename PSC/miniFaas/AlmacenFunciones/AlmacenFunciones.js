
// ============================================================
// AlmacenDeFunciones.js
// 2023-12-12
// ============================================================

//import { createClient } from "redis"

const redis = require( "redis" )

// ------------------------------------------------------------
// ------------------------------------------------------------
class AlmacenFunciones {

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
  async guardar_funcion( idFuncion, textoFuncion ) {
    await this.cliente.set( "funcion_" + idFuncion, textoFuncion )
  } // ()

  // ..........................................................
  // ..........................................................
  async recuperar_funcion( idFuncion ) {
    return await this.cliente.get( "funcion_" + idFuncion )
  } // ()


} // class

// ------------------------------------------------------------
// ------------------------------------------------------------
module.exports = {
  AlmacenFunciones,
}

// ============================================================
// ============================================================
// ============================================================
// ============================================================
