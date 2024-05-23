N=800;
solf=zeros(N,2);
tic
spmd 
    trozo=floor(N/numlabs); %redondeo inferior
    if labindex<numlabs
       ini=(labindex-1)*trozo+1;
       fin=labindex*trozo;
    else
       ini=(labindex-1)*trozo+1;
       fin=N;
    end  
    trozo2=fin-ini+1;
    sol=zeros(trozo2,2); %generamos dentro sol, A,B,C
     A=rand(trozo2,1);B=rand(trozo2,1);C=rand(trozo2,1);  
   for i=1:trozo2
        sol(i,:)=roots([A(i,1),B(i,1),C(i,1)]);
   end
end
 
for i=1:numel(ini)
   init=ini{i};
  fint=fin{i};
  %aux=sol{i};
  solf(init:fint,1:2)=sol{i};
end 
toc