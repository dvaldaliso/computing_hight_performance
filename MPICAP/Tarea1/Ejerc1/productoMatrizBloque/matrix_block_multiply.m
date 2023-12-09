%Version 1
function C = matrix_block_multiply(A, B, block_size)
    % Multiplicación de matrices en bloque.

    %obtenermos las dimensiones de las matrices
    [m, n] = size(A);
    [~, p] = size(B);

    %Verificamos que se puedan calcular las matrices
    if n ~= size(B, 1)
        error('Las dimensiones de las matrices no son compatibles para la multiplicación.');
    end

    %Creamos la matriz resultante que vamos a obtener con todo 0
    C = zeros(m, p);
    
    % Dividir las matrices en bloques y realizar la multiplicación
    for i = 1:block_size:m
        for j = 1:block_size:p
            for k = 1:block_size:n
                % Multiplicación de bloques
                block_A = A(i:min(i+block_size-1, m), k:min(k+block_size-1, n));
                block_B = B(k:min(k+block_size-1, n), j:min(j+block_size-1, p));
                C(i:min(i+block_size-1, m), j:min(j+block_size-1, p)) = C(i:min(i+block_size-1, m), j:min(j+block_size-1, p)) + block_A * block_B;
            end
        end
    end
end