A=[3,1,2,6;4,5,6,3;1,8,1,2;5,9,5,5]
[m,n] = size(A);

for j = 1:n
     col=A(:, j);
     if j-1 ~= 0
        pos=j-1 ;
        col(1:pos) = 0;
     end
     pj = norm(col);
     v = col;
     v(j,1) = pj + A(j, j);
     t = transpose(v);
     Bj = (t * v)/2;
    for k = j:n
       [yjk] = fact(j, k, A, v, m, Bj);
       [a]=cmod(j, k, yjk, A, v, m);
       A=a;
       %cmod
    end    
end

% Resolver el sistema triangular superior
C = A
for j = n:-1:1
    xj = C(:, j)/A(j, j)
    for i = 1:j-1
        C(i,:) = C(i,:) - A(i,j)*xj(j)
    end    
end    

% Factor
function [yjk] = fact(j, k, A, v, m, Bj)
    % Factor
    sum = 0;
    for i=j:m
        tem = v(i) * A(i,k);
        sum = sum + tem;
    end
   yjk = sum/Bj;
end

%Cmod
function [A] = cmod(j, k, yjk, A, v, m)
    for i = j:m
        A(i, k) = A(i, k) - yjk * v(i) 
    end
end