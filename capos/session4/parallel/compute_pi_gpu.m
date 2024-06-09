function piresult = compute_pi_gpu(N)
gpu = gpuDevice();
tic;
x=gpuArray.rand(N,1);
y=gpuArray.rand(N,1);
total_inside= sum(((x .* x + y .* y) < 1)); 
piresult = 4*gather(total_inside)/N;
wait(gpu)
toc
fprintf('The computed value of pi is %8.7f.\n',piresult);
end
