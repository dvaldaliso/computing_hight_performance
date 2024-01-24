// kernel:  vadd
// Purpose: Compute the elementwise sum c = a+b
// input: a float vectors of length count
// output: 
//
__kernel void vadd(                                           
   __global float* v 
   __global float* vmax                                           
   const unsigned int count)                                      
{                                                                  
   int id = get_global_id(0); 
   numWorkitem = get_global_size(0);
   int block_size = count/numWorkitem;
   int start = block_size*id;
   int end = start + block_size-1                
   if(end > count){
       end=count-1;
   }
   float max = -1.0f;
   for (int i = start ; i <= end ; i++) {
       if(v[i]>max){
        max=v[i];
       } 
   }
   vmax[id]=max;
}                                                                      

