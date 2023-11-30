function C = productoMatrizPorMatriz(A, B)
    [m, r] = size(A);
    [v,n] = size(B);
    
    % Producto matriz por matriz utilizando operaciones vectoriales (versión fila)
    fila = zeros(m, n);
    for i = 1:m
        for j = 1:n
            fila(i, j) = A(i, :) * B(:, j);
        end
    end
    
    % Producto matriz por matriz utilizando operaciones vectoriales (versión columna)
    columna = zeros(m, n);
    for j = 1:n
        for i = 1:m
            columna(i, j) = A(i, :) * B(:, j);
        end
    end
    
    disp('Versión fila:');
    disp(fila);
    
    disp('Versión columna:');
    disp(columna);
end
