#include "stdio.h"
#include  "malloc.h"
typedef struct Lnode
{
    int data;
    struct Lnode *next;
} Lnode;
Lnode* create(int n)  //��������n�����ĵ�ѭ������h
{
    int i;
    Lnode *h,*p;//pΪ��ǰ�����ɽ���ָ��
    Lnode *r = (Lnode *)malloc(sizeof(Lnode));//rΪβָ��
    r->data = n;
    h = r;//hΪͷָ��
    for(i = n - 1 ; i > 0; i--)//ͷ�巨��������
    {   p = (Lnode *)malloc(sizeof(Lnode));
        p->data = i;
        p->next = h;
        h = p;
    }
    r->next = h ; //�γɻ�
    return h;
}
void jeseph(Lnode *p,int m)
{
    //��Լɪ������������˵ı��
    Lnode *q;
    int j = 0;
    printf("��������Ϊ:\n");
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
    printf("\n������n��m��ֵ��\n\n");
    scanf("%d,%d",&n,&m);
    h = create(n) ;
    jeseph(h,m);
}
