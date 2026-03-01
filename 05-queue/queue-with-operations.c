#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node {
    int val;
    struct Node *next;
};

struct QueueRecord {
    struct Node *front;   /* dummy node */
    struct Node *rear;    /* last real node or dummy */
    int size;
};

typedef struct QueueRecord* Queue;

Queue CreateQueue();
void MakeEmptyQueue(Queue q);
int IsEmptyQueue(Queue q);
int QueueSize(Queue q);
void Enqueue(int x, Queue q);
int Dequeue(Queue q);
int FrontOfQueue(Queue q);
int RearOfQueue(Queue q);
void DisplayQueue(Queue q);

/* Create a queue: allocate the queue record and call MakeEmptyQueue */
Queue CreateQueue() {
    Queue q = malloc(sizeof(struct QueueRecord));
    if (!q) {
        printf("Out of memory.\n");
        exit(1);
    }
    q->front = NULL;  // front will be set in MakeEmptyQueue
    q->rear = NULL;
    q->size = 0;
    MakeEmptyQueue(q);
    return q;
}

/* MakeEmptyQueue: free all real nodes, reset dummy, size, front, rear */
void MakeEmptyQueue(Queue q) {
    if (q->front != NULL) {
        struct Node *current = q->front->next;
        while (current) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    if (q->front == NULL) {
        q->front = malloc(sizeof(struct Node));
        if (!q->front) {
            printf("Out of memory.\n");
            exit(1);
        }
    }

    q->front->next = NULL;  // dummy node points to nothing
    q->rear = q->front;     // rear points to dummy initially
    q->size = 0;
}
//------------------------------------------------------------------------------

/* Queue status */
int IsEmptyQueue(Queue q) { return q->size == 0; }
int QueueSize(Queue q) { return q->size; }

/* Enqueue */
void Enqueue(int x, Queue q) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Out of memory.\n");
        exit(1);
    }
    newNode->val = x;
    newNode->next = NULL;

    q->rear->next = newNode; // append after rear
    q->rear = newNode;       // update rear
    q->size++;
}

/* Dequeue */
int Dequeue(Queue q) {
    if(IsEmptyQueue(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    struct Node *temp = q->front->next;

    int val = temp->val;
    q->front->next = temp->next;

    if(q->rear == temp)
        q->rear = q->front;

    free(temp);
    q->size--;

    return val;
}

/* Front / Rear values */
int FrontOfQueue(Queue q) {
    if(IsEmptyQueue(q)) { printf("Queue is empty.\n"); return -1; }
    return q->front->next->val;
}

int RearOfQueue(Queue q) {
    if(IsEmptyQueue(q)) { printf("Queue is empty.\n"); return -1; }
    return q->rear->val;
}

/* Display queue */
void DisplayQueue(Queue q) {
    struct Node *cur = q->front->next;
    while(cur) {
        printf("--> %d  ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}