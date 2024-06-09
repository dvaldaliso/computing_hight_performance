function [x0,iter] =mini_ejes(fun,x0)
[m,n]=size(x0);
direc=eye(m);%Matriz identidad:matriz de direcciones
ind_c=1;
fin=0;
iter=0;
while(fin==0)
 iter=iter+1;
 ind_c=mod(iter,m)+1;%seleccion de direccion, la columna ind_c
 pk=direc(:,ind_c); 
 f=@(alfa) feval(fun,x0+alfa*pk); %funcion anonima auxiliar unidimensional
 alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
 x1=x0+alfa_b*pk;
 if norm(x1-x0)<1e-6
     fin=1;
 end    
 x0=x1;    
end    
end

% test
% [x,iter] = mini_ejes('function_min',x0)


