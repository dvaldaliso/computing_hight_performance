function [y] = min_steep(fun,x0)
n = length(x0)

for i=10
p = gradfun(fun,x0)
f = @(alfa)feval(fun, x0+alfa*p);
z = fminsearch(f,0);
x0 = x0+z*p

end

end

%test
% [x,iter] = min_steep('function_min',x0)