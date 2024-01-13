A=[3,1,2,6;4,5,6,3;1,8,1,2;5,9,5,5]
[m,n] = size(A);

for j = 1:n
    ro = norm(A(:,j))
    for k = j:n
        yij = fact(j,k,A,ro,m)
    end    
end

function fact(j, k, A, ro,m)
    % Factor
    v = A(:,j)
    v(j,1)=ro+A(j,k)
    t=v'
    Bj = (v' * v)/2
    yij=0
    for i=j:m
        tem = v(i) * A(i,k)
        yij=yij + tem
    end
    %return yij/Bj
end
