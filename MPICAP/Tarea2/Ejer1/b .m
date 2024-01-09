data = load("SistemasResolucin32/mat_rango_32.mat")
data2 = load("SistemasResolucin32/vectore_32.mat")
data3 = load("SistemasResolucin32/IMref32.mat")
A1 = data.Matrices(1,1) 
A2 = data.Matrices(1,2)
B1 = data2.Vectores(1,1)
B2 = data2.Vectores(1,2)

A13 = A1{1}


%disp(matrize11)
%x = matrize11 / matrize12
%load west0479
%A = west0479;
%b = transpose(ones(1,length(A))) ;

%AT*AX = AT*B

xX = (A.' * A) \ (A.' * b);