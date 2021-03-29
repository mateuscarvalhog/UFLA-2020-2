/* 
  implementacao no ubuntu
  colocar archive.txt na pasta pessoal
  trocar "cura" no path pelo usuario do so
  caso necessario, altere o tamanho do vetor
 */

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    int fd[2]; 
    pid_t pid; 
    
    if(pipe(fd) < 0) {
        cout << "Erro na criacao do pipe" << endl;
        _exit(1);
    }

    if((pid = fork()) < 0) {
        cout <<"Erro na criacao do processo"<< endl;
        _exit(1);
    } 
    if (pid == 0) {     // filho
        char path[23];
    	close(fd[1]);
	    read(fd[0], path, 23 * sizeof(char));
	    close(fd[0]);
    
        execl("/usr/bin/wc", "wc", "-w", "-m", path, (char*)0);
    } 
    if(pid > 0) {       // pai
        char path[23] = {'/', 'h', 'o', 'm', 'e', '/', 'c', 'u', 'r', 'a', '/', 'a', 'r', 'c', 'h', 'i', 'v', 'e', '.', 't', 'x', 't'};
        
        close(fd[0]);
        write(fd[1], &path[0], 23 * sizeof(char));
        close(fd[1]);
        
        wait(NULL);
        cout << endl << "Father: son terminated its execution" << endl;
    }

    return 0;
}