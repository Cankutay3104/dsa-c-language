#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node
{
    int  val;
    struct Node *next;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;

List CreateList(void);
void MakeEmptyList(List);
int ListSize(List);
int HeadOfList(List);
int TailOfList(List);
int IsEmptyList(List);
void DisplayList(List);
void InsertList(List l, int pos, int value);
void DeleteList(List l, int value);
int GetElementAtPosition(List l, int pos);
int GetPositionOfElement(List l, int value);
void SortedInsert(List l, struct Node* node);
void InsertSort(List l);

int main (){

    // You can pass any command you would like to try.

    return 0;
}

List CreateList()
{
    List l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!\n");
    else
        MakeEmptyList(l);

    return l;
}

void MakeEmptyList(List l)
{
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");

    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}

int IsEmptyList(List l)
{
    return (l->size == 0);
}

int ListSize(List l)
{
    return (l->size);
}

int HeadOfList(List l)
{
    if (!IsEmptyList(l))
        return l->head->next->val;
    else
    {
        printf("The linked list is empty\n");
        return -1;
    }
}

int TailOfList(List l)
{
    if (!IsEmptyList(l))
        return l->tail->val;
    else
    {
        printf("The linked list is empty\n");
        return -1;
    }
}

void DisplayList(List l)
{
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL)
    {
        printf("--> %d\t", p->val);
        p = p->next;
    }
    printf("\n");
}

void InsertList(List l, int pos, int value) {
    if (pos < 0 || pos > l->size) {
        printf("Invalid position!\n");
        return;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->val = value;
    temp->next = NULL;

    // find the node *before* insertion point
    struct Node *current = l->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    // link in new node
    temp->next = current->next;
    current->next = temp;

    // if inserted at the end, update tail
    if (temp->next == NULL)
        l->tail = temp;

    l->size++;
}


void DeleteList(List l, int value) {
    if (IsEmptyList(l)) {
        printf("List is empty!\n");
        return;
    }

    struct Node *prev = l->head;
    struct Node *current = l->head->next;

    while (current != NULL && current->val != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value %d not found.\n", value);
        return;
    }

    prev->next = current->next;
    if (current == l->tail)
        l->tail = prev;

    free(current);
    l->size--;
}


int GetElementAtPosition(List l, int pos) {
    if (pos < 0 || pos >= l->size) {
        printf("Invalid position!\n");
        return -1;
    }

    struct Node *temp = l->head->next;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    return temp->val;
}

int GetPositionOfElement(List l, int value) {
    struct Node *temp = l->head->next;
    int pos = 0;

    while (temp != NULL) {
        if (temp->val == value)
            return pos;
        temp = temp->next;
        pos++;
    }

    printf("Value %d not found.\n", value);
    return -1;
}

void SortedInsert(List l, struct Node* node) {
    struct Node *prev = l->head;
    struct Node *curr = l->head->next;

    while (curr != NULL && curr->val < node->val) {
        prev = curr;
        curr = curr->next;
    }

    node->next = curr;
    prev->next = node;

    if (curr == NULL)
        l->tail = node;

    l->size++;
}

void InsertSort(List l) {
    struct Node *sorted = (struct Node *)malloc(sizeof(struct Node));
    sorted->next = NULL;
    struct Node *current = l->head->next;

    // reset tail and size
    l->tail = sorted;
    l->size = 0;

    while (current != NULL) {
        struct Node *next = current->next;
        SortedInsert(l, current);
        current = next;
    }

    l->head = sorted;
}

