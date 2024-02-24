PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos
numeroMaquina=$1
NUMBER_NODOS=8
i=1

while [ $i -le $NUMBER_NODOS ]
do
 { printf "$USER\n$PASS\n1\n$i\n1\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
 i=$(( i+1 ))
done