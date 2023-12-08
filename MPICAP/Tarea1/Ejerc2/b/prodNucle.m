function [y] = prodNuclemethod(x,L21,L22,L11,M11,M12)

% method puede ser alguno de los mtodos siguientes, algunos argumentos pueden cambiar en la llamada al mtodo:  bicg, bicgstab, bicgstabl, cgs, gmres, ilu, lsqr, minres, mldivide, pcg, qmr, symmlq
% 
% Esta funcin realiza el producto matriz por vector ( y=A*x). Donde A es la matriz que se obtiene 
% al discretar la ecuacin de la difusin neutrnica en dos grupos de energa.
%  No se dispone de la matriz explicita y inv(L11)(M11+M12*inv(L22)*L21))
%  el resultado se almacena en el vector y

	val1=M11.*x; 
	val2=L21.*x; 
	val3=bicg(L22,val2,1.e-7,1000); % bicg
	val3=M12.*val3;
	val1=val1+val3;
	y=bicg(L11,val1,1.e-7,1000); %bicg
end