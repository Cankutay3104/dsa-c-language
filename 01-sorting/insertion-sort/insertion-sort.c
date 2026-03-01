#include <stdio.h>

int insertionSort(int arr[], int n);

int main(){

    int arr[] = {7, 8, 26, 33, 13, 23, 98, 57};

    int n = sizeof(arr)/sizeof(arr[0]);

    int comparisons = insertionSort(arr, n);

    printf("Number of comparisons: %d\n", comparisons);

    return 0;
}

int insertionSort(int arr[], int n){
    int comparisons = 0;

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i-1;

        while (j >= 0) {
            comparisons++; // We are about to compare arr[j] and key
            
            if (arr[j] > key) {
                arr[j+1] = arr[j];
                j--;
            } 
            else {
                // The element is not greater than the key, so we stop
                break; 
            }
        }
        arr[j+1] = key;
    }
    return comparisons;
}