% Otra forma de calcular la multiplicación C  AB componente a componente es calculando mq productos internos
% (de una columna por una fila). Utilizando una notación1
% similar a la de matlab:
% cij  ai,: ˚ b:,j, i “ 1, . . . , m; j “ 1, . . . , q;
%
function C = prodMatrizColumna(A,B)
    [m,n] = size(A);
    [p,q] = size(B);
    assert(n == p, 'Las matrices no son compatibles');
    C = zeros(m, q);
    for j=1:q
        for i=1:m
            C(i,j) = A(i,:) * B(:,j);
        end
    end
end