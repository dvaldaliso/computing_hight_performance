
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
const REDIS_URL = "redis://localhost:6379/" 

// ------------------------------------------------------------
// ------------------------------------------------------------
const OE = require( "./ObservadorEncargos.js" )
const CE = require( "./ConsultasEncargos.js" )

// ------------------------------------------------------------
// ------------------------------------------------------------
async function main() {

	var redisURL = ( process.argv[2] ? process.argv[2] : REDIS_URL )

	console.log( "*-------------------------------------")
	console.log( "* mainObservador.js " + redisURL )
	console.log( "*-------------------------------------")

	const ce = await new CE.ConsultasEncargos( redisURL )

	const informar = async function () {
		console.log( " encargos totales " + await ce.cuantos_encargos()) 
		console.log( " resultados totales " + await ce.cuantos_resultados()) 
		console.log( " encargos pendientes " +  await ce.cuantos_encargos_pendientes())
	}

	const oe = await new OE.ObservadorEncargos( 
		redisURL ,
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
