data = load("SistemasResolucin32/mat_rango_32.mat")
data2 = load("SistemasResolucin32/vectore_32.mat")
data3 = load("SistemasResolucin32/IMref32.mat")
A1 = data.Matrices(1,1) 
A2 = data.Matrices(1,2)
B1 = data2.Vectores(1,1)
B2 = data2.Vectores(1,2)

A13 = A1{1}

%AT*AX = AT*B

x = (A.' * A) \ (A.' * b);