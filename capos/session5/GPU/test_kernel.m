N=800;A=rand(N,1);B=rand(N,1);C=rand(N,1);
tic
Ag=gpuArray(A);
Bg=gpuArray(B);
Cg=gpuArray(C);
solre=zeros(N,1);
solim=zeros(N,1);
solreg=gpuArray(solre);
solimg=gpuArray(solim);

kern=parallel.gpu.CUDAKernel('ecuacion.ptx','ecuacion.cu')
kern.ThreadBlockSize=800;


[solreg,solimg]=feval(kern,solreg,solimg,Ag,Bg,Cg);

gather(solreg);
gather(solimg);

