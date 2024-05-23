N=800;A=rand(N,1);B=rand(N,1);C=rand(N,1);
spmd 
  trozo=N/numlabs;
  ini=(labindex-1)*trozo+1;
  fin=labindex*trozo;
  for i=ini:fin
    sol(i,:)=roots([A(i),B(i),C(i)]);
end
end
