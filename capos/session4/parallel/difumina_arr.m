function [ imagen_out ] = difumina_arr( imorig )
%La imagen se guarda como un array tridimensional de enteros (uint8), R, G y B
% Esta funci�n calcula el valor de cada pixel como la media de todos los
% pixeles vecinos y vuelve a guardarlo en variables de tipo uint8
[m,n,tam]=size(imorig)
im=double(imorig);
auxj=n-1;
auxi=m-1;
imagen_out=zeros(size(im),'uint8');
    function X = mif(row, col, ind)
        rowU = max(1,row-1);  rowD = min(m,row+1);
        colL = max(1,col-1);  colR = min(n,col+1);
        aux=double((1.0/5.0)*(im(rowU, col,ind)+ im(row, colL,ind)+im(row, col,ind)+...
               im(row, colR,ind)+ im(rowD,col,ind)));  
             aux=max(0,uint8(aux));
           imagen_out(i,j,ind)=min(255,aux);
        
    end

rows = gpuArray.colon(1, gridSize)';
cols = gpuArray.colon(1, gridSize);
for ind=1:tam
    imagen_out(:,:,ind)=arrayfun(@mif, rows, cols, ind) 
end
end

% test
% matr = imread('lena.png')
% difumina_arr(matr)