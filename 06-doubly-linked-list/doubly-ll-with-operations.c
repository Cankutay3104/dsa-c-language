#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

struct Node
{
    int val;
    struct Node *next;
    struct Node *prev;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int length;
};
typedef struct ListRecord *DoubleList;

DoubleList CreateList(int);
void MakeEmptyList(DoubleList);
void InsertListAtPosition(DoubleList, int, int);
void DisplayList(DoubleList);
int DeleteListAtPosition(DoubleList l, int pos);
int IsEmptyList(DoubleList l);
int GetElementAtPosition(DoubleList l, int pos);
int GetPositionOfElement(DoubleList l, int value);
void BrowseForward(DoubleList l);
void BrowseBackward(DoubleList l);
int ListSize(DoubleList l);



DoubleList CreateList(int size)
{
    DoubleList l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL){
        printf("Out of memory!\n");
        return NULL;
    }
    else{
        MakeEmptyList(l);
        return l;
    }
}

void MakeEmptyList(DoubleList l)
{
    struct Node *p = l->head, *tmp;

    if(p != NULL) {
        p = p->next;
        while(p != NULL){
            tmp = p;
            p = p->next;
            free(tmp);
        }
        l->head->next = NULL;
        l->tail = l->head;
        l->length = 0;
        return;
    }

    l->head = malloc(sizeof(struct Node));
    if(l->head == NULL){
        printf("Out of memory!\n");
        exit(1);
    }

    l->head->next = NULL;
    l->head->prev = NULL;
    l->tail = l->head;
    l->length = 0;

}

void InsertListAtPosition(DoubleList l, int pos, int val)
{
    if(pos < 0 || pos > l->length){
        printf("Invalid position!\n");
        return;
    }

    struct Node *current = l->head;
    for(int i=0; i<pos; i++)
        current = current->next;

    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->val = val;
    newNode->next = current->next;
    newNode->prev = current;

    if(current->next != NULL)
        current->next->prev = newNode;
    else
        l->tail = newNode;

    current->next = newNode;

    l->length++;
}

void DisplayList(DoubleList l)
{
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL)
    {
        printf("--> %d\t", p->val);
        p = p->next;
    }
}

int DeleteListAtPosition(DoubleList l, int pos)
{
    if(IsEmptyList(l) || pos < 0 || pos >= l->length)
        return -1;

    struct Node *current = l->head->next;

    for(int i=0; i<pos; i++)
        current = current->next;

    int val = current->val;

    current->prev->next = current->next;

    if(current->next != NULL)
        current->next->prev = current->prev;
    else
        l->tail = current->prev;

    free(current);
    l->length--;

    return val;
}

int IsEmptyList(DoubleList l){
    return l->length == 0;
}

int GetElementAtPosition(DoubleList l, int pos){
    if(IsEmptyList(l)){
        printf("List is empty. Returning -1.\n");
        return -1;
    }
    struct Node *current = l->head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    return current->val;
}

int GetPositionOfElement(DoubleList l, int value){
    if(IsEmptyList(l)){
        printf("List is empty. Returning -1.\n");
        return -1;
    }
    struct Node *current = l->head;
    int counter = 0;
    while(current->val != value && current != NULL){
        current = current->next;
        ++counter;
    }

    if(current == NULL){
        printf("There is no such value in the list.\n");
        return -1;
    }

    return counter;
}

void BrowseForward(DoubleList l){
    struct Node *current = l->head->next;
    while(current != NULL){
        printf("--> %d ", current->val);
        current = current->next;
    }
    printf("\n");
}

void BrowseBackward(DoubleList l){
    struct Node *current = l->tail;
    while(current != NULL){
        printf(" %d <--", current->val);
        current = current->prev;
    }
    printf("\n");
}

int ListSize(DoubleList l){
    return l->length;
}
