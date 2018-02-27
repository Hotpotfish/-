#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAXLEN 100

/*以下问题要求统一在一个大程序里解决。
14、按先序遍历的扩展序列建立二叉树的存储结构
15、二叉树先序、中序、后序遍历的递归算法
16、二叉树中序遍历的非递归算法
17、二叉树层次遍历的非递归算法
18、求二叉树的深度(后序遍历)

20、求树的深度*/



typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct  snode
{
    BiTNode  B;   // Data域
    struct  snode  *next;
}snode;

typedef struct linkstack
{
    snode *top;
  //  snode *tail;
    int number;
}linkstack;



void createBiTree(BiTree *T)    //4_14按先序遍历的扩展序列建立二叉树的存储结构
{
    char ch;
   // BiTNode *P;
   // printf("输入根节点字符\n");
    scanf("%c",&ch);
    fflush(stdin);
    if(ch == '.')
    {
        *T = NULL;
        return;
    }

    else{
            *T = (BiTNode *)malloc(sizeof(BiTNode));//向内存申请节点空间
            (*T)->data= ch;
            printf("输入%c的左孩子\n",(*T)->data);
            createBiTree(&(*T)->lchild);//生成左子树
            printf("输入%c的右孩子\n",(*T)->data);
            createBiTree(&(*T)->rchild);//生成右子树
        }
}/*createBiTree*/


void printTree(BiTree bt,int nLayer)    //输出二叉树
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



void Preorder(BiTree T)    // 4_15先序遍历二叉树
{

    if(T != NULL)
    {
        printf("%c",T->data);                  // 访问根结点
        Preorder(T->lchild);// 遍历左子树
        Preorder(T->rchild);// 遍历右子树
    }
    else
    return;
}

void Inorder (BiTree T)
{                    // 4_15中序遍历二叉树
   if(T != NULL)
    {
        Inorder(T->lchild); // 遍历左子树
        printf("%c",T->data);              // 访问根结点
        Inorder(T->rchild);// 遍历右子树
    }
}

void Postorder (BiTree T)
{                    //4_15 后序遍历二叉树
   if(T != NULL)
    {
        Postorder(T->lchild); // 遍历左子树
        Postorder(T->rchild);// 遍历右子树
        printf("%c",T->data);                  // 访问根结点
    }
}

void InitStack(linkstack *S)   //初始化链式栈
{
    snode *p;
    p = (snode *)malloc(sizeof(snode));
    if(p == NULL)
    {
        printf("内存分配错误，初始化失败！\n");
        return;
    }
    S->top = p;
    S->number = 0;
  //  S->tail = S->head;
}

void push(linkstack *S,  BiTNode B)   //链式栈进栈算法
{
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    if(t == NULL)
    {
        printf("错误：内存分配不成功，进栈失败!\n");
        return;
    }
    t->B = B;
    t->next = S->top;
    S->top = t;
    printf("%c进栈\n",B.data);
    S->number ++;
    return;
}

 BiTNode *pop(linkstack *S)   //链式栈出栈算法
{
    snode *p;
    if(S->top == NULL)
    {
        printf("栈空!\n");
        return NULL;
    }
    else
    {
        p = S->top;
        S->top = S->top->next;
        return(&(p->B));
        free(p);
        printf("%c成功出栈!\n",S->top);
        return;
    }

}



BiTNode *GoFarLeft(BiTree T, linkstack *S)//找到最左下的结点
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

void Inorder_I(BiTree T)//4_16 中序遍历二叉树的非递归算法一
{
    BiTNode *t;
    linkstack *S;
    t = GoFarLeft(T, S);            // 找到最左下的结点
    while(t != NULL)
    {
        printf("%c",t->data);
        if (t->rchild)
        {
             t = GoFarLeft(t->rchild, S);
        }
        else if (S->top != NULL)    // 栈不空时退栈
        t = pop(S);
        else
        {
          t = NULL;  // 栈空表明遍历结束
        }
    } // while
}// Inorder_I


void translevel(BiTree b)           //4_17按层次遍历
{
    struct node
    {
        BiTree *vec[MAXLEN];
        int f,r;
    }q;
    q.f=0;
    q.r=0;
    if (b != NULL) printf("%c",b->data);
    q.vec[q.r]=b;                        //结点指针进入队列
    q.r=q.r+1;
    while (q.f<q.r)               //队列不为空
    {
        b=q.vec[q.f];   q.f=q.f+1;   //队头出队列
        if (b->lchild!=NULL)       //输出左孩子，并入队列
        {
            printf("%c",b->lchild->data);
            q.vec[q.r]=b->lchild;
            q.r=q.r+1;
       }
       if(b->rchild!=NULL)      //输出右孩子，并入队列
       {
          printf("%c",b->rchild->data);
          q.vec[q.r]=b->rchild;
          q.r=q.r+1;
       }//if
   }//while
}//置队列为空队列



int Depth (BiTree T )  //后序遍历求出深度
{
    int depthval, depthLeft,  depthRight;

          //4_18 返回二叉树的深度
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
    printf("树的层次为%d\n",Depth(T));

}
