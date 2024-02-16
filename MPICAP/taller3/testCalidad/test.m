run("salidalsqr.m");
run("salidasvd.m");

datos_mat = load('IMref32.mat');
% Acceder a la variable almacenada en la estructura 
 matriz_datos = datos_mat.im; % Asegúrate de que esta variable existe en tu archivo .mat

 lsqr = reshape(Vec_0x55f02bda2500_0, 32, 32);
 svd = reshape(Vec_0x564c96fb5770_0, 32, 32);


 % Calcular PSNR
psnr_valor_lsqr = psnr(lsqr, matriz_datos);
fprintf('El valor de PSNR_lsqr es: %.2f dB\n', psnr_valor_lsqr);

% Calcular SSIM
ssim_valor_lsqr = ssim(lsqr, matriz_datos);
fprintf('El valor de SSIM_lsqr es: %.4f\n', ssim_valor_lsqr);

 % Calcular PSNR
psnr_valor_svd = psnr(svd, matriz_datos);
fprintf('El valor de PSNR_svd es: %.2f dB\n', psnr_valor_svd);

% Calcular SSIM
ssim_valor_svd = ssim(svd, matriz_datos);
fprintf('El valor de SSIM_svd es: %.4f\n', ssim_valor_svd);

% display image lsqr
%figure;imcontrast(imshow(lsqr))
%display image svd
figure;imcontrast(imshow(svd))