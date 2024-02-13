# Ejercicio 1 lsqr
## compilacion -> make lsqr
## ejecucion -> ./lsqr -file A32_30.petsc -fileb b32_30_forbild.petsc -files salidalsqr.m
Con figure;imcontrast(imshow(I)) la puedes visualizar, y con la barra de contraste ir ajustando. Si se ve bien la forma, la imagen está correcta.

También puedes compararla con la que os di de referencia, IMref32.mat, y puedes medir la calidad de la generada con respecto a la de referencia con psnr y ssim.


# Ejercicio 2 svd
## compilacion -> make svd
## ejecucion -> ./svd -file A32_30.petsc -fileb b32_30_forbild.petsc -files salidalsvd.m

## Matlab
## run('salidalsvd.m') -> me da un vector ->Vec_0x55f02bda2500_0
## reshape(Vec_0x55f02bda2500_0, 32,32) -> esto me da una variable llamada 'ans' que se la pasamos debajo
## figure;imcontrast(imshow(ans))