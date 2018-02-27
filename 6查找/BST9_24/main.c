#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "string.h"
#define   EQ(a,b)    ((a)== (b))
#define   LT(a,b)    ((a)  <   (b))
#define   LQ(a,b)    ((a) <= (b))

#define FALSE 0;
#define TRUE 1;

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

int SearchBST (BiTree T, int key, BiTree f, BiTree *p)   //平衡树查找算法
{
   // f = NULL;
    if(T == NULL) //树为空
    {
        *p = f;
        return FALSE;
    }
    else if(EQ(key, T->data))   //此时已经找到
    {
        *p = T;
        return TRUE;
    }
    else if(LT(key, T->data))
    {
        SearchBST (T->lchild, key, T, p);
    }
    else SearchBST (T->rchild, key, T, p );
}

int InsertBST(BiTree *T, int e)   //二叉平衡树插入算法
{
    BiTree p;
    if(!SearchBST ( *T, e, NULL, &p ))
    {
        BiTree s1;
        s1 = (BiTree)malloc(sizeof(BiTNode));
        s1->data = e;
        s1->lchild = s1->rchild = NULL;
        if(!p)
        {
            *T = s1;

        }
        else if(LT(e,p->data))
        {
            p->lchild = s1;
        }
        else p->rchild = s1;
        return TRUE;
    }
    else return FALSE;
}
void Preorder(BiTree T)    // 先序遍历二叉树
{

    if(T != NULL)
    {
        printf("%d ",T->data);                  // 访问根结点
        Preorder(T->lchild);// 遍历左子树
        Preorder(T->rchild);// 遍历右子树
    }
    else
        return;
}

int DeleteBST(BiTree *T, int key)  //删除结点的算法
{
    if(!T)
    {
        return FALSE;
    }
    else
    {
        if(EQ(key, (*T)->data))
        {
            Delete(T);
            return TRUE;
        }
        else if(LT(key, (*T)->data))
        {
            DeleteBST(&((*T)->lchild),key);
        }
        else
        {
            DeleteBST(&((*T)->rchild),key);
        }
    }

}
void Delete(BiTree *p)
{
    BiTree *q;
    if(!(*p)->lchild)
    {
        q = p;
        *p = (*p)->lchild;
        free(q);
    }
    else if(!(*p)->rchild)
    {
        q = p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        BiTNode *s;
        q = p;
        s = (*p)->lchild;
        while(s->lchild)
        {
            *q = s;
            s = s->lchild;
        }
        (*p)->data = s->data;
        if(q != p)
        {
            (*q)->rchild = s->lchild;

        }
        else
        {
            (*q)->lchild = s->lchild;

        }
        free(s);
    }

}


int main()
{
    int i;
    BiTree T;
    T = NULL;
    int s[10];//测试数据
    s[0] = 50;
    s[1] = 30;
    s[2] = 80;
    s[3] = 20;
    s[4] = 40;
    s[5] = 90;
    s[6] = 35;
    s[7] = 85;
    s[8] = 32;
    s[9] = 88;
    for(i = 0 ; i < 10 ; i++)
    {
        InsertBST(&T, s[i]);   //插入顺序二叉树
    }
    printf("顺序二叉树插入成功!\n");
    Preorder(T);
    DeleteBST(&T,32);
    printf("\n");
    Preorder(T);




}
