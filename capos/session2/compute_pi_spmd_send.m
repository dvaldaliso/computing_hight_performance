% basic monte carlo method to compute pi. This is the sequential
% version that uses a simple loop. input variable N is the number of
% points we will use to compute pi. Large value of N will result in
% a better approximation of pi, using spmd

function piresult = compute_pi_spmd_send(N)
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

    middel=labindex<numlabs;
    if labindex == 1
        labSend(total_inside,2)
    else if middel  
        total_inside = total_inside + labReceive(labindex-1)
        labSend(total_inside, labindex+1)
    else
        total_inside = total_inside + labReceive(labindex-1)
    end         
    end
end    



piresult = 4*total_inside{numel(ini)}/N;
toc
fprintf('The computed value of pi is %8.7f.\n',piresult);
end