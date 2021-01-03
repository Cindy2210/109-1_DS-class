#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Lib.h"

struct Data_node
{
    dllNode_t cursor;
    int data;
};
typedef struct Data_node Node_t;

void print(Node_t *head)
{
    while(head != NULL)
    {
        printf("%d", head->data);
        head = DLL_next_node(head);
    }
    printf("\n");
}
Node_t *carry(Node_t **head, Node_t *tail)
{
    int add;
    while(DLL_prev_node(tail) != NULL)
    {
        if(tail->data >= 10)
        {
            add = tail->data / 10;
            tail->data = tail->data %10;
            tail = DLL_prev_node(tail);
            tail->data += add;
        }
        else
            tail = DLL_prev_node(tail);
    }
    if( tail->data >=10)
    {
        Node_t *new_data = malloc(sizeof(Node_t));
        add = tail->data /10;
        tail->data = tail->data %10;

        new_data->data = add;
        new_data->cursor.next = tail;
        tail->cursor.prev = new_data;
        *head = new_data;
    }
    return *head;
}
int main()//addition
{
    char Num1[50], Num2[50];
    scanf("%s%s", Num1, Num2);

    int i, j;
    Node_t *head = NULL, *tail = NULL;

    int Len1 = strlen(Num1), Len2 = strlen(Num2);
    if(Len1 != Len2)
    {
        if(Len1 > Len2)
        {
            for( i = Len1-1, j = Len2-1 ; j>= 0 ; i--, j--)
            {
                Node_t *new_node = malloc(sizeof(Node_t));
                new_node->data = (Num1[i]-'0')+(Num2[j]-'0');

                if( i == Len1-1 && j == Len2-1 )
                {
                    head = new_node;
                    tail = new_node;
                    DLL_init(head);
                    continue;
                }
                DLL_add_before(new_node, head);
                head = new_node;
                head->cursor.prev = NULL;
            }

            for( ; i >= 0; i--)
            {
                Node_t *new_node = malloc(sizeof(Node_t));
                new_node->data = (Num1[i]-'0');
                DLL_add_before( new_node, head);
                head = new_node;
                head->cursor.prev = NULL;
            }
            head = carry(&head, tail);
            print(head);
        }
        else
        {
            for( i = Len1-1, j = Len2-1 ; i>= 0 ; i--, j--)
            {
                Node_t *new_node = malloc(sizeof(Node_t));
                new_node->data = (Num1[i]-'0')+(Num2[j]-'0');

                if( i == Len1-1 && j == Len2-1 )
                {
                    head = new_node;
                    tail = new_node;
                    DLL_init(head);
                    continue;
                }
                DLL_add_before(new_node, head);
                head = new_node;
                head->cursor.prev = NULL;
            }

            for( ; j >= 0; j--)
            {
                Node_t *new_node = malloc(sizeof(Node_t));
                new_node->data = (Num2[j]-'0');
                DLL_add_before( new_node, head);
                head = new_node;
                head->cursor.prev = NULL;//DLL_next_node(head) = NULL;
                //current = DLL_prev_node(current);
            }
            head = carry(&head, tail);
            print(head);
        }
    }
    else
    {
        for( i = Len1-1 ; i >= 0 ; i--)
        {
            Node_t *new_node = malloc(sizeof(Node_t));
            new_node->data = (Num1[i]-'0')+(Num2[i]-'0');
            if( i == Len1-1 )
            {
                head = new_node;
                tail = new_node;
                DLL_init(new_node);
                continue;
            }
            DLL_add_before( new_node, head);
            head = new_node;
            head->cursor.prev = NULL;//DLL_next_node(head) = NULL;

        }
        head = carry(&head, tail);
        print(head);
    }
}

