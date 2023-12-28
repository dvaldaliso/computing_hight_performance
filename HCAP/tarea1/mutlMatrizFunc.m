
function C = multiplicarMatrices(A, B)
    [m, n] = size(A);
    [~, p] = size(B);
    C = zeros(m, p);
    for k = 1:n
        for i = 1:m
            for j = 1:p
                C(i, j) = C(i, j) + A(i, k) * B(k, j);
            end
        end
    end
end