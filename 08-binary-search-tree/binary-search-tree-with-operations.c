#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define MAX(a,b) (((a)>(b))?(a):(b))

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

typedef struct Node *Tree;

// --- LINKED LIST STACK ADT (For Iterative In-Order) ---
struct StackNode {
    Tree data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

void InitStack(struct Stack* s) {
    s->top = NULL;
}

int IsStackEmpty(struct Stack* s) {
    return s->top == NULL;
}

void Push(struct Stack* s, Tree t) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Stack Overflow\n");
        return;
    }
    newNode->data = t;
    newNode->next = s->top;
    s->top = newNode;
}

Tree Pop(struct Stack* s) {
    if (IsStackEmpty(s))
        return NULL;

    struct StackNode* temp = s->top;
    Tree data = temp->data;

    s->top = temp->next;
    free(temp);

    return data;
}

// --- LINKED LIST QUEUE ADT (For Level Order) ---

struct QueueNode {
    Tree data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

void InitQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int IsQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}

void Enqueue(struct Queue* q, Tree t) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode == NULL) {
        printf("Queue Overflow\n");
        return;
    }

    newNode->data = t;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Tree Dequeue(struct Queue* q) {
    if (IsQueueEmpty(q))
        return NULL;

    struct QueueNode* temp = q->front;
    Tree data = temp->data;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return data;
}

// --- FUNCTION SIGNATURES ---

// Template Functions
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree);       

// Search Functions
Tree IterativeFindMinimum(Tree t);       
Tree IterativeFindMaximum(Tree t);       
Tree RecursiveFindMaximum(Tree t);       
Tree RecursiveFindMinimum(Tree t);       
Tree FindElement(int val, Tree t);       

// Structure & Modification
Tree DeleteBinarySearchTree(int val, Tree t);   
void PrintBinaryTreeStructure(Tree t, int level);

// Properties
int CountNodes(Tree t);            
int CountLeaves(Tree t);           
int TreeHeight(Tree t);            
Tree CopyTree(Tree t);             
int IdenticalTrees(Tree t1, Tree t2); 

// Advanced Traversal
Tree IterativeInsert(int val, Tree t); 
void LevelOrderTraversal(Tree t);      
void InOrderDisplayStack(Tree t);      


// --- FUNCTION IMPLEMENTATIONS ---

/* Recursive Insertion */
Tree InsertElement(int val, Tree t) {
    if (t == NULL) {
        t = (Tree)malloc(sizeof(struct Node));
        if (t == NULL) {
            printf("Out of space!!!\n");
            return NULL;
        }
        t->val = val;
        t->left = t->right = NULL;
    }
    else if (val < t->val)
        t->left = InsertElement(val, t->left);
    else if (val > t->val)
        t->right = InsertElement(val, t->right);
    // Else: value is already in the tree, do nothing.

    return t;
}

Tree CreateTree(void) {
    return NULL;
}

Tree MakeEmptyTree(Tree t) {
    if (t != NULL) {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

/* Recursive In-Order Traversal */
void DisplayTree(Tree t) {
    if (t != NULL) {
        DisplayTree(t->left);
        printf("%d\n", t->val);
        DisplayTree(t->right);
    }
}

/* Iterative Find Minimum */
Tree IterativeFindMinimum(Tree t) {
    if (t == NULL)
        return NULL;

    while (t->left != NULL)
        t = t->left;

    return t;
}

/* Iterative Find Maximum */
Tree IterativeFindMaximum(Tree t) {
    if (t == NULL)
        return NULL;

    while (t->right != NULL)
        t = t->right;

    return t;
}

/* Recursive Find Maximum */
Tree RecursiveFindMaximum(Tree t) {
    if (t == NULL)
        return NULL;

    if (t->right == NULL)
        return t;

    return RecursiveFindMaximum(t->right);
}

/* Recursive Find Minimum */
Tree RecursiveFindMinimum(Tree t) {
    if (t == NULL)
        return NULL;

    if (t->left == NULL)
        return t;

    return RecursiveFindMinimum(t->left);
}

/* Recursive Find Element */
Tree FindElement(int val, Tree t) {
    if (t == NULL)
        return NULL;

    if (val < t->val)
        return FindElement(val, t->left);
    else if (val > t->val)
        return FindElement(val, t->right);
    else
        return t;
}

/* Delete Function */
Tree DeleteBinarySearchTree(int val, Tree t) {
    Tree current = t;
    Tree parent = NULL;

    // 1. Find Node
    while (current != NULL && current->val != val) {
        parent = current;
        if (val < current->val)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return t; // Not found

    // 2. Handle 2 Children
    if (current->left != NULL && current->right != NULL) {
        Tree succ = current->right;
        Tree succParent = current;

        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        current->val = succ->val;
        current = succ;
        parent = succParent;
    }

    // 3. Handle 0 or 1 Child
    Tree child;
    if (current->left != NULL)
        child = current->left;
    else
        child = current->right;

    if (parent == NULL) {
        Tree temp = child;
        free(current);
        return temp; // New root
    }
    else {
        if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;

        free(current);
        return t;
    }
}

// Change signature in declaration too!
void PrintBinaryTreeStructure(Tree t, int level){
    if (t == NULL)
        return;

    // 1. Go Right (Increase level)
    PrintBinaryTreeStructure(t->right, level + 1);

    // 2. Create Format
    for (int i = 0; i < level; ++i) {
        printf("      ");
    }
    printf("%d\n", t->val);

    // 3. Go Left (Increase level)
    PrintBinaryTreeStructure(t->left, level + 1);
}

/* Count Nodes */
int CountNodes(Tree t) {
    if (t == NULL)
        return 0;

    return 1 + CountNodes(t->left) + CountNodes(t->right);
}

/* Count Leaf Number */
int CountLeaves(Tree t) {
    if (t == NULL)
        return 0;

    if (t->left == NULL && t->right == NULL)
        return 1;

    return CountLeaves(t->left) + CountLeaves(t->right);
}

/* Find Tree Height */
int TreeHeight(Tree t) {
    if (t == NULL)
        return -1;

    return 1 + MAX(TreeHeight(t->left), TreeHeight(t->right));
}

/* Copy The Tree */
Tree CopyTree(Tree t) {
    if (t == NULL)
        return NULL;

    Tree newNode = (Tree)malloc(sizeof(struct Node));
    newNode->val = t->val;
    newNode->left = CopyTree(t->left);
    newNode->right = CopyTree(t->right);

    return newNode;
}

/* Check Identical Trees */
int IdenticalTrees(Tree t1, Tree t2) {
    if (t1 == NULL && t2 == NULL)
        return 1;

    if (t1 == NULL || t2 == NULL)
        return 0;

    if (t1->val != t2->val)
        return 0;

    return IdenticalTrees(t1->left, t2->left) && IdenticalTrees(t1->right, t2->right);
}

/* Iterative Insert */
Tree IterativeInsert(int val, Tree t) {
    Tree newNode = (Tree)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->left = newNode->right = NULL;

    if (t == NULL)
        return newNode;

    Tree current = t;
    Tree parent = NULL;

    while (current != NULL) {
        parent = current;
        if (val < current->val)
            current = current->left;
        else if (val > current->val)
            current = current->right;
        else {
            free(newNode);
            return t;
        }
    }

    if (val < parent->val)
        parent->left = newNode;
    else
        parent->right = newNode;

    return t;
}

/* Level Order (Queue based) */
void LevelOrderTraversal(Tree t) {
    if (t == NULL)
        return;

    struct Queue q;
    InitQueue(&q);
    Enqueue(&q, t);

    while (!IsQueueEmpty(&q)) {
        Tree current = Dequeue(&q);
        printf("%d ", current->val);

        if (current->left)
            Enqueue(&q, current->left);

        if (current->right)
            Enqueue(&q, current->right);
    }
    printf("\n");
}

/* In Order (Stack based) */
void InOrderDisplayStack(Tree t) {
    if (t == NULL)
        return;

    struct Stack s;
    InitStack(&s);
    Tree current = t;

    while (current != NULL || !IsStackEmpty(&s)) {
        while (current != NULL) {
            Push(&s, current);
            current = current->left;
        }

        current = Pop(&s);
        printf("%d ", current->val);
        current = current->right;
    }
    printf("\n");
}