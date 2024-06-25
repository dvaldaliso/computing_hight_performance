x0 = ones(1, 6);


f_sistema = 'f_sistema';
z = feval(f_sistema, x0);

norm(z);

for i=1:5
    A = difjacn(f_sistema, x0);
    %z = feval(f_sistema, x0);
    [L,U]=lu(A)

    y = L\(-z);
    s = U\y;
    x0 = x0 + s;
    z = feval(f_sistema, x0);
    norm(z)
end