/*
  codigo feito utilizando como base exemplo de aula
 */

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    int fd[2], fd2[2]; 

    pid_t pid; 
    if((pipe(fd)) < 0 or (pipe(fd2) < 0) ) {
        cout << "Pipe nao criado" << endl;
        _exit(1);
    }
    
    if( (pid=fork())<0 ) {
        cout <<"Processo nao criado"<< endl;
        _exit(1);
    }
    if(pid == 0) {   // filho
        int meu_vetor[10];
        close(fd[1]);
        read(fd[0], meu_vetor, 40);
        close(fd[0]);
        int menor = meu_vetor[0];
        for (int i = 1; i < 10; i++) {
            if(meu_vetor[i] < menor)
                menor = meu_vetor[i];
        }

        close(fd2[0]);
        write(fd2[1], &menor, sizeof(menor));
        close(fd2[1]);
    }
        
    if(pid > 0) {
        int vetor[10]={21, 12, 3, 94, 51, 69, 36, 84 ,90, 10};
        close( fd[0] );
        write( fd[1], &vetor[0], 10*sizeof(int));
        close( fd[1] );
        
        int maior = vetor[0];
        for (int i = 1; i < 10; i++) {
            if(vetor[i] > maior)
                maior = vetor[i];
        }


        int menor;
        
        wait(NULL);

        close(fd2[1]);
        read(fd2[0], &menor, sizeof(menor));
        close(fd2[0]);

        cout << "Pai:\t- Menor: "<< menor << endl
             << "\t- Maior: " << maior << endl;
    }

    return 0;
}