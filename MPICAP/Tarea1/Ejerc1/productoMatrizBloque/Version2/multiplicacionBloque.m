function result = matrixMultiplyBloques(A, B, blockSize)
    [m, nA] = size(A);
    [p, nB] = size(B);

    if nA ~= p
        error('Matrix dimensions do not match for multiplication.');
    end

    result = zeros(m, nB);

    for i = 1:blockSize:m
        for j = 1:blockSize:nB
            i_end = min(i + blockSize - 1, m);
            j_end = min(j + blockSize - 1, nB);

            for k = 1:blockSize:p
                result(i:i_end, j:j_end) = result(i:i_end, j:j_end) + ...
                    A(i:i_end, k:min(k + blockSize - 1, nA)) * B(k:min(k + blockSize - 1, p), j:j_end);
            end
        end
    end
end