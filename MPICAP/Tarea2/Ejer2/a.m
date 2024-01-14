A=[3,1,2,6;4,5,6,3;1,8,1,2;5,9,5,5]
[m,n] = size(A);

for j = 1:n
    pj = norm(A(:, j))
     v = A(:, j);
     v(j,1) = pj + A(j, j);
     t = transpose(v);
     Bj = (t * v)/2;
    for k = j:n
       [yjk]=fact(j, k, A, v, m, Bj)
       cmod(j, k, yjk, A, v, m)
       %cmod
    end    
end

function [yjk] = fact(j, k, A, v, m, Bj)
    % Factor
    sum= 0;
    for i=j:m
        tem = v(i) * A(i,k);
        sum = sum + tem;
    end
   yjk = sum/Bj;
end

function cmod(j, k, yjk, A, v, m)
    for i = j:m
        A(i, k) = A(i, k) - yjk * v(i) 
    end
end

