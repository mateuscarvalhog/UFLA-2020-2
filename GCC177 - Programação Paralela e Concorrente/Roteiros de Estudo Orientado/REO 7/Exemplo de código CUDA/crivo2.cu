//Rodrigo Amamdor Coelho: 28/02/2011

//Este código é o Crivo de Aristóteles executado paralelamente na GPU.
//
//


#include <cuda.h>
#include <cutil.h>
#include<stdio.h>
#include <cuda_runtime.h> 



///////////////////////////////////////////////////////////////////////////////////
//GPU KERNEL

__shared__ int k;
__global__ void crivo_array(int *a)

{

	int idx = blockIdx.x*blockDim.x+threadIdx.x; // parassar entre as threads e blocls de threads
	a[idx]= idx;
	k=2;


	while(k*2<=idx){

		if (((a[idx] % k) == (0))&&(a[idx] > 0)&&(a[idx] != k)){ //verifico se é multipo de k
			a[idx] = a[idx] * -1; //marco o elemento na lista
		}

		k++;

		while(a[k]<0){
			k++;
		}

	}

}

///////////////////////////////////////////////////////////////////////////////////
//CPU

 int main(void)
{

	int *a_h, *a_d, threads, blocks;

	const int N=100000; //Numero de elementos da lista


	//Determino o numero de threads e blocks de threads usados
	if (N < 256)
	{
		threads = N;
		blocks = 1;
	}
	else
	{
		threads = 256;
		if ((N % threads) == 0)
			blocks = N/threads;
		else
			blocks = (N/threads) + 1;
	}
	//Fim do determincao	


	size_t size = N*sizeof(int); //determinando o tamanho do vetor de inteiros

	a_h=(int*)malloc(size); //alocando espaço na memoria da CPU

	cudaMalloc((void**)&a_d,size); //alocando espaço na memoria da GPU



	unsigned int timer = 0;
	CUT_SAFE_CALL(cutCreateTimer(&timer)); //cria função de calculo de tempo no CUDA
	CUT_SAFE_CALL(cutStartTimer(timer)); //inicia função de calculo de tempo no CUDA



	//faz crivo
	cudaMemcpy(a_d,a_h,size,cudaMemcpyHostToDevice);
	crivo_array<<<blocks,threads>>>(a_d);
	cudaMemcpy(a_h,a_d,size,cudaMemcpyDeviceToHost);
	//fim do crivo




	printf("\nTempo de computacao: %f (ms) \n\n", cutGetTimerValue(timer)); 
	CUT_SAFE_CALL(cutDeleteTimer(timer)); //finaliza com a função de contagem de tempo
/*
	printf("São primos os numeros entre 2 e %d\n", N);
	for(int i=2; i<N; i++)
		if (a_h[i] > 0)
			printf("%d\n",a_h[i]); //imprimo somente os numeros não marcados (primos)
*/

	free(a_h); // Liberando memoria da CPU
	cudaFree(a_d); // Liberando memoria da GPU

}
