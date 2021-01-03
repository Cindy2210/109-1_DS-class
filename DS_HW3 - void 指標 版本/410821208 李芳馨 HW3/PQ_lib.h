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
/* �إߤ@�� pq, �䤤 pqClass����PQ������(MINHEAP or MAXHEAP)�A�����j�p�� elementSize, �̦h���ƭӼƬ� maxSize */
int IsEmpty(PQ_t *pq); /* return 0: not empty, 1: empty*/
int IsFull(PQ_t *pq); /* return 0: not full, 1:full */
int Enqueue(PQ_t *pq, void* eleA); /* add an element into PQ */
void *Dequeue(PQ_t *pq); /*delete an element from PQ */


#endif
