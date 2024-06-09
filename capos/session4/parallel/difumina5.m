function [ imagen_out ] = difumina5( imorig )
%La imagen se guarda como un array tridimensional de enteros (uint8), R, G y B
% Esta función calcula el valor de cada pixel como la media de todos los
% pixeles vecinos y vuelve a guardarlo en variables de tipo uint8
[m,n,tam]=size(imorig)
im=double(imorig);
auxj=n-1;
auxi=m-1;
imagen_out=zeros(size(im),'uint8');
for ind=1:tam
    for j=2:auxj
        for i=2:auxi
           aux=double((1.0/5.0)*(im(i-1,j,ind)+ im(i,j-1,ind)+im(i,j,ind)+...
               im(i,j+1,ind)+ im(i+1,j,ind)));  
             aux=max(0,uint8(aux));
           imagen_out(i,j,ind)=min(255,aux);
        end
    end    
end
end

