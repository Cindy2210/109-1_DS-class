#include <stdio.h>
#include <stdlib.h>
#include "BSTlib.c"
#include "BSTlib.h"

typedef struct student student;

struct student
{
    node_t link;
    int grade;
    char name;
};

void print_node(void *node)
{
    printf("%d ", ((student*)node)->grade);
}

int comp(void *node1, void *node2)
{
    if( ((student*)node1)->grade > ((student*)node2)->grade )
        return 1;
    else if( ((student*)node1)->grade < ((student*)node2)->grade )
        return -1;
    else
        return 0;
}
/*
int find(void *node1, void *node2)
{
    if( ((student*)node1)->name == ((student*)node2)->name )
        return 1;
    return 0;
}

int equ(void *node1, void *node2)
{
    if( ((student*)node1)->grade == ((student*)node2)->grade )
        return 1;
    return 0;
}*/

int main()
{
    student num[9];
    student num2[9];
    int (*alpha)(void*, void*) = &comp;
    void (*out)(void*) = &print_node;/*
    int (*search)(void*, void*) = &find;
    int (*e)(void*, void*) = &equ;*/

    num[0].grade = 2;
    num[1].grade = 25;
    num[2].grade = 25;
    num[3].grade = 6;
    num[4].grade = 3;
    num[5].grade = 45;
    num[6].grade = 95;
    num[7].grade = 25;
    num[8].grade = 89;

    num[0].name = 'A';
    num[1].name = 'B';
    num[2].name = 'C';
    num[3].name = 'D';
    num[4].name = 'E';
    num[5].name = 'F';
    num[6].name = 'G';
    num[7].name = 'H';
    num[8].name = 'I';

    num2[0].grade = 2;
    num2[1].grade = 1;
    num2[2].grade = 5;
    num2[3].grade = 6;
    num2[4].grade = 3;
    num2[5].grade = 4;
    num2[6].grade = 10;
    num2[7].grade = 7;
    num2[8].grade = 8;

    num2[0].name = 'A';
    num2[1].name = 'B';
    num2[2].name = 'C';
    num2[3].name = 'D';
    num2[4].name = 'E';
    num2[5].name = 'F';
    num2[6].name = 'G';
    num2[7].name = 'H';
    num2[8].name = 'I';

    for(int i=0; i<9; i++)
    {
        (num[i].link).left = NULL;
        (num[i].link).right = NULL;
        (num2[i].link).left = NULL;
        (num2[i].link).right = NULL;
    }

    node_t *root = NULL, *root2 = NULL;
    for(int i=0; i<9; i++)
    {
        insertNode((void*)(&num[i]), &root, alpha);
        insertNode((void*)(&num2[i]), &root2, alpha);
    }

    inOrder(root, out);
    printf("\n");

    node_t *temp = findMaxNode(root);
    print_node(temp);
    printf("\n");

    temp = findNode((void*)(&num[1]), root, alpha);

    print_node(temp);
    printf("\n");

    node_t *nr = NULL;
    treeCopy(&nr, root, sizeof(student));
    inOrder(nr, out);
    printf("\n");
    inOrder(root, out);
    printf("\n");

    int flag = 1;

    treeEqual(root, root2, alpha, &flag);
    if( flag == 1 )
    {
        printf("Tree is equal!\n");
    }
    else
    {
        printf("Not equal!\n");
    }


        deleteNode((void*)(&num[2]), &root, alpha);
        inOrder(root, out);
        printf("\n#1--%d \n\n", num[2].grade);

        deleteNode((void*)(&num[6]), &root, alpha);
        inOrder(root, out);
        printf("\n#2--%d \n\n", num[6].grade);

        deleteNode((void*)(&num[3]), &root, alpha);
        inOrder(root, out);
        printf("\n#3--%d \n\n", num[3].grade);

        deleteNode((void*)(&num[4]), &root, alpha);
        inOrder(root, out);
        printf("\n#4--%d \n\n", num[4].grade);

        deleteNode((void*)(&num[1]), &root, alpha);
        inOrder(root, out);
        printf("\n#5--%d \n\n", num[1].grade);

        deleteNode((void*)(&num[8]), &root, alpha);
        inOrder(root, out);
        printf("\n#6--%d \n\n", num[8].grade);

        deleteNode((void*)(&num[7]), &root, alpha);
        inOrder(root, out);
        printf("\n#7--%d \n\n", num[7].grade);

        deleteNode((void*)(&num[5]), &root, alpha);
        inOrder(root, out);
        printf("\n#8--%d \n\n", num[5].grade);

    /*
    void *kk = delete_root(to_void(root));
    free(root);
    root = (node*)kk;
    inorder(root, out);
    printf("\n");

    void *pp = delete_root(to_void(root));
    free(root);
    root = (node*)pp;
    inorder(root, out);
    printf("\n");

    void *ppg = delete_root(to_void(root));
    free(root);
    root = (node*)ppg;
    inorder(root, out);
    printf("\n");

    void *ppgg = delete_root(to_void(root));
    free(root);
    root = (node*)ppgg;
    inorder(root, out);
    printf("\n");
    */
    return 0;
}
