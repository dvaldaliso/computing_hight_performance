% 
% data = load("Documentos/SistemasResolucin32/mat_rango_32.mat")
% data2 = load("Documentos/SistemasResolucin32/vectore_32.mat")
% data3 = load("Documentos/SistemasResolucin32/IMref32.mat")
% A1 = data.Matrices(1,1) 
% A2 = data.Matrices(1,2)
% B1 = data2.Vectores(1,1)
% B2 = data2.Vectores(1,2)
 
% A11=A1{1}
% b11= B1{1}
% A = [A11 b11]

% Datos de la diapositiva 38, para comprobar que el algoritmo va bien que funciona bien.
% A=[3,1,2;4,5,6,;1,8,1;5,9,5]
% b=[6;3;2;5]
% [m,n] = size(A); 
% A=[A,b]
 
load west0479
A = west0479;
b= A* ones(length(A),1);
[m,n] = size(A);  
A = [A, b];
tic;
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
    for k = j:n+1
       [yjk] = fact(j, k, A, v, m, Bj);
       [a]=cmod(j, k, yjk, A, v, m);
       A=a;
       %cmod
    end    
end

% Resolver el sistema triangular superior

C=A(:,n+1);
%x = resolverTriangularSuperior(A, C,m,n)
x = resolverTriangularSuperiorFila(A, C,m,n)

tiempo_house_holder = toc;
fprintf('Metodo house holder: %f segundos\n', tiempo_house_holder);
 Erx2=norm(x-ones(m,1))/norm(x)%p



%Auxiliar
function [yjk] = fact(j, k, A, v, m, Bj)
    % Factor
    sum = 0;
    for i=j:m
        tem = v(i) * A(i,k);
        sum = sum + tem;
    end
   yjk = sum/Bj;
end

function [A] = cmod(j, k, yjk, A, v, m)
    for i = j:m
        A(i, k) = A(i, k) - yjk * v(i); 
    end
end

function x = resolverTriangularSuperior(A, C,m,n)
   x = zeros(n, 1);
   for j=n:-1:1
    x(j) = C(j)/A(j,j);
    for i=1:j-1
        C(i,:) = C(i,:)-A(i,j)*x(j);
    end
   end    
   
end

function x = resolverTriangularSuperiorFila(A, b,m,n)
 x = zeros(n, 1);  
 x(n) = b(n)/A(n,n);
   for j=n-1:-1:1
    x(j) = b(j);
    for i=j+1:n
        x(j) = x(j) - A(j,i)*x(i);
    end
    x(j) = x(j)/A(j,j);
   end    
   
end