# Ejecucion
## Para ejecutar el tutorial tenemos que hacerlo en algún ordenador que tenga instalado el paquete oneApi de Intel 
## Ejecutamos -> source /opt/intel/oneapi/setvars.sh
## Pasamos a compilar
## Compilar -> icc -O1 -std=c99 -DNOFUNCCALL Multiply.c Driver.c -o MatVector
## ejecutar -> ./MatVector

# Generar informes
## Compilar -> icc -std=c99 -O2 -D NOFUNCCALL -qopt-report=1 -qopt-report-phase=vec Multiply.c Driver.c -o MatVector