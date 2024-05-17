numero_conos=100000;
D=rand(1,numero_conos)+10;
H=rand(1,numero_conos)+10;
%versión con bucle
tic
V = zeros(1,numero_conos) %Esto no estaba en el codigo original
for n=1:numero_conos
V(n) = (1/12)*pi*(D(n)^2)*H(n);
end
tiempo_bucle=toc
% version vectorizada
tic
Vv=(1/12)*pi*(D.^2).*H;
tiempo_vectorizado=toc