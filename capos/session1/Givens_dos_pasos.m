A=rand(6)
Aaux=A;
Q=eye(6)
%primera rotacion, con los dos ultimos elementos de la primera columna
[c,s]=givens(A(5,1),A(6,1))
A=appl_givens_f(A,5,6,c,s) % la aplicamos a las filas 5 y 6 de A
pause
Q=appl_givens_c(Q,5,6,c,s) % la aplicamos a las columnas 5 y 6 de Q
pause
%segunda rotacion, con el ultimo y penultimo elemento de la primera columna
[c,s]=givens(A(4,1),A(5,1))
A=appl_givens_f(A,4,5,c,s) % la aplicamos a las filas 4 y 5 de A
pause
Q=appl_givens_c(Q,4,5,c,s) % la aplicamos a las columnas 4 y 5 de Q



