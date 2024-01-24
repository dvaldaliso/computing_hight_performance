# el .c se ejecuta en al cpu
# el .cl se ejecuta en la gpu
en vadd.cl
int i = get_global_id(0);  //Esto te dice cada wock item, quien es  