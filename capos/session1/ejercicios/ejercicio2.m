[x,y] = ginput;
plot(x,y,"*");
hold on

axis([0 1 0 1])
M = [];

grado = 2;
for i=0:grado
    M=[x.^i,M];
end

[Q,R] = qr(M);
sol=R\(Q' * y);
xp = 0:0.01:1; 
yp = polyval(sol,xp);
plot(xp,yp)
