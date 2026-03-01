#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node {
    int val;
    struct Node *next;
};

typedef struct Node StackRecord;
typedef StackRecord *Stack;

Stack CreateStack();
void MakeEmptyStack(Stack s);
int IsEmptyStack(Stack s);
void PushStack(int x, Stack s);
int PopStack(Stack s);
int TopOfStack(Stack s);
void DisplayStack(Stack s);


//This function initialises a stack with a dummy node
Stack CreateStack()
{
    Stack head = (Stack) malloc(sizeof(StackRecord));
    if (!head) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    head->next = NULL; // dummy node's next is first element (NULL = empty)
    head->val = 0; // dummy value unused
    return head;
}

//This function empties the content of a stack
void MakeEmptyStack(Stack s)
{
    if (!s) return;

    struct Node *p = s->next;
    while (p != NULL) {
        struct Node *tmp = p;
        p = p->next;
        free(tmp);
    }
    s->next = NULL;

}

//This function checks if a stack is empty or not
int IsEmptyStack(Stack s)
{
    return s->next == NULL;
}

//This function checks if a stack is full
int IsFullStack(Stack s)
{
    return FALSE;
}

//This function creates a new node, adds the value of x to this node
//and then pushes this new node to the given stack
void PushStack(int x, Stack s)
{
    if (!s) return;

    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    if (!node) {
        fprintf(stderr, "Push: memory allocation failed\n");
        return;
    }
    node->val = x;
    node->next = s->next;
    s->next = node;

}

//This function pops the top node from the stack frees the memory location
//of that node and returns the value stored in that top node
int PopStack(Stack s)
{
    if (IsEmptyStack(s)) {
        return -1; // sentinel when empty
    }

    struct Node *node = s->next;
    int val = node->val;
    s->next = node->next;
    free(node);
    return val;
}

//This function returns the value stored at the top node
int TopOfStack(Stack s)
{
    if(IsEmptyStack(s)) return -1;
    return s->next->val;
}

//This function displays the content of a stack
void DisplayStack(Stack s)
{
    struct Node *p;
    printf("Stack content:\n");
    if (IsEmptyStack(s))
        printf("The stack is empty!\n");
    else{
        p = s->next;
        while (p != NULL)
        {
            printf("\t--> %d\n", p->val);
            p = p->next;
        }
    }
}
