#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_PRIORITY_QUEUE_SIZE 16
#define FALSE 0
#define TRUE 1

struct HeapStruct
{
    int capacity;
    int size;
    int *elements;
};
typedef struct HeapStruct *PriorityQueue;

PriorityQueue InitializePriorityQueue(int);
void DestroyPriorityQueue(PriorityQueue);
void MakeEmptyPriorityQueue(PriorityQueue);
void InsertPriorityQueue(int, PriorityQueue);
int DeletePriorityQueue(PriorityQueue);
int FindMinPriorityQueue(PriorityQueue);
int IsEmptyPriorityQueue(PriorityQueue);
int IsFullPriorityQueue(PriorityQueue);
void DisplayPriorityQueue(PriorityQueue);
PriorityQueue BuildPriorityQueue(int, int[]);
void Heapify(int[], int, int);


PriorityQueue InitializePriorityQueue(int maxElements)
{
    PriorityQueue h;

    if (maxElements < MIN_PRIORITY_QUEUE_SIZE){
        printf("Priority queue size is too small!\n");
        return NULL;
    }
    h = (PriorityQueue)malloc(sizeof(struct HeapStruct));

    if (h == NULL){
        printf("Out of memory space!!!\n");
        return NULL;
    }

    h->elements = malloc((maxElements + 1) * sizeof(int));
    if (h->elements == NULL){
        printf("Out of memory space!!!\n");
        free (h);
        return NULL;
    }

    h->capacity = maxElements;
    h->size = 0;
    h->elements[0] = INT_MIN;

    return h;
}

void MakeEmptyPriorityQueue(PriorityQueue h)
{
    h->size = 0;
}

int IsEmptyPriorityQueue(PriorityQueue h)
{
    return h->size == 0;
}

int IsFullPriorityQueue(PriorityQueue h)
{
    return h->size == h->capacity;
}

void DestroyPriorityQueue(PriorityQueue h)
{
    free(h->elements);
    free(h);
}

void DisplayPriorityQueue(PriorityQueue h)
{
    int i;
    for (i = 1; i <= h->size; i++)
        printf("--> %d\n", h->elements[i]);
}

int FindMinPriorityQueue(PriorityQueue h)
{
    if (h == NULL || IsEmptyPriorityQueue(h))
    {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    // In a min-heap, the root (index 1) is always the minimum
    return h->elements[1];
}

void InsertPriorityQueue(int val, PriorityQueue h)
{
    int i;

    if (IsFullPriorityQueue(h))
    {
        printf("Priority Queue is full!\n");
        return;
    }

    // Start at the end of the heap and move up
    // h->elements[0] is INT_MIN, acting as a sentinel to stop the loop
    for (i = ++h->size; h->elements[i / 2] > val; i /= 2)
    {
        h->elements[i] = h->elements[i / 2];
    }

    h->elements[i] = val;
}

int DeletePriorityQueue(PriorityQueue h)
{
    int i, child;
    int minElement, lastElement;

    if (IsEmptyPriorityQueue(h))
    {
        printf("Priority Queue is empty!\n");
        return h->elements[0];
    }

    minElement = h->elements[1];
    lastElement = h->elements[h->size--];

    // We use the Heapify logic here to "percolate down" the last element
    // Starting from the root (1)
    for (i = 1; i * 2 <= h->size; i = child)
    {
        child = i * 2;

        // Find smaller child
        if (child != h->size && h->elements[child + 1] < h->elements[child])
        {
            child++;
        }

        // Percolate down
        if (lastElement > h->elements[child])
        {
            h->elements[i] = h->elements[child];
        }
        else
        {
            break;
        }
    }

    h->elements[i] = lastElement;
    return minElement;
}

PriorityQueue BuildPriorityQueue(int n, int a[])
{
    PriorityQueue h;
    int i;

    h = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (h == NULL){
        printf("Out of memory space!!!\n");
        return NULL;
    }

    h->elements = malloc((n + 1) * sizeof(int));
    if (h->elements == NULL){
        printf("Out of memory space!!!\n");
        free(h);
        return NULL;
    }

    h->capacity = n;
    h->size = n;
    h->elements[0] = INT_MIN;

    for (i = 0; i<n; i++)
    {
        h->elements[i + 1] = a[i];
        printf("%d\n", h->elements[i + 1]);
    }

    for (i = n / 2; i>0; i--){
        Heapify(h->elements, i, n);
    }
    return h;
}

void Heapify(int a[], int rootIndex, int heapSize)
{
    int child;
    int temp = a[rootIndex];

    // While the current node has at least a left child
    for (; rootIndex * 2 <= heapSize; rootIndex = child){
        child = rootIndex * 2;

        // Step 1: Find the smaller of the two children
        if (child != heapSize && a[child + 1] < a[child]){
            child++;
        }

        // Step 2: If the child is smaller than the temp value, move it up
        if (temp > a[child]){
            a[rootIndex] = a[child];
        }
        else{
            break; // Found the right spot
        }
    }
    a[rootIndex] = temp;
}


void MaxHeapify(int a[], int rootIndex, int heapSize) {
    int child, temp = a[rootIndex];

    for (; rootIndex * 2 <= heapSize; rootIndex = child) {
        child = rootIndex * 2;

        // Find LARGER child
        if (child != heapSize && a[child + 1] > a[child])
            child++;

        // Move larger child up if it's bigger than temp
        if (temp < a[child])
            a[rootIndex] = a[child];
        else
            break;
    }
    a[rootIndex] = temp;
}

// Increase value at index i and re-heapify
void IncreaseKey(int i, int newValue, PriorityQueue h) {
    if (newValue < h->elements[i])
        return; // Must be an increase

    h->elements[i] = newValue;

    Heapify(h->elements, i, h->size); // Sink it down
}

// Decrease value at index i and re-heapify
void DecreaseKey(int i, int newValue, PriorityQueue h) {
    if (newValue > h->elements[i])
        return; // Must be a decrease

    h->elements[i] = newValue;

    // Swim it up (Percolate Up logic)
    int val = h->elements[i];
    for (; h->elements[i / 2] > val; i /= 2) {
        h->elements[i] = h->elements[i / 2];
    }
    h->elements[i] = val;
}

// Find k-smallest element in an array
int FindKSmallest(int a[], int n, int k) {
    PriorityQueue h = BuildPriorityQueue(n, a);

    int result;
    for (int i = 0; i < k; i++) {
        result = DeletePriorityQueue(h); // Extract min k times
    }
    return result;
}

// Heap Sort (Ascending using Max Heap)
void HeapSort(int a[], int n) {
    // 1. Build Max Heap
    for (int i = n / 2; i > 0; i--)
        MaxHeapify(a, i, n);

    // 2. Extract elements one by one
    for (int i = n; i > 1; i--) {
        // Swap root (largest) with the last element
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        // Heapify the reduced heap
        MaxHeapify(a, 1, i - 1);
    }

}