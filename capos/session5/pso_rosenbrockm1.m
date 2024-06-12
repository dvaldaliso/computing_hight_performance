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
tic
for paso=1:500
    for i=1:numparticles
        rp=rand();
        rg=rand();
        vx(i)=w*vx(i)+fip*rp*(best_posx(i)-posx(i))+fip*rg*(bestgx-posx(i));
        vy(i)=w*vy(i)+fip*rp*(best_posy(i)-posy(i))+fip*rg*(bestgy-posy(i));
        posx(i)=posx(i)+lr*vx(i);
        posy(i)=posy(i)+lr*vy(i);
        nv(i)=rosenb(posx(i),posy(i));
        if (nv(i)<imf(i))
            imf(i)=nv(i);
            best_posx(i)=posx(i);
            best_posy(i)=posy(i);
        end    
    end   
    [gaux,indgn]=min(nv);
    if (gaux<g)
            g=gaux;
            indg=indgn;
            bestgx=posx(indg);
            bestgy=posy(indgn);
        end
      
      g 
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

