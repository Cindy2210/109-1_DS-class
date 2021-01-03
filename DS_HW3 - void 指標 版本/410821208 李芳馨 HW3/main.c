#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PQ_lib.h"
#include "PQ_lib.c"
//#include "PQ_lib_debug-vers.c"

typedef struct stu stu;

struct stu
{
    char ID;
    int grade;
};

int Grade(void *EA, void *EB)
{
    //printf("LG:%d RG:%d\n", ((stu*)EA)->grade, ((stu*)EB)->grade);
    if( ((stu*)EA)->grade > ((stu*)EB)->grade )
    {
        //printf("RETURN 1\n");
        return 1;
    }
    //printf("RETURN 0\n");
    return 0;
}

void print(PQ_t *pq)
{
    stu *temp;
    //printf("???\n");
    for (int i=0; i < pq->heap.numElemts; i++)
    {
        //printf("??????????????/\n");
        temp = (stu *)(pq->heap.elemts + i*sizeof(stu));
        printf("index=%d, ID=%c,grade=%d\n",i,temp->ID, temp->grade);
    }
}
int main()
{
    stu class1[99];
    stu class2[99];
    PQ_t class_heap;
    int (*tt)(void*, void*) = Grade;

    class1[0].ID = 'A', class1[0].grade = 98;
    class1[1].ID = 'B', class1[1].grade = 60;
    class1[2].ID = 'C', class1[2].grade = 77;
    class1[3].ID = 'D', class1[3].grade = 49;
    class1[4].ID = 'E', class1[4].grade = 88;
    class1[5].ID = 'F', class1[5].grade = 19;
    class1[6].ID = 'G', class1[6].grade = 100;
    class1[7].ID = 'H', class1[7].grade = 58;
    class1[8].ID = 'I', class1[8].grade = 67;
    class1[9].ID = 'J', class1[9].grade = 85;
    class1[10].ID = 'K', class1[10].grade = 89;
    class1[11].ID = 'L', class1[11].grade = 46;
    class1[12].ID = 'M', class1[12].grade = 55;
    class1[13].ID = 'N', class1[13].grade = 70;
    class1[14].ID = 'O', class1[14].grade = 23;

    class2[0].ID = 'Z', class2[0].grade = 81;
    class2[1].ID = 'X', class2[1].grade = 69;
    class2[2].ID = 'J', class2[2].grade = 15;
    class2[3].ID = 'L', class2[3].grade = 44;
    class2[4].ID = 'H', class2[4].grade = 99;

    createPQ(&class_heap, MAXHEAP, sizeof(stu), 30, tt);
    //printf("!!\n");


    for(int i=0; i<15; i++)
    {
        Enqueue(&class_heap, &class1[i]);
        //print(&class_heap);
        //printf("\n-------------------------------\n");
    }
    printf("!!\n");
    void *root1;

    for(int i=0; i<8; i++)
    {
        //printf("!!\n");
        root1 = Dequeue(&class_heap);
        //printf("!12345!!!!!!!!!!!!!!!!!!!!!\n");
        if( root1 != NULL )
            printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );
        if( root1 == NULL)
            printf("NULL\n");
        print(&class_heap);
        printf("\n==============================================\n");
    }
    /*
        for(int i=0; i<5; i++)
            EnQueue(&class_heap, &class2[i]);

        for(int i=0; i<11; i++)
        {
            root1 = DeQueue(&class_heap);
            if( root1 != NULL )
                printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );
        }
    */
    return 0;
}

/*#include <stdio.h>
#include <string.h>
#include "pq.h"
typedef struct myElement
{
    char ID[10];
    int math;
    int eng;
} student_t;


int compareMath(void *elementA, void *elementB)
{
    int mathA = ((student_t *)elementA)->math;
    int mathB = ((student_t *)elementB)->math;
    if(mathA>mathB)
    {
        return 1;
    }
    else if(mathA<mathB)
    {
        return -1;
    }
    return 0;
}

void print(PQ_t *pq)
{
    student_t *temp;
    for (int i=0; i<pq->heap.numElements; i++)
    {
        temp = (student_t *)(pq->heap.elements + i*sizeof(student_t));
        printf("index=%d, ID=%s,math=%d, eng=%d\n",i,temp->ID, temp->math, temp->eng);
    }
}

int main()
{
    student_t node[6]=
    {
        {"C120308001", 70, 100},
        {"B220406001", 60, 90},
        {"D120306001", 80, 95},
        {"A220407001", 65, 90},
        {"D220506001", 10, 70},
        {"A120406001", 90, 90}
    };

    PQ_t maxPQ;

    createPQ(&maxPQ, MAXHEAP, sizeof(student_t), 100, compareMath);

    for(int i=0; i<6; i++)
        Enqueue(&maxPQ, &node[i]);
    print(&maxPQ);

}
*/
