function [ f ] = f_sistema( x )
%p2=x(1), Q=x(2), Q_1=x(3), Q_2=x(4)
f(1)=2.35*exp(-3)*((x(2)).^1.75)-75+x(1);
f(2)=4.67*exp(-3)*(x(3).^1.75)+20-x(1);
f(3)=3.72*exp(-2)*(x(4).^1.75)+15-x(1);
f(4)=x(2)-x(3)-x(4);
f=f(:); %esto los transforma a columna


end

