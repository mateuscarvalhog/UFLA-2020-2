#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

#define NUM_THREADS 5
#define tam 100

using namespace std;

pthread_mutex_t mutex;
int array[tam];

void *bubble_sort(void *param) {
    long i = (long) param;
    int aux;

    pthread_mutex_lock(&mutex);
    for (int j = 0; j < tam-1-i; j++) {
        if (array[j] > array[j+1]) {
            aux = array[j];
            array[j] = array[j+1];
            array[j+1] = aux;
        }
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void print_array(int array[]) {
    for(int i = 0; i < tam; i++){
        cout << array[i] << " ";
    }
    cout << endl << endl;
}

int main(){
	srand(time(NULL));
    for(int i = 0; i < tam; i++) {
        array[i] = rand() % 100;
    }

	cout << "Array before assortment: " << endl;
	print_array(array);

	pthread_t threads[NUM_THREADS];
    for (long i = 0; i < tam; i++){
        pthread_create(&threads[i % NUM_THREADS], NULL, bubble_sort, (void *)(i));
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

	cout << "Array after assortment: " << endl;
	print_array(array);

    pthread_mutex_destroy(&mutex);

    return 0;
}