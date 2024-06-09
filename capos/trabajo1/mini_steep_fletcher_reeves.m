function [x0,iter] =mini_steep_fletcher_reeves(fun,x0)
[m,n]=size(x0);
r0=-gradfun(fun,x0);
p0=r0;
fin=0;
iter=0;
while(fin==0)
 iter=iter+1;
% dir=gradfun(fun,x0); 
 f=@(alfa) feval(fun,x0+alfa*p0); %funcion anónima auxiliar unidimensional
 alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
 x1=x0+alfa_b*p0;
 r1=-gradfun(fun,x1);
 beta=(r1'*r1)./(r0'*r0);
 p1=r1+beta*p0;
 if norm(x1-x0)<1e-5
     fin=1;
 end    
 x0=x1; 
 p0=p1;
 r0=r1;
end    
end


% test pag 25 session 4
% [x,iter] = mini_steep_fletcher_reeves('function_min',x0)

