tiemposTabla = table('Size', [0, 4], 'VariableTypes', {'double', 'double', 'double', 'double'}, 'VariableNames', {'Fila', 'Columna', 'TiempoFila', 'TiempoColumna'});

tamaMatrices = [100, 200,400,600,800,1000];

for i = 1:length(tamaMatrices)
    % Generar una matriz de tamaño tamañosMatrices(i) x tamañosMatrices(i)
    size = tamaMatrices(i);
    
    A=rand(size,size);
    B=rand(size,size);
    %tomar tiempo
    
    matProdCol = @() prodMatrizColumna(A,B);
    timeColumna = timeit(matProdCol);
    
    matProdFila = @() prodMatrizFila(A,B)
    timeFil = timeit(matProdFila);


    % Agregar los tiempos medidos a la tabla
    tiemposTabla = [tiemposTabla; table(tamaMatrices(i), tamaMatrices(i), timeFil, timeColumna, 'VariableNames', {'Fila', 'Columna', 'TiempoFila', 'TiempoColumna'})];
end






tiemposTablaBloc = table('Size', [0, 3], 'VariableTypes', {'double', 'double', 'double',}, 'VariableNames', {'tamaBloque', 'tiempo', 'TamaMatriz'});

TamaBloque = [10, 50,100,200,600,800,1000,1200,1400];

for i = 1:length(TamaBloque)
    % Generar una matriz de tamaño tamañosMatrices(i) x tamañosMatrices(i)
    sizeBloc = TamaBloque(i);
    
    A=rand(2000,2000);
    B=rand(2000,2000);
    
    matProdBloc= @() matrixMultiplyBloques(A,B,sizeBloc)
    timeBlock1 = timeit(matProdBloc);


    % Agregar los tiempos medidos a la tabla
    tiemposTablaBloc = [tiemposTablaBloc; table(TamaBloque(i), timeBlock1, 2000, 'VariableNames', {'tamaBloque', 'tiempo', 'TamaMatriz'})];
end

