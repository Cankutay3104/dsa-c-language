#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

/*A Node declaration to store a value, pointer to the next node and a priority value*/
struct Node
{
    int priority;
    int val;
    struct Node *next;
};

struct QueueRecord
{
    struct Node *front;   
    struct Node *rear;    
    int size;             
};

typedef struct QueueRecord *Queue;

Queue CreateQueue(int);
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);
void InsertWithPriority(Queue q, int val, int priority);
int DeleteWithPriority(Queue q);
void InsertWithPrioritySorted(Queue q, int val, int priority);
int DeleteMin(Queue q);


/*Inserts an element with priority in O(1) time*/
void InsertWithPriority(Queue q, int val, int priority)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Out of memory space\n");
        return;
    }

    newNode->val = val;
    newNode->priority = priority;
    newNode->next = NULL;

    // Insert at rear for O(1)
    q->rear->next = newNode;
    q->rear = newNode;
    q->size++;
}


/*Deletes the element with minimum priority (O(n) time)*/
int DeleteWithPriority(Queue q)
{
    if (IsEmptyQueue(q)) {
        printf("The queue is empty\n");
        return -1;
    }

    struct Node *prev = q->front;      
    struct Node *curr = q->front->next; 
    struct Node *minPrev = prev;       
    struct Node *minNode = curr;       

    // Find the node with minimum priority
    while (curr != NULL) {
        if (curr->priority < minNode->priority) {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove minNode from the list
    minPrev->next = minNode->next;
    if (minNode == q->rear) // If the minNode was rear, update rear
        q->rear = minPrev;

    int val = minNode->val;
    free(minNode);
    q->size--;

    return val;
}

/* Inserts an element in sorted order (O(n) time) */
void InsertWithPrioritySorted(Queue q, int val, int priority)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Out of memory space\n");
        return;
    }

    newNode->val = val;
    newNode->priority = priority;
    newNode->next = NULL;

    struct Node *prev = q->front;
    struct Node *curr = q->front->next;

    // Traverse to find the correct position
    while (curr != NULL && curr->priority <= priority) {
        prev = curr;
        curr = curr->next;
    }

    // Insert between prev and curr
    prev->next = newNode;
    newNode->next = curr;

    // Update rear if inserted at the end
    if (curr == NULL)
        q->rear = newNode;

    q->size++;
}

/* Deletes the element with minimum priority (O(1) time) */
int DeleteMin(Queue q)
{
    if (IsEmptyQueue(q)) {
        printf("The queue is empty\n");
        return -1;
    }

    struct Node *minNode = q->front->next; // First real node
    int val = minNode->val;

    q->front->next = minNode->next;
    if (minNode == q->rear) // If it was the only node
        q->rear = q->front;

    free(minNode);
    q->size--;

    return val;
}


/* Stack push using priority queue
   insertOrder is passed from caller to maintain LIFO */
void StackPush(Queue q, int val, int insertOrder)
{
    int priority = -insertOrder; // negative so most recent element has lowest priority
    InsertWithPrioritySorted(q, val, priority);
}

/* Stack pop using priority queue */
int StackPop(Queue q)
{
    return DeleteMin(q);
}


/* Queue enqueue using priority queue (FIFO)
   insertOrder is passed from caller to maintain FIFO */
void QueueEnqueue(Queue q, int val, int insertOrder)
{
    int priority = insertOrder;
    InsertWithPrioritySorted(q, val, priority);
}

/* Queue dequeue using priority queue */
int QueueDequeue(Queue q)
{
    return DeleteMin(q);
}


/* Insert into max-priority queue using a min-priority queue */
void MaxPQInsert(Queue q, int val)
{
    int priority = -val;
    InsertWithPrioritySorted(q, val, priority);
}

/* Delete from max-priority queue */
int MaxPQDelete(Queue q)
{
    return DeleteMin(q);          
}


/*This function initialises the queue*/
Queue CreateQueue(int maxElements)
{
    Queue q;

    q = (struct QueueRecord *) malloc(sizeof(struct QueueRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyQueue(q);
    return q;
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
    q->size = 0;
    q->front = (struct Node *) malloc(sizeof(struct Node));
    if (q->front == NULL)
        printf("Out of memory space\n");
    else{
        q->front->next = NULL;
        q->rear = q->front;
    }
}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
    return (q->size == 0);
}

/*Returns the queue size*/
int QueueSize(Queue q)
{
    return (q->size);
}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->front->next->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->rear->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *pos;

    pos=q->front->next;
    printf("Queue content:\n");

    printf("-->Priority   Value\n");
    while (pos != NULL)
    {
        printf("--> %d\t     %d\n", pos->priority, pos->val);
        pos = pos->next;
    }
}
