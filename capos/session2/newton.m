x0(1)=50;
x0(2)=23;
x0(3)=16;
x0(4)=7;
x0=x0(:);

f_sistema = 'f_sistema';
z = feval(f_sistema, x0);

norm(z);

for i=1:5
    A = difjacn(f_sistema, x0);
    [L,U]=lu(A)

    y = L\(-z);
    s = U\y;
    x0 = x0 + s;
    z = feval(f_sistema, x0);
    norm(z)
end