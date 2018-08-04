#include <stdio.h>  
#include <omp.h>  
  
int main( )   
{
  int a[12], i;

  omp_set_dynamic(0);  
  printf("DIN %d\n", omp_get_dynamic());
  #pragma omp parallel for schedule(dynamic, 2)  
    for (i=0; i<12; i++)
      {
	if(i==0)
	  printf("DIN %d\n", omp_get_dynamic());
	  
        a[i]=i;
	printf(" thread %d a[%d]=%d \n", omp_get_thread_num(),i,a[i]);
      }

    omp_set_dynamic(1);
    printf("DIN %d\n", omp_get_dynamic());
    
#pragma omp parallel for  
    for (i=0; i<12; i++)
      {
	if(i==0)
	  printf("DIN %d\n", omp_get_dynamic());
	printf(" thread %d a[%d]=%d \n", omp_get_thread_num(),i,a[i]);
      }
    
    printf("DIN %d\n", omp_get_dynamic());
    printf("****\n");

    omp_set_dynamic(0);
    printf("DIN %d\n", omp_get_dynamic());
    
#pragma omp parallel for  
    for (i=0; i<12; i++)
      {
	if(i==0)
	  printf("DIN %d\n", omp_get_dynamic());
	printf(" thread %d a[%d]=%d \n", omp_get_thread_num(),i,a[i]);
      }
    
    printf("DIN %d\n", omp_get_dynamic());
}  
