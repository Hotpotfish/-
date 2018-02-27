#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode;
typedef struct LinkList
{
    LNode *head;
    int length;
}LinkList;

void InitList(LinkList *L)
{
    int i;
    LNode *p, *q;
    for(i = 0 ; i < 10 ; i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        p->data = i;
        if(i == 0)
        {

            L->head = p;
            q = L->head;
        }
        else
        {
            q ->next = p;
        }
        p -> next = NULL;
        q = p;
        L->length++;
    }
    return;

}

void printfList(LinkList *L)
{
    LNode *p;
    p = L->head;
    printf("%d ",p->data);
    while(p -> next != NULL)
    {
        p = p ->next ;
        printf("%d ",p->data);
    }
    printf("\n");
}

void Reverse(LinkList *L)
{
    int i = 0;
    int Arr[L->length];
    LNode *p, *q;
    p = L -> head;
    Arr[i] = p->data;
    i++;
    while(p->next != NULL)
    {
        p = p -> next;
        Arr[i] = p -> data;
        i++;
    }


    for(i = L->length - 3 ; i >= 0 ; i--)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p ->data = Arr[i];
        if(i == L->length - 3)
        {
            L -> head = p;
            q = L -> head;
        }
        else
        {
             q -> next = p;

        }
        p ->next = NULL;
        q = p;
    }

   /* while(p -> next != NULL)
    {
        p ->data = Arr[i];
        if(i == L->length - 1)
        {
            L -> head = p;
            q = L -> head;
        }
        else
        {
            q -> next = p;
        }
        p ->next = NULL;
        q = p;
        i --;
    }
    */
    return;

}


int main()
{
    LinkList L;
    //L.length = 0;
    InitList(&L);
    printfList(&L);
    Reverse(&L);
    printfList(&L);


}
