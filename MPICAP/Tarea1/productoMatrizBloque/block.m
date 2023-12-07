%funcion que crea los bloques
function C = block(A, M, N, i, j)
    [dm, hm] = desdehasta(M, i);
    [dn, hn] = desdehasta(N, j);
    C = A(dm:hm, dn:hn);
end