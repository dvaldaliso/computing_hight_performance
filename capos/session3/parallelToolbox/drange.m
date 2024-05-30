A=ones(10);
Ad=distributed(A);
spmd
    Al=getLocalPart(Ad)
    [m,n]=size(Al);
    for i=drange(1:10)
        Ad(:,i)=Ad(:,i)*i;
    end
end
An=gather(Ad)

%drange va muy lento