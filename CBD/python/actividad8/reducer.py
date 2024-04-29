#!/usr/bin/python
import sys

current_resource = None
current_count = 0
max_resource = None
max_count = 0

# Iterar sobre cada línea de entrada
for line in sys.stdin:
    # Dividir la línea en clave y valor usando una tabulación como separador
    resource, _ = line.strip().split('\t')
    
    # Incrementar el contador para el recurso actual
    if current_resource == resource:
        current_count += 1
    else:
        # Actualizar el recurso más popular si el contador actual es mayor
        if current_resource and current_count > max_count:
            max_resource = current_resource
            max_count = current_count
        # Reiniciar para el nuevo recurso
        current_resource = resource
        current_count = 1

# Lidiar con el último recurso
if current_resource and current_count > max_count:
    max_resource = current_resource
    max_count = current_count

# Imprimir el recurso web más popular
print("Recurso web más popular:", max_resource, "con", max_count, "accesos")
