function [x0,iter] =mini_ejes_metodo_powell(fun,x0)
[m,n]=size(x0);
dir=eye(m);%Matriz identidad:matriz de direcciones
fin=0;
iter=0;
while(fin==0)
 iter=iter+1;
 x=x0;
 for i=1:m
     f=@(alfa) feval(fun,x+alfa*dir(:,i)); %funcion anónima auxiliar unidimensional
     alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
     x=x+alfa_b*dir(:,i);
 end
 for i=1:m-1
     dir(:,i)=dir(:,i+1);
 end    
 dir(:,m)=x-x0;
 f=@(alfa) feval(fun,x+alfa*dir(:,m)); %funcion anónima auxiliar unidimensional
 alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
 x1=x+alfa_b*dir(:,m);
 if norm(x1-x0)<1e-5
     fin=1;
 end    
 x0=x1;    
end    
end

% test pag 25 session 4
% [x,iter] = mini_ejes_metodo_powell('function_min',x0)
