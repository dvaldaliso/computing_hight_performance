N=800;A=distributed.rand(1,N);
B=distributed.rand(1,N);
C=distributed.rand(1,N);
sol=distributed.zeros(2,N);
tic
spmd
    for i=drange(1:N)
    sol(:,i)=roots([A(i),B(i),C(i)]);
    end
end
toc