#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	int size, rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	int sendBuffer, recvBuffer[size - 1];
	sendBuffer = size * rank;
	cout << "Sou o processo " << rank << " e tenho a informação " << sendBuffer << "\n";

	if(rank != 0) {
		MPI_Send(&sendBuffer, 1, MPI_FLOAT, 0, rank, MPI_COMM_WORLD);
	} else {
		cout << "Sou o processo " << rank << " e tenho todas as informações: " << sendBuffer << " ";
		for(int i = 0; i < size - 1; i++) {
			MPI_Recv(&recvBuffer[i], 1, MPI_INT, i + 1, i + 1, MPI_COMM_WORLD, &status);
			cout << recvBuffer[i] << " ";
		}
		cout << endl;
	}
	
    MPI_Finalize();
    return 0;
}
