%% Tarea 1.- Unidad temática 1
%% EJERCICIO 1.
% Se pretende realizar el producto matriz por matriz, C=A*B donde A∈R^mxr, 
% B∈R^rxn. Implementa un programa en MATLAB que realice dicho cálculo de 
% las siguientes formas:

%% EJERCICIO 2.

% c) Abordar el problema de autovalores ordinario, ecuación 6 del documento 
% aplicacion1-SeguridadReactoresNucleares.pptx de la carpeta 
% Caso de estudio 1.
[V2,D2] = eigs(@(x)productoMethondc(x,L21,L22,L11,M11,M12),219,5)









