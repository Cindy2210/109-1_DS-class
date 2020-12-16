#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PQ_lib.h"
struct HeapType ///Heap_t
{
    void *elemts; // element array
    int numElemts; // number of elements
};
typedef enum H ///H_class
{
    MINHEAP = 0,///0
    MAXHEAP   ///1
};

struct PQ  ///PQ_t
{
    H_class pqClass;
    Heap_t  heap;
    int maxSize, eleSize;
    int (*cp)(void *eleA, void *eleB);//結構裡面可以有函式指標
};

/*
typedef struct HeapType Heap_t;
typedef enum H H_class;
typedef struct PQ PQ_t;
*/


//利用 memcpy 實作 swap
static void swap_fn(void *eleA, void *eleB, int eleSize)
{
    void *tmp = (char*)malloc(sizeof(char)*eleSize);
    memcpy(tmp, eleA, eleSize);
    memcpy(eleA, eleB, eleSize);
    memcpy(eleB, tmp, eleSize);
    free(tmp);
    return;
}


void createPQ(PQ_t *pq, H_class pqClass, int eleSize, int maxSize, int (*cp)(void *eleA, void *eleB))
/* 建立一個 pq, 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)，元素大小為 elementSize, 最多元數個數為 maxSize */
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
    if(pq->heap.numElemts == pq->maxSize+1)
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

            if( pq->cp( (char*)pq->heap.elemts + (pq->eleSize * parent_i),  (char*)pq->heap.elemts + (pq->eleSize * bottom)) == 0 )
                //cp == 0 means first <= second, which means parent <= left_child
            {
                swap_fn( (char*)pq->heap.elemts + (pq->eleSize * parent_i),  (char*)pq->heap.elemts + (pq->eleSize * bottom), pq->eleSize);
            }
            bottom = parent_i;
        }
        else if(pq->pqClass == 0)//MINheap
        {
            if(bottom%2 == 1)//bottom is odd, means left_child
                parent_i = (bottom-1)/2;
            else//bottom is even, means right_child
                parent_i = (bottom-2)/2;

            if( pq->cp((char*)pq->heap.elemts + (pq->eleSize * parent_i),  (char*)pq->heap.elemts + (pq->eleSize * bottom)) == 1 )
                //cp == 1 means first > second, which means parent > left_child
            {
                swap_fn( (char*)pq->heap.elemts + (pq->eleSize * parent_i),  (char*)pq->heap.elemts + (pq->eleSize * bottom), pq->eleSize);
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
    Heap_t cur = pq->heap;
    memcpy( ((char*)pq->heap.elemts) + (pq->eleSize) * (pq->heap.numElemts), eleA, pq->eleSize);
    ReheapUp( pq, 1, pq->heap.numElemts);
    pq->heap.numElemts++;
}

static void ReheapDown(PQ_t *pq, int root, int bottom)
//static 在使用者的main中沒辦法看到//private在C裡面語法用static
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
            if( pq->cp( ((char*)pq->heap.elemts) + pq->eleSize*L, ((char*)pq->heap.elemts) + pq->eleSize*R ) == 1 )
                max_i = L;
            else
                max_i = R;
            //root <= max_child
            if( pq->cp( ((char*)pq->heap.elemts) + pq->eleSize*root, ((char*)pq->heap.elemts) + pq->eleSize*max_i ) == 0 )
            {
                swap_fn(((char*)pq->heap.elemts) + pq->eleSize*root, ((char*)pq->heap.elemts) + pq->eleSize*max_i, pq->eleSize);
                root = max_i;
                flag = 1;
            }
        }
        else//MINHeap
        {
            //decide min_child
            // left_child > right_child
            if( pq->cp( ((char*)pq->heap.elemts) + pq->eleSize*L, ((char*)pq->heap.elemts) + pq->eleSize*R ) == 1 )
                min_i = R;
            else
                min_i = L;
            //root > min_child
            if( pq->cp( ((char*)pq->heap.elemts) + pq->eleSize*root, ((char*)pq->heap.elemts) + pq->eleSize*min_i ) == 1 )
            {
                swap_fn(((char*)pq->heap.elemts) + pq->eleSize*root, ((char*)pq->heap.elemts) + pq->eleSize*min_i, pq->eleSize);
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
    void *print = (void*)malloc(sizeof(char) * pq->eleSize);
    memcpy(print, ((char*)pq->heap.elemts), pq->eleSize);
    pq->heap.numElemts--;
    memcpy( ( ( char*)pq->heap.elemts), ( ((char*)pq->heap.elemts)+ pq->eleSize * pq->heap.numElemts), pq->eleSize);
    ReheapDown(pq, 1, pq->heap.numElemts-1);
    return print;

}

