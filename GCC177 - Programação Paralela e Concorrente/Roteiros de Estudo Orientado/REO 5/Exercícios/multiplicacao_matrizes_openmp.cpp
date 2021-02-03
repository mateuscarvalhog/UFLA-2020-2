#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define n 2

using namespace std;

void matrix_multiplier(double a[], double b[], double c[]) {   
    #pragma omp parallel for num_threads(n % 4 + 1)
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < n; j++) {
            double aux  = 0;
            for (int k = 0; k < n; k++) {
                aux += a[i*n+k] * b[k*n+j];
            } 
            c[i*n+j] = aux;
        }
    }
}

void printMatrix(double m[]){
    int cont = 0;
    for (int i = 0; i < n * n; i++){
        cout << m[i] << " ";
        cont++;
        
        if (cont % n == 0){
            cont = 0;
            cout << endl;
        }   
    }
    
    cout << endl;
}

int main() {
    double a[n*n], b[n*n], c[n*n];
    srand(time(NULL));
    for(int i=0; i<n*n; i++){
        a[i] = rand() % 100; 
        b[i] = rand() % 100;
    }

    matrix_multiplier(a, b, c);

    printMatrix(a);
    printMatrix(b);
    printMatrix(c);
}