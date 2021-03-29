#include <pthread.h>
#include <stdio.h>
#include <math.h>
#define NUM_THREADS     10

int A[NUM_THREADS];
pthread_barrier_t barreira;


void imprimevetor(int tid){
int k;
for (k=0;k<NUM_THREADS;k++)  printf("T(%d):A[%d]=%d\n",tid, k,A[k]);printf("\n");
}
void *func(void *threadid)
{
   int i = (int)threadid ;
   A[i]=i;
  pthread_barrier_wait(&barreira);
imprimevetor(i);
}


int main (int argc, char *argv[])
{
int j;
   
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   pthread_barrier_init(&barreira,NULL,NUM_THREADS);
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, func, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         return(1);
      }
   }
   
   pthread_barrier_destroy(&barreira); 
   for(t=0; t<NUM_THREADS; t++){
                rc = pthread_join(threads[t], NULL);
                if (rc) {
                        printf("ERRO. Codigo do pthread_create() eh: %d\n", rc);
                        return(0);
                }
        }

 
   pthread_exit(NULL);
   return(0);
}

 
