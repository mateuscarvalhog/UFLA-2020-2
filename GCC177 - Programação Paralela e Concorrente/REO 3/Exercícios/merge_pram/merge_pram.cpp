#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 8

using namespace std;

int A[N] = {4, 5, 6, 7, 0, 1, 2, 3};

int merge_pram(int i){
    cout << getpid() << " responsavel pelo valor " << A[i - 1] <<endl;
    
    int low, high, index;

    if (i <= N / 2) {
        low = (N / 2) + 1;
        high = N;
    } else {
        low = 1;
        high = N / 2;
    }
    
    do {
        index = (low + high) / 2;
        if (A[i - 1] < A[index - 1]) {
            high = index - 1;
        } else {
            low = index + 1;
        }
    } while (low <= high);

    return high + i - N / 2;
}

int main(){

    for (int i = 1; i <= N; i++){
        if(fork() == 0){
            int pos = merge_pram(i);
            cout << getpid() << " terminou na posicao " << pos << endl;
            exit(0);
        }
    }
    
    for (int i = 0; i < N; i++){
        wait(NULL);
    }

    return 0;
}