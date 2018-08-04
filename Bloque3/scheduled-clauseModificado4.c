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
      printf("En el parallel:\n");
      printf(" In parallel: %d\n", omp_in_parallel());
      printf(" Nº procesadores disponibles: %d\n", omp_get_num_procs());
      printf(" Nº threads usados: %d\n", omp_get_num_threads());
    }
    // suma = suma + a[i];
    //printf(" thread %d suma a[%d]=%d suma=%d \n",
    //omp_get_thread_num(),i,a[i],suma);
  }

  omp_get_schedule(&kind,&modifier);
  printf("Fuera de parallel for: \n");
  printf(" In parallel: %d\n", omp_in_parallel());
  printf(" Nº procesadores disponibles: %d\n", omp_get_num_procs());
  printf(" Nº threads usados: %d\n", omp_get_num_threads());
}
