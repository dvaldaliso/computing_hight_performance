PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos

accion=$1
salida=$2
nodo=$3

case $accion in
    1)
        { printf "$USER\n$PASS\n1\n$salida\n1\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
    ;;
    2)
        { printf "$USER\n$PASS\n1\n$salida\n2\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
    ;;
esac

case $salida in

    a)
       { printf "$USER\n$PASS\n1\n9\n$accion\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU 
    ;;
    "n $nodo")
        { printf "$USER\n$PASS\n1\n$nodo\n$accion\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
    ;;
    "f $nodo")
        { printf "$USER\n$PASS\n1\n9\n$accion\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
    ;;
    "t $nodo")
        { printf "$USER\n$PASS\n1\n9\n$accion\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
esac