% Enfoque 2: [c,R,P] = qr(A,b); x= P*( R\c).
% Para 32x32
% data = load("mat_rango_32.mat"); % Matriz de 32x32. 
% data2 = load("vectore_32.mat"); % Vector de 32 elementos. 
% A1 = data.Matrices(1,1); % Para matriz 32x32. 
% A2 = data.Matrices(1,2); % Para matriz 32x32. 
% B1 = data2.Vectores(1,1);% Para vector con 32 elementos. 
% B2 = data2.Vectores(1,2); % Para vector con 32 elementos. 
% A11=A1{1}; % Para matriz 32x32
% B11= B1{1}; % Para vector con 32 elementos
% tic;
% [c, R, P] = qr(A11, B11); % Para la saga de 32
% x2 = P * (R \ c);
% time2 = toc;
% whos 
% % Mostrar los tiempos de cómputo
% fprintf('Tiempo usando qr(A,b): %f segundos\n', time2);

% Para 128x128
data = load("Sistema128x30.mat"); % Matriz 128x128. 
data2 = load("Sistema128x30.mat"); % Vector de 128 elementos. 
A12 = data.A; % Para matriz 128x128
B12 = data2.b; % Para vector de 128 elementos
tic;
[c, R, P] = qr(A12, B12); 
x2 = P * (R \ c);
time2 = toc;
whos 
% Mostrar los tiempos de cómputo
fprintf('Tiempo usando qr(A,b): %f segundos\n', time2);

% Para 256x256
% data = load("A256_30.mat"); % Matriz 256x256. 
% data2 = load("b256_30.mat"); % Vector de 256 elementos.
% A1 = data.A; % Para matriz 256x256
% B1 = data2.b; % Para vector de 256 elementos
% tic;
% [c, R, P] = qr(A1, B1); 
% x2 = P * (R \ c);
% time2 = toc;
% whos 
% % Mostrar los tiempos de cómputo
% fprintf('Tiempo usando qr(A,b): %f segundos\n', time2);
clear all;

