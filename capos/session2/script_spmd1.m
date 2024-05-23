clear           %archivo ejemplo3.m
N=1200;A=rand(N,1);B=rand(N,1);C=rand(N,1);
spmd 
  trozo=N/numlabs %numlabs: numero de worker como mpi
  ini=(labindex-1)*trozo+1; %labindex el current worker parecido en mpi
  fin=labindex*trozo
  for i=ini:fin
    sol(i,:)=roots([A(i),B(i),C(i)]);
end
end

% luego de la ejecucion chequeo que hace cada worker
% sol{1}
% sol{2}
% size(sol)