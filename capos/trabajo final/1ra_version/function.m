A = [4, 1, 2, 1, 0;
    1, 3, 0, 1, 1;
    2, 0, 2, 2, 1;
    1, 1, 2, 3, 2;
    0, 1, 1, 2, 2];
eig(A)    
x0 = ones(5, 1);
lambda0 = 1.0;

La función newton_method busca encontrar un autovalor y un autovector de una matriz simétrica usando el método de Newton.
Toma los siguientes argumentos:
A: La matriz simétrica.
x0: El vector inicial para x (en este caso, un vector de unos).
lambda0: El valor inicial para λ.
tol (opcional): La tolerancia para la convergencia.
max_iter (opcional): El número máximo de iteraciones.


Se calcula 
𝐹(𝑥,𝜆) = 𝐴𝑥−𝜆𝑥

Se construye el Jacobiano 
𝐽 combinando 𝐽𝑥=𝐴−𝜆𝐼 y 𝐽𝜆=−𝑥.

Se resuelve el sistema lineal 
𝐽𝛿=−𝐹 para obtener 𝛿 (cambios en 𝑥 y 𝜆).
Se actualizan 𝑥 y 𝜆.
