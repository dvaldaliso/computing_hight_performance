function C = prodMatrizFila(A,B)
    [m,n] = size(A);
    [p,q] = size(B);
    assert(n == p, 'Las matrices no son compatibles');
    C = zeros(m, q);
    for i=1:m
        for j=1:q
            for k=1:n
                C(i,j) = C(i,j) + A(i,k) * B(k,j);
            end
        end
    end
end