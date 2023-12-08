%Realizamos una función desdehasta que dada una partición, devuelva donde empieza y donde acaba el elemento
%k-ésimo de la partición. Por ejemplo, si tenemos la partición  [10, 12, 13, 24] de 59, la primer elemento va desde el 1
%hasta el 10; el segundo desde el 11 hasta el 22; el tercero desde el 23 hasta el 35; y el cuarto desde 36 hasta 59:
function [d,h] = desdehasta(v, k)
    w = cumsum([0, v]);
    d = w(k) + 1;
    h = w(k+1);
end