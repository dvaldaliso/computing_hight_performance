%Version 2
%Realizamos una funcion mult5 que dadas dos matrices A y B, calcule C “ AB realizando particiones aleatorias de
%las filas de A, una partición aleatoria común para las columnas de A y las filas de B y una partición aleatoria de las
%columnas de B. A continuación, calcula la matriz por cajas multiplicando las particiones anteriores de forma similar
%a como hicimos con la primera forma de multiplicar matrices, salvo que ahora, en vez de ir multiplicando escalares
%vamos multiplicando cajas:
%function C = mult5(A, B)
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