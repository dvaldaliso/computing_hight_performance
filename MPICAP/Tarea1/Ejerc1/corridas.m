A=rand(100,100);
B=rand(100,100);
%tomar tiempo
matProdCol = @() prodMatrizColumna(A,B);
elapsed_timeColumnaCien = timeit(matProdCol);

matProdFila = @() prodMatrizFila(A,B)
elapsed_timeFilaCien = timeit(matProdFila);

A=rand(500,500);
B=rand(1000,1000);

matProdColQuin = @() prodMatrizColumna(A,B);
elapsed_timeColumnaQuin = timeit(matProdColQuin);

matProdFilaQuin =  @() prodMatrizFila(A,B)
elapsed_timeFilaQuin = timeit(matProdFilQuin);


A=rand(1000,1000);
B=rand(1000,1000);

matProdColMil = @() prodMatrizColumna(A,B);
elapsed_timeColumnaMil = timeit(matProdColMil);

matProdFilaMil =  @() prodMatrizFila(A,B)
elapsed_timeFilaMil = timeit(matProdFilaMil);