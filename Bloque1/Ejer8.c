/* SumaVectoresC.c 
   Suma de dos vectores: v3 = v1 + v2
*/ 

#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#include <omp.h> 

//#define PRINTF_ALL// comentar para quitar el printf ...
// que imprime todos los componentes
#define VECTOR_GLOBAL
#ifdef VECTOR_GLOBAL
#define MAX 33554432 //=2^25
double v1[MAX], v2[MAX], v3[MAX]; 
#endif

int main(int argc, char** argv){ 
 
  int i; 
  //struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
  double diff, start, end;

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){ 
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
 
  unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
#ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
#endif

  //Inicializar vectores
#pragma omp parallel sections private (i)
  {

    #pragma omp section
    for(i=0; i<N/4; i++){
      //   printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
    }

    #pragma omp section
    for(i=N/4; i<N/2; i++){
      // printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
    }

    
    #pragma omp section
    for(i=N/2; i<(3*N/4); i++){
      //  printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
    }

    #pragma omp section
    for(i=(3*N/4); i<N; i++){
      //  printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
      }
  }
  //clock_gettime(CLOCK_REALTIME,&cgt1);

  printf("\n");
  
  start=omp_get_wtime();

  //Calcular suma de vectores
#pragma omp parallel sections
  {
    #pragma omp section
    for(i=0; i<N/4; i++){
      //  printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v3[i] = v1[i] + v2[i];
    }

    #pragma omp section
    for(i=N/4; i<N/2; i++){
      //   printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v3[i] = v1[i] + v2[i];
    }

    #pragma omp section
    for(i=N/2; i<3*N/4; i++){
      //  printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v3[i] = v1[i] + v2[i];
    }

    #pragma omp section
    for(i=3*N/4; i<N; i++){
      //  printf("thread %d ejecuta la iteración %d del bucle\n", omp_get_thread_num(),i);
      v3[i] = v1[i] + v2[i];
    }
  }

  end=omp_get_wtime();

  printf("start= %f\n",start);
  printf("end= %f\n",end);
  
  //printf("dif= %f\n",end-start);

  // clock_gettime(CLOCK_REALTIME,&cgt2);
  //ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

  diff= (end-start);

  //Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
  printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",diff,N); 
  for(i=0; i<N; i++) 
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",i,i,i,v1[i],v2[i],v3[i]); 

#else
  printf("Tiempo(seg.):%16.16f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n", diff,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]); 
#endif
  return 0; 
}
