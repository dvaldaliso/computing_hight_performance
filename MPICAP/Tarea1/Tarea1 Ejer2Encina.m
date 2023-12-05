val1=M12.*x; 
	val2=L21.*x; 
	val3=bicg (L22,val2,1.e-7,1000); % bicg
	val3=M11.*val3;
	val1=val1+val3;
	y=bicg(L11,val1,1.e-7,1000); %bicg
    k= L21.*y;
    z= bicg(L11,k, 1.e-7,1000);