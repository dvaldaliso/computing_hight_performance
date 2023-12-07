%funcion que chequea si estan corectas las matrices
function [m, n, q] = check(A,B)
    [m,n] = size(A);
    [p,q] = size(B);
    assert(n == p, 'Las matrices no son compatibles');
end