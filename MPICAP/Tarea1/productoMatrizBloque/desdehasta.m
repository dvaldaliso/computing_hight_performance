function [d,h] = desdehasta(v, k)
    w = cumsum([0, v]);
    d = w(k) + 1;
    h = w(k+1);
end