#include <stdio.h>

int partition(int arr[], int low, int high, int *comparisons);
void quickSort(int arr[], int low, int high, int *comparisons);

int main() {

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int comparisons = 0;

    quickSort(arr, 0, n - 1, &comparisons);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nTotal comparisons: %d\n", comparisons);

    return 0;
}


void quickSort(int arr[], int low, int high, int *comparisons) {
    if (low < high) {
        int p = partition(arr, low, high, comparisons);

        if (p > low)
            quickSort(arr, low, p - 1, comparisons);
        if (p < high)
            quickSort(arr, p + 1, high, comparisons);
    }
}

int partition(int arr[], int low, int high, int *comparisons) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    int temp;

    while (1) {
        while (i <= high && (++(*comparisons)) && arr[i] <= pivot)
            i++;
        while (j >= low && (++(*comparisons)) && arr[j] > pivot)
            j--;
        if (i >= j) break;

        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j;
}
