%Version 2
function C = mult5(A, B)
    [m, n, q] = check(A, B);
    M = particion(m)
    N = particion(n)
    Q = particion(q)
    C = zeros(m, q);
    for i=1:length(M)
        for j=1:length(Q)
            c = zeros(M(i), Q(j));
            for k=1:length(N)
                a = block(A, M, N, i, k);
                b = block(B, N, Q, k, j);
                c = c + a*b;
            end
            [dm, hm] = desdehasta(M, i);
            [dn, hn] = desdehasta(Q, j);
            C(dm:hm, dn:hn) = c;
        end
    end
end