axis([-3,3 ,-3,3])
grid
hold on
echo on
x=[1;sqrt(3)]
plot([0,x(1)],[0,x(2)],'b')
pause
th=pi/4;
q=[cos(th),sin(th);-sin(th),cos(th)];
y=q*x;
plot([0,y(1)],[0,y(2)],'g')
pause
y=q*y;
plot([0,y(1)],[0,y(2)],'g')
pause,echo off
disp(' para hacer cero la segunda componente de x, cogemos th=pi/3')
pause,echo on
th=pi/3;
q=[cos(th),sin(th);-sin(th),cos(th)];
y=q*x
pause
plot([0,y(1)],[0,y(2)],'r')
pause
disp(' para hacer cero la primera componente de x, cogemos th=pi/6')
pause
th=-pi/6;
q=[cos(th),sin(th);-sin(th),cos(th)];
y=q*x
pause
plot([0,y(1)],[0,y(2)],'r')