#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct avl_node
{
    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
    int height; // tree height
} avlNode_t;

typedef struct student stu;
struct student
{
    avlNode_t links;
    char id;
    int grade;
};

void inorder(avlNode_t *root)
{
    if (root)
    {
        //        printf("L:\t");
        inorder(root->left);
        printf("%d(%p)  high:%d(id:%c)\t", ((stu *)root)->grade, &((stu *)root)->grade, ((stu *)root)->links.height, ((stu *)root)->id);
        printf("root:(%p)\n", root);
        //printf("Bf:%d\n", root->balFact);
        //        printf("R:\t");
        inorder(root->right);
    }
    //    printf("return;\n");
}

void inorderdebug(avlNode_t *root)
{
    if (root)
    {
        printf("L:\t");
        inorderdebug(root->left);
        printf("%d(%p)  high:%d(id:%c)\n", ((stu *)root)->grade, &((stu *)root)->grade, ((stu *)root)->links.height, ((stu *)root)->id);
        printf("root:(%p)\n", root);
        //printf("Bf:%d\n", root->balFact);
        printf("R:\t");
        inorderdebug(root->right);
    }
    printf("return;\n");
}
void pre(avlNode_t *root)
{
    if (root)
    {
        printf("%d(%p)  high:%d(id:%c)\t", ((stu *)root)->grade, &((stu *)root)->grade, ((stu *)root)->links.height, ((stu *)root)->id);
        printf("root:(%p)\n", root);

        pre(root->left);
        pre(root->right);
    }
}
void preorder(avlNode_t *root)
{
    if (root)
    {
        printf("%d(%p)  high:%d(id:%c)\n", ((stu *)root)->grade, &((stu *)root)->grade, ((stu *)root)->links.height, ((stu *)root)->id);
        printf("root:(%p)\n", root);
        printf("L:\t");
        preorder(root->left);
        printf("R:\t");
        preorder(root->right);
    }
    printf("return;\n");
}

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
/*
static avlNode_t *rotatR(avlNode_t **tree, avlNode_t *root)
{
    avlNode_t *second = root;

    avlNode_t *first = root->left;
    root->left = NULL;
    first->parent = NULL;

    avlNode_t *firstRight = first->right;
    first->right = NULL;
    if(firstRight)
        firstRight->parent = NULL;

    avlNode_t *rootParnt = root->parent;
    if(rootParnt)
        rootParnt->left = NULL;
    root->parent = NULL;
    /*
    if(second)
    printf("second:%p\n", second);
    else
        printf("second is NULL!\n");
    if(first)
    printf("first:%p\n", first);
    else
        printf("first is NULL!\n");
    if(firstRight)
    printf("firstRight:%p\n", firstRight);
    else
        printf("firstRight is NULL!\n");
    if(rootParnt)
    printf("rootParnt:%p\n", rootParnt);
    else
        printf("rootParnt is NULL!\n");


    first->right = second;
    second->parent = first;

    second->left = firstRight;
    if(firstRight)
        firstRight->parent = second;
//    printf("??\n");

    if((*tree) == root)//rootParnt is NULL
    {
        (*tree) = first;        
    }
    else
    {
        rootParnt->left = first;
        first->parent = rootParnt;  
    }
    return second;

}*/

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
            //            printf("if (rootGrand->right == rootParnt)\n");
            //            printf("????????????????????????????????????????????????????????????????????????????????????????????????????????????LR????????????\n");
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
             /*
            printf("rootParnt:%p\n", rootParnt);
            printf("rootGrand:%p\n", rootGrand);
            printf("root:%p\n", root);
            if (rootR)
                printf("rootR:%p\n", rootR);
            else
                printf("rootR is NULL!!!!!!!!!\n");
*/
            //printf("else (rootGrand->right == rootParnt)\n");
            //printf("LL????????????????????????????????????????????????????????????????????\n");
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
            printf("LR---------------------------\n");
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
            printf("RR------------------------\n");
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
    //    avlNode_t *head = (*tree);

    //    printf("\t\trotatL\n");
    root = rotatL(tree, root->left->right);
    getHigh(root);
    /*
    printf("\n");
    printf("===========================in LR=================================\n");
    printf("inorder\n");
    //inorder(root);
    inorderdebug(head);
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("preorder\n");
    preorder(head);

    printf("\t\trotatR\n");
    */
    root = rotatR(tree, root->parent);
    getHigh(root);
    /*
    printf("\n");
    printf("inorder\n");
    //inorder(root);
    inorderdebug(head);
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("preorder\n");
    preorder(head);
    printf("\n======================finist in LR=================================\n");
    */
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
/*
static int getHigh(avlNode_t *root)
{
    if(!root)
    {
        if(root->left == NULL && root->right == NULL)
            return 1;//leaf node
        else if( getHigh(root->right) > getHigh(root->left))
        {//right child is higher
            return (root->right)->height +1;
        }
        else
        {//left child is higher
            return (root->left)->height +1;
        }   
    }
    else//empty node
        return 0;
}*/
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
        printf("In bF=============================================================================================\n");
        printf("root:%p\n", root);

        int L, R;
        if (root->left == NULL)
            L = 0;
        else
            L = root->left->height;
        if (root->right == NULL)
            R = 0;
        else
            R = root->right->height;
        printf("L:%d R:%d\n", L, R);
        int balance = L - R;
        printf("balFac:%d\n", balance);

        if (balance == 0 || balance == 1 || balance == -1)
            bF(tree, root->parent);
        else if (balance == 2) //type LL or type LR
        {
            if (findprebF(root->left) == 1) //type LL
            {
                //printf("findprebF(root->left) == 1)\n");
                printf("LL\n");
                LL(tree, root);
            }
            else if (findprebF(root->left) == -1) //type LR
            {
                //printf("findprebF(root->left) == -1)\n");
                printf("LR\n");
                LR(tree, root);
            }
        }
        else if (balance == -2)
        {
            if (findprebF(root->right) == 1) //type
            {
                //printf("if findprebF(root->right) == 1)\n");
                printf("RL\n");
                RL(tree, root);
            }
            else if (findprebF(root->right) == -1) //type RR
            {
                //printf("if findprebF(root->right) == -1)\n");
                printf("RR\n");
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

    //printf("avlNode_t *cur = *root;\n");
    avlNode_t *cur = *tree;
    avlNode_t *head = *tree;
    while (1)
    {
        //printf("%d\n", cp(cur, elemt));
        if (cp((void *)cur, elemt) == 1 || cp((void *)cur, elemt) == 0) //cur >= elemt, go left
        {
            //    printf("if(cp(cur, elemt) == 1 || cp(cur, elemt) == 0)\n");
            if (cur->left == NULL)
            {
                //        printf("if(cur->left == NULL)\n");
                cur->left = ((avlNode_t *)elemt);
                ((avlNode_t *)elemt)->parent = cur;
                break;
            }
            cur = cur->left;
        }
        else if (cp(cur, elemt) == -1) //cur < elemt, go right
        {
            //    printf("else if(cp((void*)cur, elemt) == -1)\n");
            if (cur->right == NULL)
            {
                //        printf("if(cur->right == NULL)\n");
                cur->right = ((avlNode_t *)elemt);
                ((avlNode_t *)elemt)->parent = cur;
                break;
            }
            cur = cur->right;
        }
    }
    /*
    printf("=========================AfterInsert=================================\n");
    printf("inorder\n");
    //inorder(root);
    inorderdebug(head);
    printf("\n-----------+++++++++++++++++++++---------------\n");
    printf("preorder\n");
    preorder(head);
    printf("\n======================finistInsert=================================\n");

    printf("getHigh((avlNode_t *)elemt);\n");
    */
    getHigh((avlNode_t *)elemt);
    //printf("bF(tree, (avlNode_t *)elemt);\n");
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
avlNode_t *findMax(avlNode_t *root)
{
    while (root->right)
        root = root->right;
    return root;
}
avlNode_t *findMin(avlNode_t *root)
{
    while (root->left)
        root = root->left;
    return root;
}

void Delete(void *elemt, avlNode_t **tree, int (*cp)(void *eleA, void *eleB))
{
    printf("============================in Delete================================\n");
    avlNode_t *head = (*tree);
    avlNode_t *root = (*tree);

    avlNode_t *targ = Find(root, elemt, cp);
    printf("find:%p\n", targ);

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
                printf("\t\tif( R >= L)\n");
                avlNode_t *minNode = findMin(targ->right);
                printf("miinNode:%p\n", minNode);
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
                    printf("!!\n");
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
                printf("-----------targ--------------------------------%p----------------------------------------------\n", targ);
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
stu *AvlMalloc(char key, int data)
{
    stu *tmp = (stu *)malloc(sizeof(stu));
    tmp->id = key;
    tmp->grade = data;

    tmp->links.left = NULL;
    tmp->links.right = NULL;
    tmp->links.parent = NULL;
    tmp->links.height = 0;

    return tmp;
}

int compare(void *A, void *B)
{
    if (((stu *)A)->grade > ((stu *)B)->grade)
        return 1;
    else if (((stu *)A)->grade < ((stu *)B)->grade)
        return -1;
    else
        return 0;
}

void main()
{
    stu *math1[20];
    stu *del[20];
    char name[20] = "ABCDEFGHIJKLMNOPQ";
    //int grade[20] = {88, 77, 66, 44, 33, 22, 11, 99};//LL
    //int grade[20] = { 1, 11, 22, 33, 44, 66, 77, 88};//RR
    //int grade[20] = {50, 20, 30, 10, 15, 5, 8, 70, 80};//LL
    //int grade[20] = {50, 60, 30, 20, 35, 33, 31, 32};//LR
    //int grade[20] = {32, 31, 33, 35, 34, 50, 40, 20, 5, 10, 12, 15, 60, 70, 80}; //RL & RR
    int grade[20] = {100, 30, 70, 110, 105, 20, 10, 5, 120, 130}; //
    //
    int (*cmpar)(void *, void *) = compare;

    for (int i = 0; i < 10; i++)
        math1[i] = AvlMalloc(name[i], grade[i]);

    avlNode_t *root = NULL;
    for (int i = 0; i < 10; i++)
    {
        Insert(math1[i], &root, cmpar);
        printf("insert:%d\n", math1[i]->grade);
        /*printf("\n-----------------------inor:------------------------\n");
        inorder(root);*/
        printf("\n-----------------------pre:------------------------\n");
        //pre(root);
        preorder(root);
        printf("\n-----------------------------------------------\n");
    }
    printf("<<<<<<<<<<<<<<<<<<<<<AfterInsert>>>>>>>>>>>>>>>>>>>>>\n");
    //pre(root);
    preorder(root);
    printf("\n-----------------------------------------------\n");
    printf("Delete 105\n");
    Delete(math1[4], &root, cmpar);
    pre(root);
    printf("\n-----------------------------------------------\n");
    printf("Delete 30\n");
    Delete(math1[1], &root, cmpar);
    pre(root);
    printf("\n-----------------------------------------------\n");
    printf("Delete 10\n");
    Delete(math1[6], &root, cmpar);
    pre(root);
    printf("\n-----------------------------------------------\n");
    printf("Delete 20\n");
    Delete(math1[5], &root, cmpar);
    pre(root);
    printf("\n===============================================\n");
    preorder(root);

    /*Delete(math1[], &root, cmpar);
    pre(root);
    printf("\n===============================================\n");
    Delete(math1[5], &root, cmpar);
    pre(root);
    printf("\n===============================================\n");
*/
    /*


    printf("<<<<<<<<<<<<<<<<<<<<<In_Main>>>>>>>>>>>>>>>>>>>>>\n");

    printf("inorder\n");
    //inorder(root);
    inorderdebug(root);
    printf("\n-----------------------------------------------\n");
    preorder(root);
    printf("\n===============================================\n");
    */
    /*
    avlNode_t *prt = Find(root, math1[6], cmpar);
    printf("%p\n", prt);
    avlNode_t *prt = Find(root, math1[5], cmpar);
    printf("%p\n", prt);
    avlNode_t *prt = Find(root, math1[0], cmpar);
    printf("%p\n", prt);
    */
    /*
    Delete(math1[5], &root, cmpar);

    printf("<<<<<<<<<<<<<<<<<<<<<AfterDelele>>>>>>>>>>>>>>>>>>>>>\n");
    printf("Delete 40\n");

    printf("inorder\n");
    //inorder(root);
    inorderdebug(root);
    printf("\n-----------------------------------------------\n");
    preorder(root);
    printf("\n===============================================\n");

    Delete(math1[6], &root, cmpar);

    printf("<<<<<<<<<<<<<<<<<<<<<AfterDelele>>>>>>>>>>>>>>>>>>>>>\n");

    printf("Delete 40\n");
    printf("inorder\n");
    //inorder(root);
    inorderdebug(root);
    printf("\n-----------------------------------------------\n");
    preorder(root);
    printf("\n===============================================\n");*/
}