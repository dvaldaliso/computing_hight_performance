% Para matriz 32x32 y vector con 32 elementos
% data = load("mat_rango_32.mat"); % Matriz de 32x32. 
% data2 = load("vectore_32.mat"); % Vector de 32 elementos. 
% A1 = data.Matrices(1,1);  
% A2 = data.Matrices(1,2);  
% B1 = data2.Vectores(1,1);
% B2 = data2.Vectores(1,2); 
% A11=A1{1}; % Para matriz 32x32
% B11= B1{1}; % Para vector con 32 elementos

% % Método 1
% tic;
% [Q, R] = qr(A11);
% x = R \ (Q' * B11);
% tiempo_metodo_1 = toc;
% fprintf('Metodo 1: %f segundos\n', tiempo_metodo_1);

% % Método 2. ESTE METODO FUNCIONA
% tic;
% [Q, R] = qr(A11, 0);
% x = R \ (Q' * B11);
% tiempo_metodo_2 = toc;
% fprintf('Metodo 2: %f segundos\n', tiempo_metodo_2);

% 
% % Método 3. ESTE METODO FUNCIONA
% tic;
% [c, R] = qr(A11, B11);
% x = R \ c;
% tiempo_metodo_3 = toc;
% fprintf('Metodo 3: %f segundos\n', tiempo_metodo_3);
% 
% % Método 4 ESTE METODO FUNCIONA
% tic;
% [c, R, P] = qr(A11, B11);
% x = P * (R \ c);
% tiempo_metodo_4 = toc;
% fprintf('Metodo 4: %f segundos\n', tiempo_metodo_4);

% % Para matriz 128x128 y vector con 128 elementos
% data = load("Sistema128x30.mat"); % Matriz 128x128. 
% data2 = load("Sistema128x30.mat"); % Vector de 128 elementos. 
% A12 = data.A; % Para matriz 128x128.
% B12 = data2.b; % Para vector de 128 elementos.

% % Método 1
% tic;
% [Q, R] = qr(A12);
% x = R \ (Q' * B12);
% tiempo_metodo_1 = toc;
% fprintf('Metodo 1: %f segundos\n', tiempo_metodo_1);

% % Método 2. ESTE METODO FUNCIONA
% tic;
% [Q, R] = qr(A12, 0);
% x = R \ (Q' * B12);
% tiempo_metodo_2 = toc;
% fprintf('Metodo 2: %f segundos\n', tiempo_metodo_2);

% 
% % Método 3. ESTE METODO FUNCIONA
% tic;
% [c, R] = qr(A12, B12);
% x = R \ c;
% tiempo_metodo_3 = toc;
% fprintf('Metodo 3: %f segundos\n', tiempo_metodo_3);
% 
% % Método 4 ESTE METODO FUNCIONA
% tic;
% [c, R, P] = qr(A12, B12);
% x = P * (R \ c);
% tiempo_metodo_4 = toc;
% fprintf('Metodo 4: %f segundos\n', tiempo_metodo_4);

% % Para matriz 256x256 y un vector de 256 elementos
data = load("A256_30.mat"); % Matriz 256x256. 
data2 = load("b256_30.mat"); % Vector de 256 elementos. 
A1 = data.A; % Para matriz 256x256
B1 = data2.b; % Para vector de 256 elementos
% % Método 1
% tic;
% [Q, R] = qr(A1);
% x = R \ (Q' * B1);
% tiempo_metodo_1 = toc;
% fprintf('Metodo 1: %f segundos\n', tiempo_metodo_1);

% % Método 2. ESTE METODO FUNCIONA
% tic;
% [Q, R] = qr(A1, 0);
% x = R \ (Q' * B1);
% tiempo_metodo_2 = toc;
% fprintf('Metodo 2: %f segundos\n', tiempo_metodo_2);

% 
% % Método 3. ESTE METODO FUNCIONA
% tic;
% [c, R] = qr(A1, B1);
% x = R \ c;
% tiempo_metodo_3 = toc;
% fprintf('Metodo 3: %f segundos\n', tiempo_metodo_3);
% 
% Método 4 ESTE METODO FUNCIONA
tic;
[c, R, P] = qr(A1, B1);
x = P * (R \ c);
tiempo_metodo_4 = toc;
fprintf('Metodo 4: %f segundos\n', tiempo_metodo_4);


