% basic monte carlo method to compute pi. This is the sequential
% version that uses a simple loop. input variable N is the number of
% points we will use to compute pi. Large value of N will result in
% a better approximation of pi,

function piresult = compute_pi_for_vectorizado_gpuarray(N)
tic;
xcoord=gpuArray.rand(N,1);
ycoord=gpuArray.rand(N,1);
%total_inside=0;

%cambio vectorizado
v=xcoord.^2+ycoord.^2<=1;

piresult = 4*sum(v)/N;
toc
fprintf('The computed value of pi is %8.7f.\n',piresult);
end