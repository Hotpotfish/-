#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 5
#define TRUE 1;
#define FALSE 0;
int visited[MAX_VERTEX_NUM];
int level = 1;

typedef struct ArcNode //弧节点
{
    int adjvex;     // 该弧所指向的顶点的位置
    struct ArcNode  *nextarc; // 指向下一条弧的指针
    int value;   //该弧的权值
}ArcNode;

typedef struct VNode   //头结点
{
    int number;   // 顶点信息
    ArcNode *firstarc; // 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VERTEX_NUM];

  typedef struct
{
     AdjList vertices;   // 表头结点向量
     int vexnum, arcnum; // 图的当前顶点数和弧数
}Graph;

typedef struct Qnode{       //链队结点的类型

    int data;

    struct Qnode *next;

}Qnode,*QueuePtr;



typedef struct

{         //链队指针类型
   QueuePtr front;

   QueuePtr rear;

}LinkQueue;



void InitQueue(LinkQueue *Q)

{

  Q->front=Q->rear=(QueuePtr)malloc(sizeof(Qnode));

  if(!Q->front) exit(1); //存储分配失败

  Q->front->next=NULL;

 }



void EnQueue(LinkQueue *Q,int e)

{ QueuePtr p;

  p=(QueuePtr)malloc(sizeof(Qnode));

  p->data=e;

  p->next=NULL;

  Q->rear->next=p;

  Q->rear=p;

}



int QueueEmpty(LinkQueue *Q)

{

       return(Q->front==Q->rear? 1:0);

}



void DeQueue(LinkQueue *Q,int *e)

{ QueuePtr p;

  if(QueueEmpty(Q))

  {

    printf("\n Queue is free!");

    exit(1);

  }//if

  p=Q->front->next;

  e=p->data;

  Q->front->next=p->next;

  if(Q->front->next==NULL) Q->rear=Q->front;

  free(p);

 }
void BFSTraverse(Graph G)

{
    int v;
    LinkQueue *Q;
    for( v=0;v<G.vexnum;++v)
    {
        visited[v]=FALSE;(Q);
    }
    InitQueue(Q);
    ArcNode *w;
    for( v=0;v<G.vexnum;++v)
           if(!visited[v])
           {
               EnQueue(Q,v);
               while(!QueueEmpty(Q))
               {
                    int u;
                    DeQueue(Q,u);
                    visited[u]=TRUE;
                 //   printf("->%c",G.vertices[u].data);//visit一下
                    for(w=G.vertices[u].firstarc;w;w=w->nextarc)
                    if(!visited[w->adjvex]) EnQueue(Q,w->adjvex);
                }
           }//if

}

int main()
{

}
