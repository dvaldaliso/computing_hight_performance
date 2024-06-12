
__global__ void ecuacion(double *solr, double * solim, const double *a, const double *b, const double *c )
{
 int id=threadIdx.x+blockIdx.x*blockDim.x;
double tmp=b[id]*b[id]-4*a[id]*c[id];
 if (tmp>=0)
    {solr[id]=(-b[id]+sqrt(tmp))/(2*a[id]);
     solim[id]=0.0;
    }
else
  {solr[id]=(-b[id]/(2*a[id]));
   solim[id]=(sqrt(-tmp))/(2*a[id]);
  }
}

 
 
