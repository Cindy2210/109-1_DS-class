#include "Lib.h"
#include<stdlib.h>
#include<stdio.h>

void DLL_init(dllNode_t * head)
{
    head->next = NULL;
    head->prev = NULL;
}//建構一個空的 list


int DLL_isEmpty(dllNode_t *head) // head 是否為空的list
{
    //head 有一個不為NULL的記憶體 但Next&prev指向NULL而已
    if(head->next == NULL && head->prev == NULL)
        return true;
    else
        return false;
}


dllNode_t * DLL_next_node(dllNode_t * node) //(下一個節點)
{
    return node->next;
}

dllNode_t * DLL_prev_node(dllNode_t * node) //(上一個節點)
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
} //計算List中有幾個node

void DLL_add_before(dllNode_t * new_node, dllNode_t * head)
{
    while(head->prev != NULL)
    {
        head = head->prev;
    }
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
} //(將新node加入到head node的前一個)

void DLL_add_tail(dllNode_t * new_node, dllNode_t *head)
{
    while(head->next != NULL)
    {
        head = head->next;
    }
    head->next = new_node;
    new_node->prev = head;
    head = new_node;
} //(將新node加入到head node的後一個)

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
} //(從node所在的 Linked List 中刪除此點)

void DLL_concate(dllNode_t *firstList, dllNode_t * secondList)
{
    while(firstList->next != NULL)
        firstList = firstList->next;
    while(secondList->prev != NULL)
        secondList = secondList->prev;
    firstList->next = secondList;
    secondList->prev = firstList;
} //(將secondList 串在firstList之後)

