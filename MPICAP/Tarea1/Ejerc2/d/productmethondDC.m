%[V,D]=eigs(@(x)prodMethodc(x,L21,L22,L11,M11,M12),219,5)



function [y] = prodMethondDC(x,L21,L22,L11,M11,M12)
% [y] = prodNucle(L21,L22,L11,M11,M12,x)
% Esta función realiza el producto matriz por vector ( y=A*x), donde A es la matriz que se obtiene de la discretizacin de la ecuacin de la difusin neurtica en dos grupos de energa.
%  No se dispone de la matriz explicita ,  A= inv(L11)(M11+M12*inv(L22)*L21)), por tanto cuando se tiene que realizar el producto de A*y tenemos que realizar las operaciones siguientes:
%  el resultado se almacena en el vector y

	val1=M12.*x; % producto matriz diagonal por vector

	val2=L22*x; %  producto matriz diagonal por vector
	
    %val3=gmres(L22,val2,10,1.e-7,1000); % Resolucin de sistema no simtrico
	val3=1./L21 .*val2; % Resolucin de sistema simtrico y del +
	
    val4=M11.*val3; % Producto matriz diagonal por vector
	
    val1 = val1+val3; %Suma de vectores
    
    %val6=1./L11 .*val1;
    val6=bicg(L11,val1,1.e-7,1000)

    val7=L21.*val6
    y=cgs(L22,val7,1.e-7,1000); %Resolucin de sistema simtrico y del +
     
end