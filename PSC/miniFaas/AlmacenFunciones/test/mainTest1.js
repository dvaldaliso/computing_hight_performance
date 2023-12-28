

// ------------------------------------------------------------
// ------------------------------------------------------------
const Adf = require( "../AlmacenFunciones.js" )

// ------------------------------------------------------------
// ------------------------------------------------------------
async function main() {
  // si estamos en linux (host) y redis en contenedor
  const adf = await new Adf.AlmacenFunciones( "redis://localhost:6379/" )

  // si estamos en contenedor y redis en contenedor
  // redis://redisserv:6379/

  console.log( "conectado ")

  await adf.guardar_funcion( "foo", "function (a) { return a*2 }")

  var res = await adf.recuperar_funcion( "foo" )

  console.log( res )

  res = await adf.recuperar_funcion( "no_existe" )

  console.log( res )

  adf.cerrar()

  console.log( "hecho ")

} // main()


// ------------------------------------------------------------
// ------------------------------------------------------------
main()
// ------------------------------------------------------------
// ------------------------------------------------------------
