#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "string.h"
#define   EQ(a,b)           (!strcmp((a) , (b)))
#define   LT(a,b)           (strcmp((a) , (b)) < 0)
#define   LQ(a,b)           (strcmp((a) , (b)) <= 0)
#define FALSE 0;
#define TRUE 1;

typedef struct BiTNode
{
    char s[10];
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

int SearchBST (BiTree T, char key[10], BiTree f, BiTree *p)
{
    f = NULL;
    if(T == NULL) //树为空
    {
        p = f;
        return FALSE;
    }
    else if(EQ(key, T->s))   //此时已经找到
    {
        p = T;
        return TRUE;
    }
    else if(LT(key, T->s))
    {
      SearchBST (T->lchild, key, T, p);
    }
    else SearchBST (T->rchild, key, T, p );
}

int InsertBST(BiTree *T, char e[10])   //二叉平衡树插入算法
{
   BiTree *p;
   if(!SearchBST ( T, e, NULL, p ))
   {
       BiTree s1;
       s1 = (BiTree)malloc(sizeof(BiTNode));
       strcpy(s1->s, e);
       s1->lchild = s1->rchild = NULL;
       if(p != NULL)
       {
           T = s1;
       }
       else if(LT(e,(*p)->s))
       {
           (*p)->lchild = s1;
       }
       else (*p)->rchild = s1;
       return TRUE;
   }
   else return FALSE;
}

int printfTree(BiTree T)
{
    BiTNode *p;
    p = T;
    prinf("%s",&)

}


int main()
{
    int i;
    BiTree *T;
    T = NULL;
   // T = (BiTree *)malloc(sizeof(BiTNode));
    char s[12][10];
    strcpy(s[0],"Jan");
    strcpy(s[1],"Feb");
    strcpy(s[2],"Mar");
    strcpy(s[3],"Ap");
    strcpy(s[4],"May");
    strcpy(s[5],"June");
    strcpy(s[6],"July");
    strcpy(s[7],"Aug");
    strcpy(s[8],"Sep");
    strcpy(s[9],"Oct");
    strcpy(s[10],"Nov");
    strcpy(s[11],"Dec");
    for(i = 0 ; i < 12 ; i++)
    {
         InsertBST(T, s[i]);   //插入顺序二叉树
    }
    printf("顺序二叉树插入成功!\n");








}
