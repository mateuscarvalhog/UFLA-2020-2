#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

#define PIPE_READ  0
#define PIPE_WRITE 1

int fd[2];

void consumptionFunc() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        cout << "Erro na criacao do processo" << endl;
        exit(1);
    } else if (pid == 0) {
        int product, readBytes;
        close(fd[PIPE_WRITE]);

        while (1) {
            // impedir que os consumidores tentem consumir antes da insercao
            // e caiam na condicao de parada na hora errada
            sleep(rand() % 7);

            readBytes = read(fd[PIPE_READ], &product, sizeof(int));
            if(readBytes == -1) {
                cout << "Erro na leitura do pipe" << endl;
            } else if(readBytes == 0) {
                break;  // condicao de parada é não ler nada
            }
            cout << "Filho " << getpid() << " consumiu item " << product << endl;
        }
        close(fd[PIPE_READ]);
        
        exit(0);
    }
}

int main() {
    if (pipe(fd) < 0) {
        cout << "Erro na criacao do pipe" << endl;
        exit(0);
    }
    
    for (int i = 0; i < 4; i++) {   // 4 consumidores
        consumptionFunc();
    }
    
    close(fd[PIPE_READ]);
    for (int i = 0; i < 10; i++) {  // 10 produtos
        int random = rand() % 100;  // numeros entre 1 e 100
        
        cout << "Pai produziu item " << random << endl;
        write(fd[PIPE_WRITE], &random, sizeof(int));

        // impedir que o produtor insira itens no pipe antes do anterior ser lido
        sleep(rand() % 7);
    }
    close(fd[PIPE_WRITE]);

    return 0;
}