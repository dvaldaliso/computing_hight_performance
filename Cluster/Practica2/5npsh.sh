#!/bin/bash

# npsh -m df
# npsh -f 2 -t 5 “df -h”

if [ $# -lt 2 ]; then
echo "Error: faltan parametros"
echo "$0 [-m|-a] -f x -t x"  
exit
fi

while  [ $# -ge 1 ]
do
	case $1 in 
		-m) MAESTRO=1 ;;
		-a) ALL=1 ;;
		-f) FROM=$2 ; shift ;;
		-t) TO=$2 ; shift ;;
		*) break ;;
	esac
	shift
done

echo $0
echo "Argumentos"
echo MAESTRO $MAESTRO
echo ALL $ALL
echo FROM $FROM
echo TO $TO
last_param="${!#}"

#chequea si esta definida y no esta vacia
if [ -n "$MAESTRO"  ]
then
	echo "maestro $last_param"
	pdsh -w cac1 -R ssh $last_param
fi

#chequea si esta definida y no esta vacia
if [ -n "$ALL"  ]
then
	echo "todos $last_param"
	pdsh -w cac[1-8] -R ssh $last_param
fi

#chequea si estan definidas y no esta vacia
if [ -n "$FROM" ] || [ -n "$TO" ]
then
    echo "rango $last_param"
	pdsh -w cac[$FROM-$TO] -R ssh $last_param
fi