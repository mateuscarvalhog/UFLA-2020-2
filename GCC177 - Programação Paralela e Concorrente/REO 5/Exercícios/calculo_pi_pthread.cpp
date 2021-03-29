#include <pthread.h>
#include <cstdlib>
#include <iostream>

#define n 50
#define NUM_THREADS 5

using namespace std;

pthread_mutex_t mutex;
double area;

double f(int i){
   double x;
   x = (double) i/(double) n;
   return 4.0/(1.0 + x*x);
}

void *calculate_area(void *param){
    long i = (long)(param);

    pthread_mutex_lock(&mutex);
    area += 4.0*f(2*i-1) + 2*f(2*i);
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    area = f(0) - f(n);


    pthread_t threads[NUM_THREADS];
    for (long i = 1; i <= n/2; i++)
        pthread_create(&threads[i % NUM_THREADS],NULL, calculate_area, (void *)i);
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    area /= (3.0 * n);
    cout << "Aproximação de pi: " << area << endl;
    
    return 0;
}