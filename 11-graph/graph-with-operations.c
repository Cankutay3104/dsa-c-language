#include <stdio.h>
#include <stdlib.h>

struct Vertex; // Forward declaration to use in main declaration

struct Arc {
    struct Vertex *destination;
    struct Arc *nextArc;
};

struct Vertex {
    char data;
    int inDegree, outDegree;
    struct Vertex *nextVertex;
    struct Arc *firstArc;
    int processed; // Helpful for traversals (0: unvisited, 1: visited)
};

struct Graph {
    int count;
    struct Vertex *first;
};

// --- Stack Implementation ---

struct SNode {
    struct Vertex *data;
    struct SNode *next;
};

struct Stack {
    struct SNode *top;
};

// --- Queue Implementation ---

struct QNode {
    struct Vertex *data;
    struct QNode *next;
};

struct Queue {
    struct QNode *front;
    struct QNode *rear;
};

// --- Stack Functions ---

struct Stack* createStack(void){
    struct Stack *s = malloc(sizeof(struct Stack));
    if (s == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

int isEmptyStack(struct Stack *s){
    return (s->top == NULL);
}

void push(struct Stack *s, struct Vertex *v){
    struct SNode *newNode = malloc(sizeof(struct SNode));
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = v;
    newNode->next = s->top;
    s->top = newNode;
}

struct Vertex* pop(struct Stack *s){
    if (isEmptyStack(s)) return NULL;

    struct SNode *temp = s->top;
    struct Vertex *v = temp->data;

    s->top = temp->next;
    free(temp);
    return v;
}

struct Vertex* peek(struct Stack *s){
    if (isEmptyStack(s)) return NULL;
    return s->top->data;
}

void destroyStack(struct Stack *s){
    while (!isEmptyStack(s))
        pop(s);
    free(s);
}

// --- Queue Functions ---

struct Queue* createQueue(void){
    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    return q;
}

int isEmptyQueue(struct Queue *q){
    return (q->front == NULL);
}

void enqueue(struct Queue *q, struct Vertex *v){
    struct QNode *newNode = malloc(sizeof(struct QNode));
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = v;
    newNode->next = NULL;

    if (q->rear == NULL){           // empty queue
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

struct Vertex* dequeue(struct Queue *q){
    if (isEmptyQueue(q)) return NULL;

    struct QNode *temp = q->front;
    struct Vertex *v = temp->data;

    q->front = temp->next;
    if (q->front == NULL)           // queue became empty
        q->rear = NULL;

    free(temp);
    return v;
}

// --- MAIN Functions ---

struct Graph* createGraph(void);
void printGraph(struct Graph* graph);
void insertVertex(struct Graph* graph, char data);
void deleteVertex(struct Graph* graph, char key);
void insertArc(struct Graph* graph, char fromKey, char toKey);
void deleteArc(struct Vertex* fromV, struct Vertex* toV);
struct Vertex* findVertex(struct Graph* graph, char key);
void DFT(struct Vertex* v);
void BFT(struct Graph* graph, char startKey);
int sumDegrees(struct Graph* graph, char key);
int isDisjoint(struct Graph* graph, char key);



struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph) {
        graph->count = 0;
        graph->first = NULL;
    }
    return graph;
}

void printGraph(struct Graph* graph){
    if (graph == NULL || graph->first == NULL) return;

    struct Vertex *v = graph->first;
    while (v != NULL){
        printf("%c -> ", v->data);

        struct Arc *a = v->firstArc;    // reset for this vertex
        while (a != NULL){
            printf("%c", a->destination->data);
            a = a->nextArc;             // move to next arc
            if (a != NULL) printf(" -> ");
        }
        printf(" |\n");
        v = v->nextVertex;
    }
}

void insertVertex(struct Graph* graph, char data){
//    prevents NULL graph, not empty graph
    if (graph == NULL)
        return;

    // Optional: avoid duplicates
    if (findVertex(graph, data) != NULL) return;

    struct Vertex *newVertex = malloc(sizeof(struct Vertex));
    if (newVertex == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newVertex->data = data;
    newVertex->inDegree = 0;
    newVertex->outDegree = 0;
    newVertex->firstArc = NULL;
    newVertex->processed = 0;

    newVertex->nextVertex = graph->first; // insert at head
    graph->first = newVertex;

    graph->count++; // important
}


void deleteVertex(struct Graph* graph, char key){
    if (graph == NULL || graph->first == NULL) return;

    // 1) find target vertex and prev
    struct Vertex *prevV = NULL;
    struct Vertex *target = graph->first;

    while (target != NULL && target->data != key){
        prevV = target;
        target = target->nextVertex;
    }
    if (target == NULL) return; // not found

    // 2) delete all incoming arcs to target
    for (struct Vertex *v = graph->first; v != NULL; v = v->nextVertex){
        if (v != target){
            // keep deleting until no arc remains (safe even if there is at most one)
            while (1){
                int before = v->outDegree;
                deleteArc(v, target);
                if (v->outDegree == before) break; // nothing deleted => stop
            }
        }
    }

    // 3) delete all outgoing arcs from target
    while (target->firstArc != NULL){
        struct Vertex *to = target->firstArc->destination;
        deleteArc(target, to);
    }

    // 4) unlink vertex node from list
    if (prevV == NULL) graph->first = target->nextVertex; // target was head
    else prevV->nextVertex = target->nextVertex;

    free(target);
    graph->count--;
}


// Insert Arc (Directed: fromSource -> toDest)
void insertArc(struct Graph* graph, char fromKey, char toKey){
    if (graph == NULL) return;

    struct Vertex *from = findVertex(graph, fromKey);
    struct Vertex *to   = findVertex(graph, toKey);
    if (from == NULL || to == NULL) return;

    // Optional: prevent duplicate arc
    for (struct Arc *a = from->firstArc; a != NULL; a = a->nextArc)
        if (a->destination == to) return;

    struct Arc *newArc = malloc(sizeof(struct Arc));
    if (newArc == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newArc->destination = to;
    newArc->nextArc = from->firstArc;  // keep old list
    from->firstArc = newArc;

    from->outDegree++;
    to->inDegree++;
}


// Delete Arc (Helper for Delete Vertex)
void deleteArc(struct Vertex* fromV, struct Vertex* toV){
    if (fromV == NULL || toV == NULL) return;

    struct Arc *prev = NULL;
    struct Arc *cur  = fromV->firstArc;

    while (cur != NULL && cur->destination != toV){
        prev = cur;
        cur = cur->nextArc;
    }

    if (cur == NULL) return; // arc not found

    // unlink
    if (prev == NULL) fromV->firstArc = cur->nextArc; // deleting first arc
    else prev->nextArc = cur->nextArc;

    fromV->outDegree--;
    toV->inDegree--;
    free(cur);
}


// Retrieve a Vertex
struct Vertex* findVertex(struct Graph* graph, char key){
    if (graph == NULL)
        return NULL;

    struct Vertex *search = graph->first;
    while (search != NULL && search->data != key)
        search = search->nextVertex;

    return search; // NULL if not found
}

// Depth First Traversal (Recursive) (With Stack)
void DFT(struct Vertex* start){
    //    Optional Version w/o Stack:
/*
   if (v == NULL) return;

   printf("%c ", v->data);
   v->processed = 1;

   struct Arc *a = v->firstArc;
   while (a != NULL){
       if (a->destination->processed == 0){
           DFT(a->destination);
       }
       a = a->nextArc;
   }
*/

    if (start == NULL) return;

    struct Stack *s = createStack();

    // Mark when discovered (pushed) to avoid pushing same vertex many times
    start->processed = 1;
    push(s, start);

    while (!isEmptyStack(s)){
        struct Vertex *v = pop(s);
        printf("%c ", v->data);

        // Push all unvisited adjacent vertices
        struct Arc *a = v->firstArc;
        while (a != NULL){
            if (a->destination->processed == 0){
                a->destination->processed = 1;
                push(s, a->destination);
            }
            a = a->nextArc;
        }
    }

    destroyStack(s);

}


// Breadth First Traversal (With Queue)
void BFT(struct Graph* graph, char startKey){
    if (graph == NULL) return;

    struct Vertex *start = findVertex(graph, startKey);
    if (start == NULL) return;

    // Reset processed flags
    for (struct Vertex *v = graph->first; v != NULL; v = v->nextVertex)
        v->processed = 0;

    struct Queue *q = createQueue();

    start->processed = 1;
    enqueue(q, start);

    while (!isEmptyQueue(q)){
        struct Vertex *v = dequeue(q);
        printf("%c ", v->data);

        struct Arc *a = v->firstArc;
        while (a != NULL){
            if (a->destination->processed == 0){
                a->destination->processed = 1;
                enqueue(q, a->destination);
            }
            a = a->nextArc;
        }
    }

    free(q); // queue nodes already freed during dequeue
}


int sumDegrees(struct Graph* graph, char key){
    if (graph == NULL)
        return -1;

    struct Vertex *v = findVertex(graph, key);
    if (v == NULL)
        return -1;

    int sum = v->inDegree + v->outDegree;
    return sum;
}


int isDisjoint(struct Graph* graph, char key){
    if (graph == NULL) return 1;            /* treat missing graph as disjoint */
    if (graph->first == NULL) return 0;     /* empty graph: usually "not disjoint" */

    struct Vertex *start = findVertex(graph, key);
    if (start == NULL) return 1;

    /* reset processed */
    for (struct Vertex *v = graph->first; v != NULL; v = v->nextVertex)
        v->processed = 0;

    /* traverse from start without printing */
    struct Stack *s = createStack();
    start->processed = 1;
    push(s, start);

    while (!isEmptyStack(s)){
        struct Vertex *v = pop(s);
        for (struct Arc *a = v->firstArc; a != NULL; a = a->nextArc){
            if (a->destination->processed == 0){
                a->destination->processed = 1;
                push(s, a->destination);
            }
        }
    }
    destroyStack(s);

    /* if any vertex unvisited => disjoint */
    for (struct Vertex *v = graph->first; v != NULL; v = v->nextVertex)
        if (v->processed == 0) return 1;

    return 0;
}