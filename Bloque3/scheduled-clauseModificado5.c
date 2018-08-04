#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

char* printSched (omp_sched_t type) {
  char * ret;
  if (type == omp_sched_static)
    ret = "Static";
  else if (type == omp_sched_dynamic)
    ret = "Dynamic";
  else if (type == omp_sched_guided)
    ret = "Guided";
  else if (type == omp_sched_auto)
    ret = "Auto";
  return ret;
}

int main(int argc, char **argv) {
  int i, n=16,chunk,a[n],suma=0;

  omp_sched_t kind;
  int modifier;

  if(argc < 2) {
    fprintf(stderr,"\nFalta chunk \n");
    exit(-1);
  }
  chunk = atoi(argv[1]);

  for (i=0; i<n; i++)
    a[i] = i;
  
  #pragma omp parallel for firstprivate(suma) lastprivate(suma) schedule(dynamic,chunk)
  for (i=0; i<n; i++)
  {
    if(i==0){
      omp_get_schedule(&kind,&modifier);
      printf("Antes de la modificación:\n");
      printf(" dyn-var: %d\n", omp_get_dynamic());
      printf(" nthreads-var: %d\n", omp_get_max_threads());
      printf(" run-shed-var: %s, %d\n", printSched(kind), modifier);

      omp_set_dynamic(1);
      omp_set_num_threads(2);
      omp_set_schedule(omp_sched_static, modifier+2);

      omp_get_schedule(&kind,&modifier);
      printf("Después de la modificación:\n");
      printf(" dyn-var: %d\n", omp_get_dynamic());
      printf(" nthreads-var: %d\n", omp_get_max_threads());
      printf(" run-shed-var: %s, %d\n", printSched(kind), modifier);
    }
  }
}
