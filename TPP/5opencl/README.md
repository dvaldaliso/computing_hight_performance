ssh tpp1_dvallop@nowherman.iteam.upv.es

## OPencl -> permite programar en cpu y gpu(programacion heterogenea) mut flexible
## thread equivalente work-item
## thread block equivalente work-group

## vio.lo = toma la mitad del vector hacia 0
## vio.hi = toma la mitad del vector hacia lenght

## ejercicio 4 
## ./mult 1024 8 --list
## ./mult 1024 8 --device 1
## cada work item ejectura un kernel
## badia@vji.es