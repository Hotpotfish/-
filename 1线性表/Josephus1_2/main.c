#include "stdio.h"
#include  "malloc.h"
typedef struct Lnode
{
    int data;
    struct Lnode *next;
} Lnode;
Lnode* create(int n)  //建立共有n个结点的单循环链表h
{
    int i;
    Lnode *h,*p;//p为当前新生成结点的指针
    Lnode *r = (Lnode *)malloc(sizeof(Lnode));//r为尾指针
    r->data = n;
    h = r;//h为头指针
    for(i = n - 1 ; i > 0; i--)//头插法建立链表
    {   p = (Lnode *)malloc(sizeof(Lnode));
        p->data = i;
        p->next = h;
        h = p;
    }
    r->next = h ; //形成环
    return h;
}
void jeseph(Lnode *p,int m)
{
    //从约瑟夫环中输出出列人的编号
    Lnode *q;
    int j = 0;
    printf("出队序列为:\n");
    do{
        j++;
        if (j == m-1)
        {
            q = p->next;
            p->next = q->next;
            printf("%d ",q->data);
            j = 0;
            free(q);
        }
            p = p->next;
        }
    while(p->next!= p);
    printf("%d\n",p->data);
    free(p);
}
void main()
{

    Lnode *h;
    int m,n;
    printf("\n请输入n和m的值：\n\n");
    scanf("%d,%d",&n,&m);
    h = create(n) ;
    jeseph(h,m);
}
