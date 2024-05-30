function [y] = min_ejes(fun,x0)
n = length(x0)
D = eye(n);

for i=10
col = mod(i,2)+1
f = @(alfa)feval(fun, x0+alfa*D(:,col));
z=fminsearch(f,0);
x0=x0+z*D(:,col)

end

end

%test
%min_ejes('funp',[8;2])