#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

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
    for(i = 0 ; i < 100 ; i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        p ->data = i;
        if(i == 0)
        {
            L->head = p;
            q = L->head;
        }
        else
        {
            q->next = p;
        }
        p->next = NULL;
        q = p;
        L->length++;
    }
    return;
}
void printList(LinkList *L)
{
    LNode *p;
    p = L->head;
    printf("%d ", p->data);
    while(p->next != NULL)
    {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");

}

void DeleteInte(int mink, int maxk, LinkList *L)
{
    if(mink >= maxk)
    {
        printf("输入错误");
        return;
    }
    L ->length = 0;
    LNode *p, *q, *r;
    p = L->head;
    while(p->next != NULL)
    {
        r = (LNode*)malloc(sizeof(LNode));
        r->data = p->data;   //当前值传给r
        if(p->data <= mink)
        {
            p = p->next;

        }
        else if((p->data > mink) && (p ->data < maxk))
        {
            if(L->length == 0)
            {
                L->head = r;
                q = L->head;
            }
            else
            {
                q->next = r;
            }
            r->next = NULL;
            q = r;
            L->length++;
            p = p->next;
        }
        else
        {
            break;
        }

    }
    return;


}


int main()
{
    LinkList L;
    InitList(&L);
    printf("%d\n",(L.length) - 2);
    printList(&L);
    DeleteInte(30,50,&L);
    printList(&L);

    return 0;
}
