#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAXLEN 100

/*��������Ҫ��ͳһ��һ�������������
14���������������չ���н����������Ĵ洢�ṹ
15���������������򡢺�������ĵݹ��㷨
16����������������ķǵݹ��㷨
17����������α����ķǵݹ��㷨
18��������������(�������)

20�����������*/



typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct  snode
{
    BiTNode  B;   // Data��
    struct  snode  *next;
}snode;

typedef struct linkstack
{
    snode *top;
  //  snode *tail;
    int number;
}linkstack;



void createBiTree(BiTree *T)    //4_14�������������չ���н����������Ĵ洢�ṹ
{
    char ch;
   // BiTNode *P;
   // printf("������ڵ��ַ�\n");
    scanf("%c",&ch);
    fflush(stdin);
    if(ch == '.')
    {
        *T = NULL;
        return;
    }

    else{
            *T = (BiTNode *)malloc(sizeof(BiTNode));//���ڴ�����ڵ�ռ�
            (*T)->data= ch;
            printf("����%c������\n",(*T)->data);
            createBiTree(&(*T)->lchild);//����������
            printf("����%c���Һ���\n",(*T)->data);
            createBiTree(&(*T)->rchild);//����������
        }
}/*createBiTree*/


void printTree(BiTree bt,int nLayer)    //���������
{
    int i;
    if(bt == NULL)
    return ;
    printTree(bt ->rchild,nLayer+1);
    for(i=0;i<nLayer;i++)
    printf(" ");
    printf("%c\n",bt->data);
    printTree(bt->lchild,nLayer+1);
}



void Preorder(BiTree T)    // 4_15�������������
{

    if(T != NULL)
    {
        printf("%c",T->data);                  // ���ʸ����
        Preorder(T->lchild);// ����������
        Preorder(T->rchild);// ����������
    }
    else
    return;
}

void Inorder (BiTree T)
{                    // 4_15�������������
   if(T != NULL)
    {
        Inorder(T->lchild); // ����������
        printf("%c",T->data);              // ���ʸ����
        Inorder(T->rchild);// ����������
    }
}

void Postorder (BiTree T)
{                    //4_15 �������������
   if(T != NULL)
    {
        Postorder(T->lchild); // ����������
        Postorder(T->rchild);// ����������
        printf("%c",T->data);                  // ���ʸ����
    }
}

void InitStack(linkstack *S)   //��ʼ����ʽջ
{
    snode *p;
    p = (snode *)malloc(sizeof(snode));
    if(p == NULL)
    {
        printf("�ڴ������󣬳�ʼ��ʧ�ܣ�\n");
        return;
    }
    S->top = p;
    S->number = 0;
  //  S->tail = S->head;
}

void push(linkstack *S,  BiTNode B)   //��ʽջ��ջ�㷨
{
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    if(t == NULL)
    {
        printf("�����ڴ���䲻�ɹ�����ջʧ��!\n");
        return;
    }
    t->B = B;
    t->next = S->top;
    S->top = t;
    printf("%c��ջ\n",B.data);
    S->number ++;
    return;
}

 BiTNode *pop(linkstack *S)   //��ʽջ��ջ�㷨
{
    snode *p;
    if(S->top == NULL)
    {
        printf("ջ��!\n");
        return NULL;
    }
    else
    {
        p = S->top;
        S->top = S->top->next;
        return(&(p->B));
        free(p);
        printf("%c�ɹ���ջ!\n",S->top);
        return;
    }

}



BiTNode *GoFarLeft(BiTree T, linkstack *S)//�ҵ������µĽ��
{
    if(T == NULL)
    {
        return NULL;
    }
    while(T->lchild != NULL)
    {
        push(S, *T);
        T = T->lchild;
    }
    return T;

}

void Inorder_I(BiTree T)//4_16 ��������������ķǵݹ��㷨һ
{
    BiTNode *t;
    linkstack *S;
    t = GoFarLeft(T, S);            // �ҵ������µĽ��
    while(t != NULL)
    {
        printf("%c",t->data);
        if (t->rchild)
        {
             t = GoFarLeft(t->rchild, S);
        }
        else if (S->top != NULL)    // ջ����ʱ��ջ
        t = pop(S);
        else
        {
          t = NULL;  // ջ�ձ�����������
        }
    } // while
}// Inorder_I


void translevel(BiTree b)           //4_17����α���
{
    struct node
    {
        BiTree *vec[MAXLEN];
        int f,r;
    }q;
    q.f=0;
    q.r=0;
    if (b != NULL) printf("%c",b->data);
    q.vec[q.r]=b;                        //���ָ��������
    q.r=q.r+1;
    while (q.f<q.r)               //���в�Ϊ��
    {
        b=q.vec[q.f];   q.f=q.f+1;   //��ͷ������
        if (b->lchild!=NULL)       //������ӣ��������
        {
            printf("%c",b->lchild->data);
            q.vec[q.r]=b->lchild;
            q.r=q.r+1;
       }
       if(b->rchild!=NULL)      //����Һ��ӣ��������
       {
          printf("%c",b->rchild->data);
          q.vec[q.r]=b->rchild;
          q.r=q.r+1;
       }//if
   }//while
}//�ö���Ϊ�ն���



int Depth (BiTree T )  //�������������
{
    int depthval, depthLeft,  depthRight;

          //4_18 ���ض����������
    if (T != NULL)
    {
        depthLeft = Depth( T->lchild );
        depthRight= Depth( T->rchild );
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    else
    {
      depthval = 0;
    }
    return depthval;
}










int main()
{
    int n;
    n = 0;
    BiTree T;
    T = (BiTNode *)malloc(sizeof(BiTNode));
    T->data = '0';
    T->lchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->rchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->lchild->data = '1';
    T->lchild->lchild = NULL;
    T->lchild->rchild = NULL;
    T->rchild->data = '2';
    T->rchild->lchild = NULL;
    T->rchild->rchild = NULL;
   // createBiTree(&T);
    Preorder(T);
    printf("\n");
    Inorder(T);
    printf("\n");
    Postorder(T);
    printf("\n");
    Inorder_I(T);
    printf("\n");
    translevel(T);
    printf("\n");
    printf("���Ĳ��Ϊ%d\n",Depth(T));

}
