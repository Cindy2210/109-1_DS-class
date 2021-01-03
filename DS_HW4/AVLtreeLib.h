#ifndef AVLtreeLib
#define AVLtreeLib

typedef struct avl_node
{
    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
    int height; // tree height
} avlNode_t;

/*
static int RightHigh(avlNode_t *root);
static int LeftHigh(avlNode_t *root);
static void getHigh(avlNode_t *root);
static avlNode_t *rotatR(avlNode_t **tree, avlNode_t *root);
static avlNode_t *rotatL(avlNode_t **tree, avlNode_t *root);
static avlNode_t *RR(avlNode_t **tree, avlNode_t *root);
static avlNode_t *LR(avlNode_t **tree, avlNode_t *root);
static avlNode_t *LL(avlNode_t **tree, avlNode_t *root);
static avlNode_t *RL(avlNode_t **tree, avlNode_t *root);
static int findprebF(avlNode_t *root);
static void bF(avlNode_t **tree, avlNode_t *root);
*/
void Insert(void *elemt, avlNode_t **tree, int (*cp)(void *eleA, void *eleB));
avlNode_t *Find(avlNode_t *root, void *elemt, int (*cp)(void *eleA, void *eleB));
/*
static avlNode_t *findMax(avlNode_t *root);
static avlNode_t *findMin(avlNode_t *root);
*/
void Delete(void *elemt, avlNode_t **tree, int (*cp)(void *eleA, void *eleB));

#endif
