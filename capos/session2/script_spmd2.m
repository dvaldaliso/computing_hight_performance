clear
N=1200;A=rand(N,1);B=rand(N,1);C=rand(N,1); solf=zeros(N,2);
tic 
spmd 
sol=zeros(N,2);
    trozo=N/numlabs;
    ini=(labindex-1)*trozo+1;
    fin=labindex*trozo
   for i=ini:fin
        sol(i,:)=roots([A(i,1),B(i,1),C(i,1)]);
   end
end

for i=1:numel(ini)
   init=ini{i}
  fint=fin{i}
  aux=sol{i};
  solf(init:fint,1:2)=aux(init:fint,1:2);
end 
toc