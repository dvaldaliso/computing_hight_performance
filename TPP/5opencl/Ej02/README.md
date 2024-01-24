# el .c se ejecuta en al host
# el .cl se ejecuta en la gpu o device
## en vadd.cl
## int i = get_global_id(0);  //Esto te dice cada wock item, quien es  

### si el codigo del kernel tiene un error, no se ve hasta que ejecute el programa, no cuando lo compile

## dimension global -> cantidad de work-item