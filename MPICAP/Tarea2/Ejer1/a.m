data = load("SistemasResolucin32/mat_rango_32.mat")
data2 = load("SistemasResolucin32/vectore_32.mat")
data3 = load("SistemasResolucin32/IMref32.mat")
A1 = data.Matrices(1,1) 
A2 = data.Matrices(1,2)
B1 = data2.Vectores(1,1)
B2 = data2.Vectores(1,2)

A11=A1{1}
b11= B1{1}

tic;
x = A11\b11;
time1=toc;
fprintf('Tiempo usando x2: %f segundos\n', time1);
%figure, spy(x)


tic;
x2 = (A11.' * A11) \ (A11.' * b11);
time2=toc;
fprintf('Tiempo usando x: %f segundos\n', time2);
%dim=sqrt(length(x2));  % Consideramos un CT de dimensiones cuadradas
%IM=reshape(x2, dim, dim);%Colocamos los datos en forma de matriz de píxeles (imagen)
%figure, imcontrast(imshow(IM)) % Mostramos la imagen con posibilidad de modificar el contraste.


Erx=norm(x-ones(1024,1))/norm(ones(1024,1))
Erx2=norm(x2-ones(1024,1))/norm(ones(1024,1))