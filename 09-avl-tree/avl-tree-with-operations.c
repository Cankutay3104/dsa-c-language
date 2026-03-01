#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

typedef struct Node *AVLTree;
struct Node
{
    int val;
    AVLTree left;
    AVLTree right;
    int height;
};

AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree InsertElement(int, AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
void DisplayTree(AVLTree);
void DisplayTreeStructure(AVLTree, int);
int AVLTreeHeight(AVLTree);
int Max(int, int);

/* Helper functions */
int TreeHeight(AVLTree t);
int BalanceFactor(AVLTree t);
void DisplayTreeStructureWithBF(AVLTree t, int depth);
int IsAVL(AVLTree t);
void PrintTreeLevelOrder(AVLTree t);
AVLTree DeleteElement(int val, AVLTree t);
AVLTree CreateAvlTree(void);
void CheckGuess(AVLTree t);


AVLTree CreateTree(void)
{
    return NULL;
}

AVLTree MakeEmptyTree(AVLTree t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

AVLTree InsertElement(int val, AVLTree t)
{
    if (t == NULL)
    {
        t = malloc(sizeof(struct Node));
        if (t == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            t->val = val; t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if (val<t->val)
    {
        t->left = InsertElement(val, t->left);

        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
            if (val < t->left->val)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithLeft(t);
    }
    else if (val > t->val)
    {
        t->right = InsertElement(val, t->right);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
            if (val > t->right->val)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithRight(t);
    }
    /* else val is already in the tree, do nothing */
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
}

void DisplayTree(AVLTree t)
{
    if (t != NULL)
    {
        DisplayTree(t->left);
        printf("%d\n", t->val);
        DisplayTree(t->right);
    }
}

void DisplayTreeStructure(AVLTree t, int depth)
{
    int i;

    if (t != NULL)
    {
        DisplayTreeStructure(t->right, depth + 1);

        for (i = 0; i < depth; i++)
            printf("     ");
        printf("%d\n", t->val);

        DisplayTreeStructure(t->left, depth + 1);
    }
}

int AVLTreeHeight(AVLTree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}

int BalanceFactor(AVLTree t){
    if (t == NULL)
        return 0;
    return AVLTreeHeight(t->left) - AVLTreeHeight(t->right);
}

void DisplayTreeStructureWithBF(AVLTree t, int depth){
    if (t == NULL)
        return;

    DisplayTreeStructureWithBF(t->right, depth + 1);

    for (int i = 0; i < depth; ++i) {
        printf("     ");
    }
    printf("%d[%d]\n", t->val, BalanceFactor(t));

    DisplayTreeStructureWithBF(t->left, depth +1);

}

int IsAVL(AVLTree t)
{
    if (t == NULL)
        return TRUE;

    int bf = BalanceFactor(t);
    if (bf < -1 || bf > 1)
        return FALSE;

    return IsAVL(t->left) && IsAVL(t->right);
}


// Right rotation
AVLTree SingleRotateWithRight(AVLTree k2)
{
    AVLTree k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) +1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;

    return k1;
}

// left rotation
AVLTree SingleRotateWithLeft(AVLTree k1)
{
    AVLTree k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) +1;
    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) +1;

    return k2;
}

// left and right rotation
AVLTree DoubleRotateWithLeft(AVLTree k3)
{
//    --- Preferred version ---
   k3->left = SingleRotateWithLeft(k3->left);
   return SingleRotateWithRight(k3);

//    --- Manual version ---
/*    AVLTree k2 = k3->left;
    AVLTree k1 = k2->right;

    k2->right = k1->left;
    k1->left = k2;

    k3->left = k1->right;
    k1->right = k3;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) +1;
    k3->height = Max(AVLTreeHeight(k3->left), AVLTreeHeight(k3->right)) +1;
    k1->height = Max(k2->height, k3->height) + 1;

    return k1;
*/
}

// Right and left rotation
AVLTree DoubleRotateWithRight(AVLTree k3)
{
//    --- Preferred version ---
   k3->right = SingleRotateWithRight(k3->right);
   return SingleRotateWithLeft(k3);

//    --- Manual version ---
/*    AVLTree k2 = k3->right;
    AVLTree k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;

    k3->right = k1->left;
    k1->left = k3;

    k3->height = Max(AVLTreeHeight(k3->left), AVLTreeHeight(k3->right)) +1;
    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) +1;
    k1->height = Max(k2->height, k3->height) + 1;

    return k1;
*/
}

AVLTree DeleteElement(int val, AVLTree t)
{
    if (t == NULL) return NULL;

    if (val < t->val)
    {
        t->left = DeleteElement(val, t->left);
    }
    else if (val > t->val)
    {
        t->right = DeleteElement(val, t->right);
    }
    else
    {
        // Found the node to delete

        // Case 0 or 1 child
        if (t->left == NULL || t->right == NULL)
        {
            AVLTree child = (t->left != NULL) ? t->left : t->right;

            if (child == NULL)
            {
                // 0 child
                free(t);
                return NULL;
            }
            else
            {
                // 1 child: replace node with its child
                AVLTree old = t;
                t = child;
                free(old);
            }
        }
        else
        {
            // Case 2 children: explicitly find inorder successor (leftmost of right subtree)
            AVLTree suc = t->right;
            while (suc->left != NULL)
                suc = suc->left;

            // Copy successor's value into current node
            t->val = suc->val;

            // Delete successor from right subtree
            t->right = DeleteElement(suc->val, t->right);
        }
    }

    // If tree became empty
    if (t == NULL) return NULL;

    // Update height (template uses -1 for NULL, so this matches)
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    // Rebalance exactly like InsertElement does, but using subtree heights
    // Left-heavy
    if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
    {
        // If left-left (or left is balanced/left-heavy) => single right rotation
        if (AVLTreeHeight(t->left->left) >= AVLTreeHeight(t->left->right))
            t = SingleRotateWithRight(t);      // RIGHT rotation (LL)
        else
            t = DoubleRotateWithLeft(t);       // LR
    }
        // Right-heavy
    else if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
    {
        // If right-right (or right is balanced/right-heavy) => single left rotation
        if (AVLTreeHeight(t->right->right) >= AVLTreeHeight(t->right->left))
            t = SingleRotateWithLeft(t);       // LEFT rotation (RR)
        else
            t = DoubleRotateWithRight(t);      // RL
    }

    // Update height again (rotations change children)
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
}

AVLTree CreateAvlTree(void){
    AVLTree t = CreateTree();
    for(int i = 0; i < 6; i++){
        int x = rand() % 101;
        t = InsertElement(x, t);
    }
    return t;
}


void PrintTree(AVLTree t){
    if (t == NULL)
        return;

    printf("%d, ", t->val);
    PrintTree(t->left);
    PrintTree(t->right);
};

void CheckGuess(AVLTree t){

    int num;
    printf("Guess a number: ");
    scanf("%d", &num);

    AVLTree current = t;
    while (current != NULL && current->val != num){
        if (current->val > num)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        printf("You lose!\n");
    else
        printf("You win!\n");

    printf("Tree structure is: ");
    PrintTree(t);
    printf("\n");
}

int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}