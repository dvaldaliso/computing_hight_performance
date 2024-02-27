#! /bin/sh

for i in 1 2 3 4 5 6 7 8
do
 ssh cac$i $1 & #& hace que se ejecuten en parelelo
done

wait  # Espera a que terminen todos los procesos