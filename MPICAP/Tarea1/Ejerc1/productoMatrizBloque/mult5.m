%Version 2
% Por cajas Al multiplicar dos matrices por cajas, hay que dividir cada una de las matrices en una retícula rectangular
% de submatrices. Si queremos calular C “ AB donde A pertenece Rmˆn y B pertenece Rnˆq , de lo que nos tenemos que asegurar es de
% que la división de las n columnas de A coincida con la división de las n filas de B. Así por ejemplo, si n “ 11, podríamos
% dividir A verticalmente en 2 bloques de 8 y 3 columnas, o en 2 bloques de 6 y 5 o en 3 bloques de 2, 3 y 6 columnas, etc.
% Esta misma división de columnas que hagamos sobre A la debemos hacer sobre las filas de B. En cuanto a las filas de
% A, las podemos dividir como queramos siempre y cuando los bloques tengan al menos una fila y entre todos los bloques
% tengamos las m filas. Independientemente, las columnas de B se pueden dividir como queramos siempre y cuando cada
% bloque tenga al menos una columna y entre todos los bloques sumen las q columnas. Por supuesto, el orden de las filas
% y columnas originales deben respetarse y no intercambiarse

% Realizamos una funcion mult5 que dadas dos matrices A y B, calcule C “ AB realizando particiones aleatorias de
% las filas de A, una partición aleatoria común para las columnas de A y las filas de B y una partición aleatoria de las
% columnas de B. A continuación, calcula la matriz por cajas multiplicando las particiones anteriores de forma similar
% a como hicimos con la primera forma de multiplicar matrices, salvo que ahora, en vez de ir multiplicando escalares
% vamos multiplicando cajas:
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