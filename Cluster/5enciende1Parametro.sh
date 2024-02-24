PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos
numeroMaquina=$1

{ printf "$USER\n$PASS\n1\n$numeroMaquina\n1\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU