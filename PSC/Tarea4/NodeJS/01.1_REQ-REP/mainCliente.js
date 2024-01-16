
// ....................................................
// este cliente envía de golpe todos los mensajes al servidor
// (no debería hacerse así)
// ....................................................

import { Cliente } from "./util/ChatCliente.js"
 
function main () {
    let nombre = (process.argv[2] ? process.argv[2]  : "noname")
	var chat = new Cliente("tcp://localhost:5556", nombre)
}
main()

