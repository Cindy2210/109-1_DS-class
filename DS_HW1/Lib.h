#include<stdio.h>
#include<stdlib.h>
#ifndef Lib.h
#define Lib.h
#define true 1
#define false 0

typedef struct node {
          struct node * prev;
          struct node * next;
       } dllNode_t;



void DLL_init(dllNode_t *head); //�غc�@�ӪŪ� list

int DLL_isEmpty(dllNode_t *head); // head �O�_���Ū�list

dllNode_t *DLL_next_node(dllNode_t *node); //(�U�@�Ӹ`�I)

dllNode_t *DLL_prev_node(dllNode_t *node);//(�W�@�Ӹ`�I)

unsigned int DLL_num_nodes(dllNode_t *head); //�p��List�����X��node

void DLL_add_before(dllNode_t * new_node, dllNode_t * head); //(�N�snode�[�J��head node���e�@��)

void DLL_add_tail(dllNode_t * new_node, dllNode_t *head); //(�N�snode�[�J��head node����@��)

void DLL_delete(dllNode_t * node); //(�qnode�Ҧb�� Linked List ���R�����I)

void DLL_concate(dllNode_t *firstList, dllNode_t * secondList); //(�NsecondList ��bfirstList����)

#endif // DOUBLELINK_H_INCLUDED
