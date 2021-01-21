#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h> 
#include <iostream>

using namespace std;

int compare(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

void swap(int *xp, int *yp) {  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}

void selectionSort(int arr[], int n) {  
    int i, j, min_idx;  
   
    for (i = 0; i < n-1; i++) {  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
            if (arr[j] < arr[min_idx])  
                min_idx = j;  
  
        swap(&arr[min_idx], &arr[i]);  
    }  
}  

void printArray(int arr[]) {
    for(int i = 0; i < 10; i++)
        cout << arr[i] << " ";
    cout << "\n\n";
}

int main () {
    int values[10] = {40, 10, 100, 90, 20, 25, 80, 79, 0, 75};

    cout << "\nArray before sort: ";
    printArray(values);

    time_t start, end;

    int pid = fork();
    if(pid > 0) {
        //father
        
        wait(NULL);

        start = clock();
        
        int n = sizeof(values)/sizeof(values[0]);
        selectionSort(values, n);
        
        end = clock();
        double time_taken = double(end - start)/CLOCKS_PER_SEC;
        
        cout << "Time taken by father to execute selection sort is: " << fixed 
             << time_taken << " sec\n";
        cout << "Father's array: ";
        printArray(values);
    } else if(pid == 0){
        //son

        start = clock();
        
        qsort(values, 10, sizeof(int), compare);
        
        end = clock();
        double time_taken = double(end - start)/CLOCKS_PER_SEC; 
        
        cout << "Time taken by son to execute quicksort is: " << fixed 
             << time_taken << " sec\n";
        cout << "Son's array: ";
        printArray(values);
    } else {
        cerr << "Unexpected Error\n";
        exit(1);
    }

    return 0;
}