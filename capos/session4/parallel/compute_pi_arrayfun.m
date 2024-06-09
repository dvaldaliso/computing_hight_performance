function piresult = compute_pi_arrayfun(N)
gpu = gpuDevice();
tic;
x=gpuArray.rand(N,1);
y=gpuArray.rand(N,1);

sal = arrayfun(@mif,x,y)

total_inside= sum(sal); 
piresult = 4*gather(total_inside)/N;
wait(gpu)
toc
fprintf('The computed value of pi is %8.7f.\n',piresult);
end
