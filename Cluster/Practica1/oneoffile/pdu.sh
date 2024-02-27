#!/bin/bash

if [ $# -lt 2 ]; then
echo "Error: faltan parametros"
echo "$0 [-1|-2] -a -n x -f x -t x"  
exit
fi

# defaults
ALL=0

# process arguments

while  [ $# -ge 1 ]
do
	case $1 in 
		-1) ACTION="ON" ;;
		-2) ACTION="OFF" ;;
		-a) ALL=1 ;;
		-n) NUM=$2 ; shift ;;
		-f) FROM=$2 ; shift ;;
		-t) TO=$2 ; shift ;;
		*) break ;;
	esac
	shift
done

echo $0
echo "Argumentos"
echo ACTION $ACTION
echo ALL $ALL
echo NUM $NUM
echo FROM $FROM
echo TO $TO


