function [c,s]=QR_givens(A)

[m,n] = size(A);
Q=eye(m);

for j=1:n
    for i=m:-1:j+1
        [c,s] = givens(A( i-1, j), A(i, j))
        A = appl_givens_f(A, i-1, i, c, s)
        Q = appl_givens_c(Q, i-1, i, c, s)
    end
end
R=A
end