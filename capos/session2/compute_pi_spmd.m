% basic monte carlo method to compute pi. This is the sequential
% version that uses a simple loop. input variable N is the number of
% points we will use to compute pi. Large value of N will result in
% a better approximation of pi, using spmd

function piresult = compute_pi_spmd(N)
tic;
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

    xcoord=rand(trozo2,1);
    ycoord=rand(trozo2,1);
    total_inside=0;
    
    for i=1:trozo2
        if (xcoord(i)^2 + ycoord(i)^2 <= 1)
            total_inside=total_inside+1;
        end
    end
end

suma=0
for i=1:numel(ini)
   suma=suma+total_inside{i};
end 

piresult = 4*suma/N;
toc
fprintf('The computed value of pi is %8.7f.\n',piresult);
end