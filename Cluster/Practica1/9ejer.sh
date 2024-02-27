#!/bin/bash

if [ $# -lt 2 ]; then
echo "Error: faltan parametros"
echo "$0 [-1|-2] -a -n x -f x -t x"  
exit
fi
#defaults
PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos
All=0

# while getopts ${OPTSTRING} opcion;

while [ $# -ge 1 ]
do
    case $1 in
        -1) ACTION=1 ;;
        -2) ACTION=2 ;;
        -a) All=1 ;;
        -n) NumNodo=$2 ; shift ;;
        -f) from=$2 ; shift ;;
        -t) to=$2; shift ;;
        *) break ;;
    esac
    shift
done

echo $0
echo "Argumentos"
echo ACTION $ACTION
echo ALL $All
echo NUM $NumNodo
echo FROM $from
echo TO $to

if [ -n "$All"  ] # chequea si esta definida y no esta vacia
then
echo "encender todas = true"
 { printf "$USER\n$PASS\n1\n9\n$ACTION\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
fi


if [ -v NumNodo ] # chequea si esta definida
then
 echo "encender un nodo"
 { printf "$USER\n$PASS\n1\n$NumNodo\n$ACTION\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
fi

if [ -v from ] || [ -v to ] # chequea si estan definidas
then
    echo "enceder rango"
    while [ "$from" -le "$to" ]
    do
        { printf "$USER\n$PASS\n1\n$from\n$ACTION\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU
        from=$(( from + 1 ))
    done
fi

