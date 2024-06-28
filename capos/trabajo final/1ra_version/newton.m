x0 = ones(6, 1);


f_sistema = 'f_sistema';
z = feval(f_sistema, x0);
tol = 1e-5;
norm(z);

while norm(z) > tol
    A = difjacn(f_sistema, x0);
    %z = feval(f_sistema, x0);
    [L,U]=lu(A)

    y = L\(-z);
    s = U\y;
    x0 = x0 + s;
    z = feval(f_sistema, x0);
    norm(z)
end