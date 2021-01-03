#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PQ_lib.h"
struct HeapType ///Heap_t
{
    void *elemts; // element array
    int numElemts; // number of elements
};

struct PQ  ///PQ_t
{
    H_class pqClass;
    Heap_t  heap;
    int maxSize, eleSize;
    int (*cp)(void *eleA, void *eleB);//���c�̭��i�H���禡����
};

/*
typedef struct HeapType Heap_t;
typedef enum H H_class;
typedef struct PQ PQ_t;
*/


//�Q�� memcpy ��@ swap
static void swap_fn(void *eleA, void *eleB, int eleSize)
{
    void *tmp = (void*)malloc(sizeof(char)*eleSize);
    memcpy(tmp, eleA, eleSize);
    memcpy(eleA, eleB, eleSize);
    memcpy(eleB, tmp, eleSize);
    free(tmp);
    return;
}


void createPQ(PQ_t *pq, H_class pqClass, int eleSize, int maxSize, int (*cp)(void *eleA, void *eleB))
/* �إߤ@�� pq, �䤤 pqClass����PQ������(MINHEAP or MAXHEAP)�A�����j�p�� elementSize, �̦h���ƭӼƬ� maxSize */
{
    pq->pqClass = pqClass;
    pq->maxSize = maxSize;
    pq->cp = cp;
    pq->eleSize = eleSize;
    pq->heap.elemts = (void*)malloc(sizeof(char) *eleSize*maxSize);
    pq->heap.numElemts = 0;///index
}


int IsEmpty(PQ_t *pq) /* return 0: not empty, 1: empty*/
{
    if(pq->heap.numElemts == 0)
        return 1;
    else
        return 0;
}

int IsFull(PQ_t *pq) /* return 0: not full, 1:full */
{
    if(pq->heap.numElemts == pq->maxSize)
        return 1;
    else
        return 0;
}

static void ReheapUp(PQ_t *pq, int root, int bottom)
{
    int parent_i;
    while(root < bottom)//means bottom != 0
    {
        if(pq->pqClass == 1)//MAXheap
        {
            if(bottom%2 == 1)//bottom is odd, means left_child
                parent_i = (bottom-1)/2;
            else//bottom is even, means right_child
                parent_i = (bottom-2)/2;

            if( pq->cp( (void*)pq->heap.elemts + (pq->eleSize * parent_i),  (void*)pq->heap.elemts + (pq->eleSize * bottom)) == 0 )
                //cp == 0 means first <= second, which means parent <= left_child
            {
                swap_fn( (void*)pq->heap.elemts + (pq->eleSize * parent_i),  (void*)pq->heap.elemts + (pq->eleSize * bottom), pq->eleSize);
            }
            bottom = parent_i;
        }
        else if(pq->pqClass == 0)//MINheap
        {
            if(bottom%2 == 1)//bottom is odd, means left_child
                parent_i = (bottom-1)/2;
            else//bottom is even, means right_child
                parent_i = (bottom-2)/2;

            if( pq->cp((void*)pq->heap.elemts + (pq->eleSize * parent_i),  (void*)pq->heap.elemts + (pq->eleSize * bottom)) == 1 )
                //cp == 1 means first > second, which means parent > left_child
            {
                swap_fn( (void*)pq->heap.elemts + (pq->eleSize * parent_i),  (void*)pq->heap.elemts + (pq->eleSize * bottom), pq->eleSize);
            }
            bottom = parent_i;
        }
    }
    return;
}
int Enqueue(PQ_t *pq, void *eleA) /* add an element into PQ */
{
    if( IsFull(pq) )
        return 0;
    memcpy( ((void*)pq->heap.elemts) + (pq->eleSize) * (pq->heap.numElemts), eleA, pq->eleSize);
    ReheapUp( pq, 0, pq->heap.numElemts);
    pq->heap.numElemts++;
    return 1;
}

static void ReheapDown(PQ_t *pq, int root, int bottom)
//static �b�ϥΪ̪�main���S��k�ݨ�//private�bC�̭��y�k��static
{
    int flag = 1, L, R, max_i, min_i;
    while(flag == 1)
    {
        L = root*2+1;
        R = root*2+2;

        if( L > bottom &&  R > bottom)
            break;

        flag = 0;

        if(pq->pqClass == 1)//MAXHeap
        {
            //decide max_child
            // left_child > right_child
            if( pq->cp( ((void*)pq->heap.elemts) + pq->eleSize*L, ((void*)pq->heap.elemts) + pq->eleSize*R ) == 1 )
                max_i = L;
            else
                max_i = R;
            //root <= max_child
            if( pq->cp( ((void*)pq->heap.elemts) + pq->eleSize*root, ((void*)pq->heap.elemts) + pq->eleSize*max_i ) == 0 )
            {
                swap_fn(((void*)pq->heap.elemts) + pq->eleSize*root, ((void*)pq->heap.elemts) + pq->eleSize*max_i, pq->eleSize);
                root = max_i;
                flag = 1;
            }
        }
        else//MINHeap
        {
            //decide min_child
            // left_child > right_child
            if( pq->cp( ((void*)pq->heap.elemts) + pq->eleSize*L, ((void*)pq->heap.elemts) + pq->eleSize*R ) == 1 )
                min_i = R;
            else
                min_i = L;
            //root > min_child
            if( pq->cp( ((void*)pq->heap.elemts) + pq->eleSize*root, ((void*)pq->heap.elemts) + pq->eleSize*min_i ) == 1 )
            {
                swap_fn(((void*)pq->heap.elemts) + pq->eleSize*root, ((void*)pq->heap.elemts) + pq->eleSize*min_i, pq->eleSize);
                root = min_i;
                flag = 1;
            }
        }
    }
}



void *Dequeue(PQ_t *pq) /*delete an element from PQ */
{
    if( IsEmpty(pq) )
        return NULL;
    void *print = (void*)malloc(sizeof(void) * pq->eleSize);
    memcpy(print, ((void*)pq->heap.elemts), pq->eleSize);
    pq->heap.numElemts--;
    memcpy( ( ( void*)pq->heap.elemts), ( ((void*)pq->heap.elemts)+ pq->eleSize * pq->heap.numElemts), pq->eleSize);
    ReheapDown(pq, 0, pq->heap.numElemts-1);
    return print;

}

