function [x0,iter] =mini_steep(fun,x0)
[m,n]=size(x0);
fin=0;
iter=0;
while(fin==0)
 iter=iter+1;
 dir=gradfun(fun,x0); 
 f=@(alfa) feval(fun,x0+alfa*dir); %funcion an�nima auxiliar unidimensional
 alfa_b=fminsearch(f,0); %minimizacion de fun desde x0 a lo largo de pk
 x1=x0+alfa_b*dir;
 if norm(x1-x0)<1e-5
     fin=1;
 end    
 x0=x1;    
end    
end



