% Realizamos una función caja que dada una matriz A, una partición de sus filas y una partición de sus columnas,
% devuelva la caja i, j:
function C = block(A, M, N, i, j)
    [dm, hm] = desdehasta(M, i);
    [dn, hn] = desdehasta(N, j);
    C = A(dm:hm, dn:hn);
end