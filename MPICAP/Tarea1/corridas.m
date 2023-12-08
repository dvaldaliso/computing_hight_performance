A=rand(10000,10000);
B=rand(10000,10000);
%tomar tiempo
matProdCol = @() prodMatrizColumna(A,B);
elapsed_time = timeit(matProdCol);
disp(matProdCol)