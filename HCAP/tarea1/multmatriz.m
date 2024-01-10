A = rand(50,20000);
B = rand (20000,50);

[m, n] = size(A);
[~, p] = size(B);
C = zeros(m, p);
% version ikj
tic
for i=1:m 
    for k=1:n 
        for j=1:p 
            C(i,j)= C(i,j)+A(i,k)*B(k,j); 
        end
    end
end
toc
% version ijk
tic
for i=1:m 
    for j=1:p 
        for k=1:n 
            C(i,j)= C(i,j)+A(i,k)*B(k,j);
        end
    end
end
toc
% version kij
tic
for k=1:n 
    for i=1:m 
        for j=1:p
            C(i,j)= C(i,j)+A(i,k)*B(k,j); 
        end
    end
end
toc
% version kji
tic
for k=1:n 
    for j=1:p 
        for i=1:m
            C(i,j)= C(i,j)+A(i,k)*B(k,j); 
        end
    end
end
toc
% version jki
tic
for j=1:p 
    for k=1:n 
        for i=1:m
            C(i,j)= C(i,j)+A(i,k)*B(k,j); 
        end
    end
end
toc

% version jik
tic
for j=1:p 
    for i=1:m 
        for k=1:n 
            C(i,j)= C(i,j)+A(i,j)*B(k,j);
        end
    end
end
toc