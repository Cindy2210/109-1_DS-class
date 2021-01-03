#include "Lib.h"
#include<stdlib.h>
#include<stdio.h>

void DLL_init(dllNode_t * head)
{
    head->next = NULL;
    head->prev = NULL;
}//�غc�@�ӪŪ� list


int DLL_isEmpty(dllNode_t *head) // head �O�_���Ū�list
{
    //head ���@�Ӥ���NULL���O���� ��Next&prev���VNULL�Ӥw
    if(head->next == NULL && head->prev == NULL)
        return true;
    else
        return false;
}


dllNode_t * DLL_next_node(dllNode_t * node) //(�U�@�Ӹ`�I)
{
    return node->next;
}

dllNode_t * DLL_prev_node(dllNode_t * node) //(�W�@�Ӹ`�I)
{
  return node->prev;
}

unsigned int DLL_num_nodes(dllNode_t *head)
{
    unsigned int num=0;
    while(head->next != NULL){
        num++;
        head = head->next;
    }

    return num;
} //�p��List�����X��node

void DLL_add_before(dllNode_t * new_node, dllNode_t * head)
{
    while(head->prev != NULL)
    {
        head = head->prev;
    }
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
} //(�N�snode�[�J��head node���e�@��)

void DLL_add_tail(dllNode_t * new_node, dllNode_t *head)
{
    while(head->next != NULL)
    {
        head = head->next;
    }
    head->next = new_node;
    new_node->prev = head;
    head = new_node;
} //(�N�snode�[�J��head node����@��)

void DLL_delete(dllNode_t * node)
{
    dllNode_t * next = node->next;
    dllNode_t * prev = node->prev;
    if(prev == NULL && next == NULL)
        free(node);
    else if(prev == NULL && next != NULL)
    {
        next->prev = NULL;
        free(node);
    }
    else if(prev != NULL && next != NULL)
    {
        next->prev = prev;
        prev->next = next;
        free(node);
    }
    else if(prev != NULL && next == NULL)
    {
        prev->next = NULL;
        free(node);
    }
} //(�qnode�Ҧb�� Linked List ���R�����I)

void DLL_concate(dllNode_t *firstList, dllNode_t * secondList)
{
    while(firstList->next != NULL)
        firstList = firstList->next;
    while(secondList->prev != NULL)
        secondList = secondList->prev;
    firstList->next = secondList;
    secondList->prev = firstList;
} //(�NsecondList ��bfirstList����)

