/* SOMA PARALELA COM PIPE
 * Processo pai cria vetor de 20 posições, preenche e 
 * envia pelo pipe os 10 primeiros elementos. Processo 
 * filho soma os elementos recebidos e envia a soma para o 
 * processo pai, que soma com a sua soma parcial dos 10 
 * ultimos elementos e gera o total.
 * Processo e pai realizam soma paralela.
 * Foram usados dois pipes. */
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
int fd[2], fd2[2]; 

pid_t pid; 
if( (pipe(fd)<0) or (pipe(fd2)<0) ) {
	cout << "Pipe nao criado" << endl;
	_exit(0);
}
if( (pid=fork())<0 ) {
	cout <<"Processo nao criado"<< endl;
	_exit(0);
}
if ( pid == 0 ) {  
	int meu_vetor[10];
	close(fd[1]);
	read(fd[0],meu_vetor,40);
	close(fd[0]);
	int soma_filho=0;
	for (int i=0;i<10;i++) {
		soma_filho+=meu_vetor[i];
	}	
	close(fd2[0]);
	write(fd2[1],&soma_filho,sizeof(soma_filho));
	close(fd2[1]);
}
	
if ( pid >0 ) {
	int vetor[20]={1, 2, 3, 4, 5, 6, 7, 8 ,9, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	close( fd[0] );
	write( fd[1], &vetor[0], 10*sizeof(int));
	close( fd[1] );
	int soma_pai=0;
	for (int i=10;i<20;i++) {
		soma_pai+=vetor[i];
	}
	int total=0;
	
	close( fd2[1] );
	
	read(fd2[0],&total,sizeof(total));
	total = total+soma_pai;
	cout << "Pai: Total="<<total<< endl;
	close(fd2[0]);	
	wait(NULL);
}

return 0;

}


