% Realizamos una función particion que dado un número natural1 (que será en su momento el número de filas o
% columnas de una matriz) nos devuelva un vector aleatorio de números naturales tal que su suma sea el número
% original. Para ello, inicializamos la variable disponibles al número original y vamos seleccionando un número aleatorio
% menor o igual a disponibles. Cuando ya no queden más, terminamos de realizar la particion.
function v = particion(m)
    disponibles = m;
    v = [];
    while (disponibles >= 1)
        n = randi(disponibles);
        v = [v, n];
        disponibles = disponibles - n;
    end
    assert(sum(v) == m);
end