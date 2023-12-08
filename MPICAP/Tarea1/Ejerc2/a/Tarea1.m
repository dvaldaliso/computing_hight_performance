%% Tarea 1.- Unidad temática 1
%% EJERCICIO 1.
% Se pretende realizar el producto matriz por matriz, C=A*B donde A∈R^mxr, 
% B∈R^rxn. Implementa un programa en MATLAB que realice dicho cálculo de 
% las siguientes formas:

% a.- Producto matriz por matriz  utilizando operaciones vectoriales, 
% versión fila y columna.
% ESTO LO HE SACADO DE CHATGPT
% Definir matrices A y B
%A = [1, 2; 3, 4; 5, 6];
%B = [7, 8, 9; 10, 11, 12];
A = rand (5);
B = rand (5);

% Calcular el producto matriz por matriz utilizando la función
productoMatrizPorMatriz(A, B);


%% EJERCICIO 2.
% Resuelve el problema de autovalores asociado al caso de estudio 1 para 
% las matrices asociadas al reactor Biblis 
% (Curso 2023/24 \UD1 \Caso de estudio1 \Biblis).
% a) Resuelve el problema de autovalores generalizado:  Ax=λMx para los 
% datos Biblis.
load('biblis2.mat')
spy(A);
whos
% eig --> Calcula vectores y matrices propias, pero densas
spy(B);
%[V,D] = eigs(A,B,5)
% Si lo ponemos asi estaria mal ya que, B mal posicionada y por eso no 
% se puede resolver el problema
[V,D] = eigs (B,A,5);
inv(D)
% El problema hay que resolverlo por bloques, no se puede resolver todo de
% una, asi que vamos poco a poco. Acabamos de calcular la lambda.
spy(L11)
figure, spy(L22)
% norm(full(L11)-full(L22)) Las matrices se convierten de dispesrso a denso
% esto lo hace la funcion full.
figure, spy(L21) % Es un vector unidimensional
figure, spy(diag(L21)) % Vector 219*1, es una matriz pero no almaceno una matriz
whos
figure, spy(diag(M11))
figure, spy(diag(M12))










