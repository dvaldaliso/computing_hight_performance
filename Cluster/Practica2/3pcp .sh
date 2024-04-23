#!/bin/bash

# Verificar que se proporcionen los argumentos necesarios
if [ $# -ne 2 ]; then
    echo "Uso: $0 <archivo_a_copiar> <directorio_o_archivo_destino>"
    exit 1
fi

# Definir el nombre del archivo y el destino
archivo_a_copiar="$1"
directorio_o_archivo_destino="$2"

# Lista de nodos restantes
nodos=(cluster2 cluster3 cluster4)

# Copiar el archivo a cada uno de los nodos restantes
for nodo in "${nodos[@]}"; do
    scp "$archivo_a_copiar" "$nodo":"$directorio_o_archivo_destino"
    # $? contiene el estado de salida del último comando ejecutado
    if [ $? -eq 0 ]; then
        echo "Archivo copiado exitosamente a $nodo:$directorio_o_archivo_destino"
    else
        echo "Error al copiar el archivo a $nodo:$directorio_o_archivo_destino"
    fi
done
