#include <stdio.h>
#include <stdlib.h>



typedef struct LNode
{
    int data;
    int freq;
    struct LNode *prior;
    struct LNode *next;
}LNode;

typedef struct LinkList
{
    LNode *head;
    int length;
}LinkList;

void InitList(LinkList *L,int n)
{
    L->length = n;
    int i;
    LNode *p, *q;
    for(i = 0 ; i < n ; i++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p -> data = i;
        p -> freq = 0;                       //假定每个结点的编号就是它的数据
        if(i == 0)
        {
            L->head = p;
            q = L->head;

        }
        else if(i == n- 1)
        {
            q->next = p;
            p->prior = q;
            p->next = L->head;
            L->head->prior = p;
            q = p;
            return;
        }
        else
        {
            q->next = p;
        }
        p->prior = q;
        p->next = NULL;
        q = p;
    }


}
void printList(LinkList *L)
{
    LNode *p;
    p = L->head;
    printf("当前编号:%d  它的前驱编号是:%d 它的后继编号是:%d 其频度为:%d",p->data,p->next->data,p->prior->data,p->freq);
    printf("\n\n");
    p = p->next;
    while(p != L->head)
    {
        printf("当前编号:%d  它的前驱编号是:%d 它的后继编号是:%d 其频度为:%d",p->data,p->next->data,p->prior->data,p->freq);
        printf("\n\n");
        p = p->next;
    }
    return;
}

void locate(LinkList *L, int x)
{
    LNode *p, *q, *temp;
    p = L->head;
    if(x >L->length)
    {
        printf("error!\n");
        return;
    }
    while(p->data != x)
    {
        p = p->next;
    }
    p->freq++;
    /*q = p->prior;
    q->next = p->next;
    p->next->prior = q;   //将p结点从链表中断开；
    q = L->head;
    while(q->next != L->head && (p->freq >= q->freq))
    {
        q = q->prior;

    }*/
    q = p->prior;
    q->next = p->next;
    p->next->prior = q;
    temp = L->head;
    while(temp->next != L->head && p->freq >= temp->freq)
    {
        temp->prior->next = p;
        p->prior = temp->prior;
        p->next = temp;
        temp->prior = p;
        return;
    }




}



int main()
{
    LinkList L;
    InitList(&L,8);
    printList(&L);
    printf("改变后\n");
    locate(&L,2);
    locate(&L,3);
    locate(&L,3);
    locate(&L,4);
    locate(&L,4);
    locate(&L,4);
    locate(&L,4);
    printList(&L);
}
