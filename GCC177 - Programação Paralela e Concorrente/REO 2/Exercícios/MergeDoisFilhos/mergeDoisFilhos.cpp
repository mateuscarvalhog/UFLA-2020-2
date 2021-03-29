#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <bits/stdc++.h> 

using namespace std;

// funcoes merge e selection retiradas do geeksforgeeks
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void selectionSort(int arr[], int n)  
{  
    int i, j, min_idx;  
  
    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n-1; i++)  
    {  
        // Find the minimum element in unsorted array  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
        if (arr[j] < arr[min_idx])  
            min_idx = j;  
  
        // Swap the found minimum element with the first element  
        swap(&arr[min_idx], &arr[i]);  
    }  
}  

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main(){
    int fd[2], fd2[2], fd3[2], fd4[2]; 

    pid_t pid;
    if((pipe(fd)) < 0 or (pipe(fd2)) < 0 or (pipe(fd3)) < 0 or (pipe(fd4)) < 0) {
        cout << "Pipe nao criado" << endl;
        _exit(1);
    }
    
    if((pid = fork()) < 0) {
        cout <<"Processo nao criado"<< endl;
        _exit(1);
    }
    if(pid == 0) {   // filho
        int meu_vetor[10];
        
        close(fd[1]);
        read(fd[0], meu_vetor, 40);
        close(fd[0]);
        
        selectionSort(meu_vetor, 10);

        close(fd2[0]);
        write(fd2[1], &meu_vetor, 10* sizeof(int));
        close(fd2[1]);

        _exit(0);
    }
    if(pid > 0) {   // pai
        pid_t pid2;
        if((pid2 = fork()) < 0) {
            cout <<"Processo nao criado"<< endl;
            _exit(1);
        }
        if(pid == 0) {   // filho
            int meu_vetor[10];
            
            close(fd3[1]);
            read(fd3[0], meu_vetor, 40);
            close(fd3[0]);
            
            selectionSort(meu_vetor, 10);

            close(fd4[0]);
            write(fd4[1], &meu_vetor, 10* sizeof(int));
            close(fd4[1]);

            _exit(0);
        }
        
        int vetor[20]={21, 12, 3, 94, 51, 69, 36, 84 ,90, 10,
                        1, 3, 56, 45, 33, 77, 67, 18, 40, 100};
        
        close(fd[0]);
        write(fd[1], &vetor[0], 10 * sizeof(int));
        close(fd[1]);
        
        close(fd3[0]);
        write(fd3[1], &vetor[10], 10 * sizeof(int));
        close(fd3[1]);

        close(fd2[1]);
        read(fd2[0], &vetor[0], 10 * sizeof(int));
        close(fd2[0]);

        close(fd4[1]);
        read(fd4[0], &vetor[10], 10 * sizeof(int));
        close(fd4[0]);
        
        wait(NULL);
        mergeSort(vetor, 0, 19);

        cout << "Array after sorting: ";
        for(int i = 0; i < 20; i++)
            cout << vetor[i] << " ";
        cout << endl;
    }

    return 0;
}