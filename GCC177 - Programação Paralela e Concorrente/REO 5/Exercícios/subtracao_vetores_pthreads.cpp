#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define NUM_THREADS 5
#define tam 10

using namespace std;

double array1[tam], array2[tam], resulting_array[tam];

void array_initializer(double array[]) {
    for(int i = 0; i < tam; i++) {
        array[i] = rand() % 100;
    }
}

void print_array(double array[]) {
    for(int i = 0; i < tam; i++){
        cout << array[i] << " ";
    }
    cout << endl << endl;
}

void *subtraction (void *param) {
    long i = (long) param;
    resulting_array[i] = array1[i] - array2[i];

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    array_initializer(array1);
    array_initializer(array2);

    pthread_t threads[NUM_THREADS];

    for(long i = 0; i < tam; i++) { 
        pthread_create(&threads[i % NUM_THREADS], NULL, subtraction, (void *)(i)); 
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    cout << "Array 1 elements: ";
    print_array(array1);
    cout << "Array 2 elements: ";
    print_array(array2);
    cout << "Resulting array: ";
    print_array(resulting_array);

    return 0;
}