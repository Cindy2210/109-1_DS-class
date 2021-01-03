#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AVLtreeLib.h"
#include "AVLtreeLib.c"

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

}