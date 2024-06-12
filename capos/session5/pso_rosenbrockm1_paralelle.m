function pso_rosenbrockm1()
liminf=-10;
limsup=-10;
numparticles=500;
posx=20*rand(numparticles,1)-10;
posy=20*rand(numparticles,1)-10;
best_posx=posx;
best_posy=posy;
imf=zeros(numparticles,1);

for i=1:numparticles
  imf(i)=rosenb(posx(i),posy(i));
end
[g,indg]=min(imf);
vx=20*rand(numparticles,1)-10;
vy=20*rand(numparticles,1)-10;
bestgx=posx(indg)
bestgy=posy(indg);
lr=0.1;
w=0.5;
fip=0.1
    function [nv,vx,posx,best_posx, best_posy, imf]=minf(row, col)
        rp=rand();
        rg=rand();
        vx=w*vx+fip*rp*(best_posx-posx)+fip*rg*(bestgx-posx);
        vy(i)=w*vy(i)+fip*rp*(best_posy-posy)+fip*rg*(bestgy-posy);
        posx=posx+lr*vx;
        posy=posy+lr*vy;
        nv=rosenb(posx,posy);
        if (nv<imf)
            imf=nv;
            best_posx=posx;
            best_posy=posy;
        end  
    end
tic
for paso=1:500
    for i=1:numparticles
        imagen_out(:,:,ind)=arrayfun(@mif, rows, cols, ind)   
    end   
    [gaux,indgn]=min(nv);
    if (gaux<g)
            g=gaux;
            indg=indgn;
            bestgx=posx(indg);
            bestgy=posy(indgn);
        end
  [bestgx,bestgy]

  if mod(paso,10)==0
      plot(posx,posy,'*')
      axis([-10,10,-10,10])
      pause
  end
end
toc
end

    
    
function s=rosenb(x,y)
s=(1-x)^2+100*(y-x^2)^2;
end

% esto no le funciono al profe