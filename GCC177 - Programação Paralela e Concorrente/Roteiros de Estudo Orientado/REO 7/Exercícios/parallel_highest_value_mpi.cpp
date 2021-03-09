#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv){
	int rank, max = 0, number = 0;
	
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
    srand(rank);
    number = rand() % 1000;
	cout << "Process " << rank << " have number " << number << endl;
    MPI_Reduce(&number, &max, 1,  MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0) {
	    sleep(0.5);
        cout << "Highest value is " << max << endl;
    }

	MPI_Finalize();
	return 0;
}