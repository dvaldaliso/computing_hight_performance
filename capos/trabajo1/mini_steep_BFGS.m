function [x0,iter] =mini_steep_BFGS(fun,x0)
[m,n]=size(x0);

B=eye(m);
fx0 = feval(fun,x0); 
gfx0=gradfun(fun,x0);

fin=0;
iter=0;
while(fin==0)
 iter=iter+1;
 d = B\(-gfx0);

 f=@(alfa) feval(fun,x0+alfa*d); %funcion an�nima auxiliar unidimensional
 alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
 x1=x0+alfa_b*d;
 
 fx1 = feval(fun,x1); 
 gfx1=gradfun(fun,x1);   

 s = x1-x0;
 y = gfx1-gfx0;
 M = -(B*s*s'*B)./(s'*B*s);
 T = (y*y')./(y'*s);
 B=B+M+T;


 if norm(x1-x0)<1e-5
     fin=1;
 end    
 x0=x1;
 fx0=fx1;
 gfx0=gfx1;    
end    
end

% test pagina 38 session 4 este esta bien
% [x,iter] = mini_steep_BFGS('function_min',x0)

