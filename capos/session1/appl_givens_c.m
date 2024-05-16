function A=appl_givens_c(A,i,k,c,s)
[m,n]=size(A)
for j=1:m
   t1=A(j,i);
   t2=A(j,k);
   A(j,i)=c*t1-s*t2;
   A(j,k)=s*t1+c*t2;
end
end


