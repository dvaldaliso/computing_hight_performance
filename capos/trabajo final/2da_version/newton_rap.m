function [x, lambda] = newton_rp(A, x0, lambda0)

    tol = 1e-5;
    x = x0;
    lambda = lambda0;
    n = length(x0);
    I = eye(n);
    fin = 0;

    while fin == 0
        
        F = A * x - lambda * x;
        Jx = A - lambda * I;
        Jlambda = -x;
        J = [Jx, Jlambda];

        delta = J \ -F;
        
        x = x + delta(1:n);
        lambda = lambda + delta(n+1);

        x = x / norm(x);
        
        if norm(F) <= tol
            fin = 1;
            return
        end
    end
end