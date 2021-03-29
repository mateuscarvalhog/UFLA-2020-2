#include "mpi.h"
#include <iostream>
#include <cstdlib>
#define SIZE 4 
using namespace std; 

int main(int argc, char *argv[]) { 
	int numtasks, rank, sendcount, recvcount, source; 
	float sendbuf[SIZE][SIZE] = { 
	{1.0, 2.0, 3.0, 4.0}, 
	{5.0, 6.0, 7.0, 8.0}, 
	{9.0, 10.0, 11.0, 12.0}, 
	{13.0, 14.0, 15.0, 16.0}}; //buffer de envio 
	float recvbuf[SIZE];//buffer de recebimento 
	MPI_Init(&argc,&argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
	if (numtasks == SIZE){ 
 		source = 0; 
 		sendcount = SIZE; 
 		recvcount = SIZE; 
 		MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source,  MPI_COMM_WORLD); 
  		cout <<"Results proc " <<rank <<":\t " <<recvbuf[0] << "\t " << recvbuf[1] << "\t " << recvbuf[2]<< "\t " <<  recvbuf[3] << endl; 
	}else 
		cout <<"Must specify " << SIZE << " processors. Terminating."; 
	MPI_Finalize(); 
} 
