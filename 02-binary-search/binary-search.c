int binarySearch(int arr[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;
    while (low <= high) {
        (*comparisons)++;
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
