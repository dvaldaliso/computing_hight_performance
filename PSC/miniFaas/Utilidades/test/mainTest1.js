
// ------------------------------------------------------------
// ------------------------------------------------------------
async function main() {


  var Utilidades = require( "../Utilidades.js" )

  //await Utilidades.async_timeout( 3000 )

  var res1 = await Utilidades.ejecutar_textoFuncion( 
    "function prueba( obj ) { return obj.a + obj.b  }",
    { a: 8, b: 7 })

  console.log( res1 )

  res2 = await Utilidades.ejecutar_textoFuncion( `function prueba( obj ) {  
    return new Promise( function( resolver, rechazar) { 
      setTimeout( function() {
        resolver( obj.a + obj.b )
      }, 3000)
    }) }`, 
    { a: 88, b: 77 })

  console.log( res2 )

  res3 = await Utilidades.ejecutar_textoPrograma( `
    function foo( a ) {  
       return 2*a
    }
    function bar( a ) {
      return foo( a * a )
    } 
    
    // main
    return bar( input ) `, 
    3 )

  console.log( res3 )
    
}

// ------------------------------------------------------------
// ------------------------------------------------------------
main()
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
