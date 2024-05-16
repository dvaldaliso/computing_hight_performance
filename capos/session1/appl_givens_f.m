function A=appl_givens_f(A,i,k,c,s)
[m,n]=size(A);
for j=1:n
   t1=A(i,j);
   t2=A(k,j);
   A(i,j)=c*t1-s*t2;
   A(k,j)=s*t1+c*t2;
end


