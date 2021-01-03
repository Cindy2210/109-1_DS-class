#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AVLtreeLib.h"
//avlNode_t *avlRoot; //avl tree root

static int RightHigh(avlNode_t *root)
{
    int cous = 0;
    while (root)
    {
        cous++;
        root = root->right;
    }

    return cous;
}

static int LeftHigh(avlNode_t *root)
{
    int cous = 0;
    while (root)
    {
        cous++;
        root = root->left;
    }

    return cous;
}

static void getHigh(avlNode_t *root)
{
    if (root)
    {
        int L, R;
        if (root->left)
            L = root->left->height + 1;
        else
            L = 1;
        if (root->right)
            R = root->right->height + 1;
        else
            R = 1;

        if (L > R)
            root->height = L;
        else
            root->height = R;
        getHigh(root->parent);
    }
    return;
}



static avlNode_t *rotatR(avlNode_t **tree, avlNode_t *root)
{
    if (root->parent == (*tree))
    { //LL
        avlNode_t *rootR = root->right;
        root->right = NULL;
        if (rootR)
            rootR->parent = NULL;

        avlNode_t *rootParnt = root->parent;
        root->parent = NULL;
        rootParnt->left = NULL;

        root->right = rootParnt;
        rootParnt->parent = root;

        rootParnt->left = rootR;
        if (rootR)
            rootR->parent = rootParnt;

        (*tree) = root;
        return root->right;
    }
    else
    {
        avlNode_t *rootParnt = root->parent;
        root->parent = NULL;
        rootParnt->left = NULL;

        avlNode_t *rootGrand = rootParnt->parent;

        avlNode_t *rootR = root->right;
        root->right = NULL;
        if (rootR)
            rootR->parent = NULL;

        if (rootGrand->right == rootParnt)
        {
            rootGrand->right = NULL;
            rootParnt->parent = NULL;

            root->right = rootParnt;
            rootParnt->parent = root;

            rootParnt->left = rootR;
            if (rootR)
                rootR->parent = rootParnt;

            rootGrand->right = root;
            root->parent = rootGrand;
        }
        else //rootGrandf->left == rootParnt
        {    //LL
            rootGrand->left = NULL;
            rootParnt->parent = NULL;

            root->right = rootParnt;
            rootParnt->parent = root;

            rootParnt->left = rootR;
            if (rootR)
                rootR->parent = rootParnt;

            rootGrand->left = root;
            root->parent = rootGrand;
        }
        return root->right;
    }
}
static avlNode_t *rotatL(avlNode_t **tree, avlNode_t *root)
{
    if (root->parent == (*tree))
    {
        avlNode_t *rootL = root->left;
        root->left = NULL;
        if (rootL)
            rootL->parent = NULL;

        avlNode_t *rootParnt = root->parent;
        root->parent = NULL;
        rootParnt->right = NULL;

        root->left = rootParnt;
        rootParnt->parent = root;

        rootParnt->right = rootL;
        if (rootL)
            rootL->parent = rootParnt;

        (*tree) = root;
        return root->left;
    }
    else
    {
        avlNode_t *rootParnt = root->parent;
        root->parent = NULL;
        rootParnt->right = NULL;

        avlNode_t *rootGrandf = rootParnt->parent;

        avlNode_t *rootL = root->left;
        root->left = NULL;
        if (rootL)
            rootL->parent = NULL;

        if (rootGrandf->left == rootParnt)
        { //LR
            rootGrandf->left = NULL;
            rootParnt->parent = NULL;

            root->left = rootParnt;
            rootParnt->parent = root;

            rootParnt->right = rootL;
            if (rootL)
                rootL->parent = rootParnt;

            rootGrandf->left = root;
            root->parent = rootGrandf;
        }
        else //rootGrandf->right == rootParnt
        {    //RR
            rootGrandf->right = NULL;
            rootParnt->parent = NULL;

            root->left = rootParnt;
            rootParnt->parent = root;

            rootParnt->right = rootL;
            if (rootL)
                rootL->parent = rootParnt;

            rootGrandf->right = root;
            root->parent = rootGrandf;
        }
        return root->left;
    }
}

static avlNode_t *RR(avlNode_t **tree, avlNode_t *root)
{
    root = rotatL(tree, root->right);
    getHigh(root);
}
static avlNode_t *LR(avlNode_t **tree, avlNode_t *root)
{
    root = rotatL(tree, root->left->right);
    getHigh(root);
    root = rotatR(tree, root->parent);
    getHigh(root);
    
}
static avlNode_t *LL(avlNode_t **tree, avlNode_t *root)
{
    root = rotatR(tree, root->left);
    getHigh(root);
}
static avlNode_t *RL(avlNode_t **tree, avlNode_t *root)
{
    root = rotatR(tree, root->right->left);
    getHigh(root);
    root = rotatL(tree, root->parent);
    getHigh(root);
}

static int findprebF(avlNode_t *root)
{
    int L, R;
    if (root->left)
        L = root->left->height;
    else
        L = 0;
    if (root->right)
        R = root->right->height;
    else
        R = 0;
    int ans = L - R;
    return ans;
}
static void bF(avlNode_t **tree, avlNode_t *root)
{
    if (root)
    {
        int L, R;
        if (root->left == NULL)
            L = 0;
        else
            L = root->left->height;
        if (root->right == NULL)
            R = 0;
        else
            R = root->right->height;
        int balance = L - R;

        if (balance == 0 || balance == 1 || balance == -1)
            bF(tree, root->parent);
        else if (balance == 2) //type LL or type LR
        {
            if (findprebF(root->left) == 1) //type LL
            {
                LL(tree, root);
            }
            else if (findprebF(root->left) == -1) //type LR
            {
                LR(tree, root);
            }
        }
        else if (balance == -2)
        {
            if (findprebF(root->right) == 1) //type RL
            {
                RL(tree, root);
            }
            else if (findprebF(root->right) == -1) //type RR
            {
                RR(tree, root);
            }
        }
    }
    return;
}
/*�o�� AVL library �ܤֻݭn�H�U��functions*/
void Insert(void *elemt, avlNode_t **tree, int (*cp)(void *eleA, void *eleB))
{
    if (!(*tree))
    {
        (*tree) = ((avlNode_t *)elemt);
        getHigh((avlNode_t *)elemt);
        return;
    }

    avlNode_t *cur = *tree;
    avlNode_t *head = *tree;
    while (1)
    {
        if (cp((void *)cur, elemt) == 1 || cp((void *)cur, elemt) == 0) //cur >= elemt, go left
        {
            if (cur->left == NULL)
            {
                cur->left = ((avlNode_t *)elemt);
                ((avlNode_t *)elemt)->parent = cur;
                break;
            }
            cur = cur->left;
        }
        else if (cp(cur, elemt) == -1) //cur < elemt, go right
        {
            if (cur->right == NULL)
            {
                cur->right = ((avlNode_t *)elemt);
                ((avlNode_t *)elemt)->parent = cur;
                break;
            }
            cur = cur->right;
        }
    }
    getHigh((avlNode_t *)elemt);
    bF(tree, (avlNode_t *)elemt);
    return;
}
avlNode_t *Find(avlNode_t *root, void *elemt, int (*cp)(void *eleA, void *eleB))
{
    while (1)
    {
        if (!root)
            return NULL;
        else
        {
            if (cp(root, elemt) == 0)
                return root;
            else if (cp(root, elemt) == 1) //root > elemt
                root = root->left;
            else //root < elemt
                root = root->right;

            if (!root)
                return NULL;
        }
    }
}
static avlNode_t *findMax(avlNode_t *root)
{
    while (root->right)
        root = root->right;
    return root;
}
static avlNode_t *findMin(avlNode_t *root)
{
    while (root->left)
        root = root->left;
    return root;
}

void Delete(void *elemt, avlNode_t **tree, int (*cp)(void *eleA, void *eleB))
{
    avlNode_t *head = (*tree);
    avlNode_t *root = (*tree);

    avlNode_t *targ = Find(root, elemt, cp);

    if (targ == (*tree))
    {
        if ((!((*tree)->left)) && (!((*tree)->right)))
        {
            free(*tree);
            return;
        }
        else if ((!((*tree)->left)) && ((*tree)->right))
        {
            avlNode_t *treeR = (*tree)->right;

            (*tree)->right = NULL;
            treeR->parent = NULL;
            free(*tree);
            (*tree) = treeR;
        }
        else if (((*tree)->left) && (!((*tree)->right)))
        {
            avlNode_t *treeL = (*tree)->left;

            (*tree)->left = NULL;
            treeL->parent = NULL;
            free(*tree);
            (*tree) = treeL;
        }
        else // ((*tree)->left)  && ((*tree)->right)
        {
            int L = targ->left->height;
            int R = targ->right->height;
            if (R >= L)
            {
                avlNode_t *minNode = findMin((*tree)->right);
                avlNode_t *targLeft = (*tree)->left;
                (*tree)->left = NULL;
                targLeft->parent = NULL;

                if (minNode->parent == (*tree))
                {
                    (*tree)->right = NULL;
                    minNode->parent = NULL;
                }
                else //minNode->parnt != (*tree)
                {
                    avlNode_t *targRight = (*tree)->right;
                    (*tree)->right = NULL;
                    targRight->parent = NULL;

                    avlNode_t *minNodeParnt = minNode->parent;
                    minNode->parent = NULL;
                    minNodeParnt->left = NULL;

                    avlNode_t *minNodeRight = minNode->right;
                    minNode->right = NULL;
                    if (minNodeRight)
                    {
                        minNodeRight->parent = NULL;
                        minNodeRight->parent = minNodeParnt;
                    }
                    minNodeParnt->left = minNodeRight;

                    targRight->parent = minNode;
                    minNode->right = targRight;
                }
                targLeft->parent = minNode;
                minNode->left = targLeft;
                free(*tree);
                (*tree) = minNode;
            }
            else
            {
                avlNode_t *maxNode = findMax((*tree)->left);
                avlNode_t *targRight = (*tree)->right;
                (*tree)->right = NULL;
                targRight->parent = NULL;

                if (maxNode->parent == (*tree))
                {
                    (*tree)->left = NULL;
                    maxNode->parent = NULL;
                }
                else //max->parnt != (*tree)
                {
                    avlNode_t *targLeft = (*tree)->left;
                    (*tree)->left = NULL;
                    targLeft->parent = NULL;

                    avlNode_t *maxNodeParnt = maxNode->parent;
                    maxNode->parent = NULL;
                    maxNodeParnt->right = NULL;

                    avlNode_t *maxNodeLeft = maxNode->left;
                    maxNode->left = NULL;
                    if (maxNodeLeft)
                    {
                        maxNodeLeft->parent = NULL;
                        maxNodeLeft->parent = maxNodeParnt;
                    }
                    maxNodeParnt->right = maxNodeLeft;

                    targLeft->parent = maxNode;
                    maxNode->left = targLeft;
                }

                maxNode->right = targRight;
                targRight->parent = maxNode;
                free(*tree);
                (*tree) = maxNode;
            }
        }

        getHigh(*tree);
        bF(tree, *tree);
        return;
    }
    else
    {
        if ((!(targ->left)) && (!(targ->right))) //targ has no child
        {
            avlNode_t *targParnt = targ->parent;

            targ->parent = NULL;
            if (targParnt->left == targ)
                targParnt->left = NULL;
            else //(targParnt->right == targ)
                targParnt->right = NULL;

            free(targ);
            targ = targParnt;
        }
        else if ((!(targ->left)) && (targ->right)) //targ has right child
        {
            avlNode_t *minNode = findMin(targ->right);

            avlNode_t *targParnt = targ->parent;
            targ->parent = NULL;

            if (minNode->parent == targ)
            {
                targParnt->right = NULL;
                minNode->parent = NULL;

                minNode->parent = targParnt;
                if (targParnt->right = targ)
                {
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }
            }
            else
            {
                avlNode_t *targRight = targ->right;
                targ->right = NULL;
                targRight->parent = NULL;

                avlNode_t *minNodeParnt = minNode->parent;
                minNode->parent = NULL;
                minNodeParnt->left = NULL;

                avlNode_t *minNodeRight = minNode->right;
                minNodeRight->parent = NULL;
                minNode->right = NULL;

                minNodeRight->parent = minNodeParnt;
                minNodeParnt->left = minNodeRight;

                minNode->parent = targParnt;
                if (targParnt->right == targ)
                {
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }

                targRight->parent = minNode;
                minNode->right = targRight;
            }
            free(targ);
            targ = minNode;
        }
        else if ((targ->left) && (!(targ->right))) //targ has left child
        {
            avlNode_t *maxNode = findMax(targ->left);

            avlNode_t *targParnt = targ->parent;
            targ->parent = NULL;

            if (maxNode->parent == targ)
            {
                targ->left = NULL;
                maxNode->parent = NULL;
            }
            else
            {
                avlNode_t *targLeft = targ->left;
                targ->left = NULL;
                targLeft->parent = NULL;

                avlNode_t *maxNodeParnt = maxNode->parent;
                maxNode->parent = NULL;
                maxNodeParnt->right = NULL;

                avlNode_t *maxNodeLeft = maxNode->left;
                maxNodeLeft->parent = NULL;
                maxNode->left = NULL;

                maxNodeLeft->parent = maxNodeParnt;
                maxNodeParnt->right = maxNodeLeft;

                targLeft->parent = maxNode;
                maxNode->left = targLeft;
            }

            maxNode->parent = targParnt;
            if (targParnt->right == targ)
            {
                targParnt->right = NULL;
                targParnt->right = maxNode;
            }
            else
            {
                targParnt->left = NULL;
                targParnt->left = maxNode;
            }
            free(targ);
            targ = maxNode;
        }
        else if ((targ->left) && (targ->right)) //targ has both child
        {
            //printf("else if ((targ->left) && (targ->right))\n");
            int L = targ->left->height;
            int R = targ->right->height;
            if (R >= L) //in right find minNode
            {
                avlNode_t *minNode = findMin(targ->right);
                avlNode_t *targL = targ->left;
                targ->left = NULL;
                targL->parent = NULL;

                avlNode_t *targParnt = targ->parent;
                targ->parent = NULL;

                if (minNode->parent == targ)
                {
                    targ->right = NULL;
                    minNode->parent = NULL;
                }
                else //minNode->parnt != targ
                {

                    avlNode_t *minParnt = minNode->parent;
                    minNode->parent = NULL;
                    minParnt->left = NULL;

                    avlNode_t *minRight = minNode->right;
                    minNode->right = NULL;
                    if (minRight)
                    {
                        minRight->parent = NULL;
                        minRight->parent = minParnt;
                    }
                    minParnt->left = minRight;

                    minNode->right = minParnt;
                    minParnt->parent = minNode;
                }
                ///minNode connect to targ
                minNode->parent = targParnt;
                if (targParnt->right == targ)
                {
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }

                minNode->left = targL;
                targL->parent = minNode;

                free(targ);
                targ = minNode;
                }
            else //in left child find maximum node
            {
                avlNode_t *maxNode = findMax(targ->left);
                avlNode_t *targR = targ->right;
                targ->right = NULL;
                targR->parent = NULL;

                avlNode_t *targParnt = targ->parent;
                targ->parent = NULL;

                if (maxNode->parent == targ)
                {
                    targ->left = NULL;
                    maxNode->parent = NULL;
                }
                else //maxNode->parnt != targ
                {
                    avlNode_t *maxParnt = maxNode->parent;
                    maxNode->parent = NULL;
                    maxParnt->right = NULL;

                    avlNode_t *maxLeft = maxNode->left;
                    maxNode->left = NULL;
                    if (maxLeft)
                    {
                        maxLeft->parent = NULL;
                        maxLeft->parent = maxParnt;
                    }
                    maxParnt->right = maxLeft;

                    maxNode->left = maxParnt;
                    maxParnt->parent = maxNode;
                }
                ///maxNode connect to targ
                maxNode->parent = targParnt;
                if (targParnt->right == targ)
                {
                    targParnt->right = NULL;
                    targParnt->right = maxNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = maxNode;
                }

                maxNode->right = targR;
                targR->parent = maxNode;
                free(targ);
                targ = maxNode;
            }
        }
        getHigh(targ);
        bF(tree, targ);
        return;
    }
}