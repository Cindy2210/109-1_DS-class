#ifndef PQ_lib
#define PQ_lib

typedef struct HeapType Heap_t;
typedef enum H ///H_class
{
    MINHEAP = 0,///0
    MAXHEAP   ///1
}H_class;
typedef struct PQ PQ_t;
void createPQ(PQ_t *pq, H_class pqClass, int eleSize, int maxSize, int (*cp)(void *eleA, void *eleB));
/* 建立一個 pq, 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)，元素大小為 elementSize, 最多元數個數為 maxSize */
int IsEmpty(PQ_t *pq); /* return 0: not empty, 1: empty*/
int IsFull(PQ_t *pq); /* return 0: not full, 1:full */
int Enqueue(PQ_t *pq, void* eleA); /* add an element into PQ */
void *Dequeue(PQ_t *pq); /*delete an element from PQ */


#endif
