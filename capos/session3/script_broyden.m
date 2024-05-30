x0(1)=50;
x0(2)=23;
x0(3)=16;
x0(4)=7;
x0=x0(:)
B = difjacn('f_sistema',x0);
s0 = f_sistema(x0)
for i=1:20
    x1 = x0-B\s0;
    s1=f_sistema(x1);
    v=(x1-x0);

    B=B+(s1*v')/(v'*v);
    norm(s1)
    x0=x1;
    s0=s1
end    
disp('solucion')
x0
    