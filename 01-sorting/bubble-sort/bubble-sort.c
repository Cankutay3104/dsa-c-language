#include <stdio.h>

int bubbleSort(int arr[], int n);

int main(){

    int arr[] = {7, 8, 26, 33, 13, 23, 98, 57};

    int n = sizeof(arr)/sizeof(arr[0]);

    int comparisons = bubbleSort(arr, n);

    printf("Number of comparisons done: %d\n", comparisons);

    return 0;
}

int bubbleSort(int arr[], int n){
    int comparisons = 0;
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            comparisons++;
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return comparisons;
}