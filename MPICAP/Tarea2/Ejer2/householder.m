A=[3,1,2,6;4,5,6,3;1,8,1,2;5,9,5,5]
[m,n] = size(A);

for j = 1:n
     col=A(:, j);
     if j-1 ~= 0
        pos=j-1 ;
        col(1:pos) = 0;
     end
     pj = norm(col);
     v = col;
     v(j,1) = pj + A(j, j);
     t = transpose(v);
     Bj = (t * v)/2;
    for k = j:n
       [yjk] = fact(j, k, A, v, m, Bj);
       [a]=cmod(j, k, yjk, A, v, m);
       A=a;
       %cmod
    end    
end

% Resolver el sistema triangular superior

b = A(:, end) % extraer el vector b
A = A(:, 1:end-1) % dejar solo el lado izquierdo del sistma de ecuaciones
A = A(1:end-1, :); % remover la ulima fila que nos da el residuo
x = resolveUpperTriangular(A, b)


%Utils
function [yjk] = fact(j, k, A, v, m, Bj)
    % Factor
    sum = 0;
    for i=j:m
        tem = v(i) * A(i,k);
        sum = sum + tem;
    end
   yjk = sum/Bj;
end

function [A] = cmod(j, k, yjk, A, v, m)
    for i = j:m
        A(i, k) = A(i, k) - yjk * v(i) 
    end
end

function x = resolveUpperTriangular(A, b)
    [filas, columnas] = size(A);
    
    if filas ~= columnas
        error('La matriz A no es cuadrada.');
    end
    
    x = zeros(filas, 1);
    
    for i = filas:-1:1
        x(i) = (b(i) - A(i, i+1:end) * x(i+1:end)) / A(i, i);
    end
end