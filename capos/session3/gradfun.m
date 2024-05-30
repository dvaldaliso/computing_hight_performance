function gr=gradfun(fun,p)
y1=feval(fun,p);
h=sqrt(eps);
gr=p;
for i=1:length(p)
   paux=p;
   paux(i)=paux(i)+h*paux(i);
   gr(i)=(feval(fun,paux)-y1)/(h*paux(i));
end