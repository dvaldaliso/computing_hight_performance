

// ------------------------------------------------------------
// ------------------------------------------------------------
const OE = require( "../ObservadorEncargos.js" )
const CE = require( "../ConsultasEncargos.js" )

// ------------------------------------------------------------
// ------------------------------------------------------------
async function main() {


  console.log( "--------------------------------------")
  console.log( "--------------------------------------")
  console.log( "mainTest1.js ")
  console.log( "--------------------------------------")

  // si estamos en linux (host) y redis en contenedor
  const ce = await new CE.ConsultasEncargos( "redis://localhost:6379/" )

  const informar = async function () {
    console.log( " encargos totales " + await ce.cuantos_encargos()) 
    console.log( " resultados totales " + await ce.cuantos_resultados()) 
    console.log( " encargos pendientes " +  await ce.cuantos_encargos_pendientes())
  }

  // si estamos en linux (host) y redis en contenedor
  const oe = await new OE.ObservadorEncargos( 
    "redis://localhost:6379/" ,
    {
      nuevo_encargo: function( encargo ) {
        console.log( " nuevo_encargo: " )
        console.log( encargo )
        informar()
      },

      nuevo_resultado: function( resultado ) {
        console.log( " nuevo_resultado: " )
        console.log( resultado )
        informar()
      }
    }
  )

  // si estamos en contenedor y redis en contenedor
  // redis://redisserv:6379/

  console.log( "conectado ")

  process.on( "SIGINT", function() {
    console.log( " terminando ... " )
    oe.cerrar()
  })

} // main()

// ------------------------------------------------------------
// ------------------------------------------------------------
main()
// ------------------------------------------------------------
// ------------------------------------------------------------
