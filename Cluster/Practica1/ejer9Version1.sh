#!/bin/bash

PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos
accion=$1
salida=$2
nodo=$3
NUMBER_NODOS=8
apagar_encender=0
numeroMaquina=0
encender_todas=0
from=0
to=0
OPTSTRING="12an:f:t:"
while getopts ${OPTSTRING} opcion;
do
    case ${opcion} in
        1)
        echo "encender"
        apagar_encender=1
        ;;
        2)
        echo "apagar"
        apagar_encender=2
        ;;
        a)
        encender_todas=1
        ;;
        n)
        numeroMaquina="$OPTARG"
        ;;
        f)
        from="$OPTARG"
        ;;
        t)
        to="$OPTARG"
        ;;
    esac
done

echo "${encender_todas}"
if [ $encender_todas -eq 1 ]
then
echo "encender todas = true"
 { printf "$USER\n$PASS\n1\n9\n$apagar_encender\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
fi
echo "$numeroMaquina"
if [ $numeroMaquina -ne 0 ]
then
echo "yeeeeee"
 { printf "$USER\n$PASS\n1\n$numeroMaquina\n$apagar_encender\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
fi
echo "$from y $to"
if [ $from -ne 0 ]
then
while [ $from -le $to ]
do
    { printf "$USER\n$PASS\n1\n$from\n$apagar_encender\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
echo "$from"
     from=$(( from + 1 ))
done
fi
