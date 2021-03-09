#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]){
    int num_procs;
    int id;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    double numero = (double) id + 1;
    double produto = 0;
    
    // Inserir chamada MPI para realizar produto paralelo dos valores 
    // armazenados na variável numero de cada processo
    MPI_Reduce(&numero, &produto, 1, MPI_DOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);

    if (id == 0){
        cout << "Produto paralelo = " << produto << endl;
    }
    MPI_Finalize();

    return 0;
}