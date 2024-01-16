% Enfoque 1: [Q,R,P]= qr(A,0); x= P*( R\Q'*b).
% Para 32x32
%  data = load("mat_rango_32.mat"); % Matriz de 32x32. 
%  data2 = load("vectore_32.mat"); % Vector de 32 elementos.
%  A1 = data.Matrices(1,1); % Para matriz 32x32. 
%  A2 = data.Matrices(1,2); % Para matriz 32x32. 
%  B1 = data2.Vectores(1,1);% Para vector con 32 elementos.
%  B2 = data2.Vectores(1,2); % Para vector con 32 elementos.
%  A11=A1{1}; % Para matriz 32x32
%  B11= B1{1}; % Para vector con 32 elementos

% Para 128x128
data = load("Sistema128x30.mat"); % Matriz 128x218
data2 = load("Sistema128x30.mat"); % Vector de 128 elementos
A12 = data.A; % Para matriz 128x128
B12 = data2.b; % Para vector de 128 elementos

% Para 256x256
% data = load("A256_30.mat"); % Matriz 256x256
% data2 = load("b256_30.mat"); % Vector de 256 elementos
% A1 = data.A; % Para matriz 256x256
% B1 = data2.b; % Para vector de 256 elementos
 tic;
%   [Q, R, P] = qr(A11, 0); % Para 32
  [Q, R, P] = qr(A12, B12); % Para 128
%  [Q, R, P] = qr(A1, B1); % Para 256

% x1 = P*(R \ (Q'*B11)); % Para 32
  x1 = P*(R \ (Q.*B12)); % Para 128
  x1 = P*(R \ (Q.*B1)); % Para 256
 time1 = toc;
 whos
 fprintf('Tiempo usando qr(A,0): %f segundos\n', time1);
clear all;