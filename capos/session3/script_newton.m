x0(1)=50;
x0(2)=23;
x0(3)=16;
x0(4)=7;
x0=x0(:)

for i=1:5
    z=f_sistema(x0);
    M=difjacn('f_sistema',x0);
    [L,U]=lu(M);
    y=L\(-z);
    s=U\y
    norm(s)
    x1=x0+s;
    x0=x1;
end    
disp('solucion')
x0
    