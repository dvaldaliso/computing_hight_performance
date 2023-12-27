
// ....................................................
// este cliente envía de golpe todos los mensajes al servidor
// (no debería hacerse así)
// ....................................................

import ClientController from "./controller/clientController.js";
function main(){
	new ClientController("tcp://localhost","5555","david")
}
main()




