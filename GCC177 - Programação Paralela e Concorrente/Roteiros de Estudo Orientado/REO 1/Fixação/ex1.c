#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    
    int i;
    pid_t pid;

    if((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if(pid == 0) {
        //O código aqui dentro será executado no processo filho
        printf("pid do Filho: %d\n", getpid());
        
        i = 20;
    } else {
        //O código neste trecho será executado no processo pai
        printf("pid do Pai: %d\n", getpid());

        i = 10;
    }

    printf("%d\n", i);
    printf("Esta regiao sera executada por ambos processos\n\n");

    exit(0);
}