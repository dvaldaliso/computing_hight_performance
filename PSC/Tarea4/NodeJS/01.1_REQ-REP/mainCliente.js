
// ....................................................
// este cliente envía de golpe todos los mensajes al servidor
// (no debería hacerse así)
// ....................................................




import { Chat } from "./util/ChatCliente.js"
 

function main () {
    let nombre = (process.argv[2] ? process.argv[2]  : "noname")
	var chat = new Chat("tcp://localhost:5556", nombre)
}
main()

