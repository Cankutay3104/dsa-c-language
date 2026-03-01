#include <stdio.h>

void swap(int *, int *);

int main(){

    int arr[] = {7, 8, 26, 33, 13, 23, 98, 57};

    int n = sizeof(arr) / sizeof(arr[0]);

    int comp_num = 0;
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            ++comp_num;
            if (arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]);
        }
    }

    printf("Number of comparisons: %d\n", comp_num);

    for (int i = 0; i < sizeof(arr)/4; ++i) {
        printf("a[%d] = %d, ", i, arr[i]);
    }

    return 0;
}

void swap(int *num1, int *num2){
    int temp;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}