
// ============================================================
// Utilidades.js
// 2023-12-12
// ============================================================

// ------------------------------------------------------------
// ------------------------------------------------------------
function async_timeout( millis ) {
  return new Promise( function( resolve, reject ) {
    setTimeout( function() {
      resolve()
    }, millis )
  } )
} // ()

// ------------------------------------------------------------
// textoFuncion: TextoFuncion, input: Objeto -> f() -> Objeto
// ------------------------------------------------------------
async function ejecutar_textoFuncion( textoFuncion, input ) {

  // Crea una nueva función (new Funcion) que inmediatamente
  // se ejecuta (notar los () al final de la línea) 
  // Por tanto se ejecuta: return function nombre( ... ) { ... }
  // Es decir, devuelve la función nombre ( ... ){ ... }
  // lo cuál se guarda en f, ya lista para ser llamada !
  var f = new Function( "return " + textoFuncion )()

  // textoFuncion (ahora f() )) puede ser síncrona o asíncrona
  var res = await f( input )

  //console.log( res )

  return res

} // ()


// ------------------------------------------------------------
// ------------------------------------------------------------
async function ejecutar_textoPrograma( textoPrograma, input ) {

  var f = new Function( 'input',  textoPrograma )

  var res = await f( input )

  //console.log( res )

  return res

} // ()

// ------------------------------------------------------------
// ------------------------------------------------------------
module.exports = { 
  ejecutar_textoFuncion,
  async_timeout,
  ejecutar_textoPrograma,
}

// ============================================================
// ============================================================
// ============================================================
// ============================================================
