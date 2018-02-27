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



void InitQueue(LinkQueue *Q)   //初始化队列

{

  Q->front=Q->rear=(QueuePtr)malloc(sizeof(Qnode));

  if(!Q->front) exit(1); //存储分配失败

  Q->front->next=NULL;

 }



void EnQueue(LinkQueue *Q,int e)    //进队算法

{ QueuePtr p;

  p=(QueuePtr)malloc(sizeof(Qnode));

  p->data=e;

  p->next=NULL;

  Q->rear->next=p;

  Q->rear=p;

}



int QueueEmpty(LinkQueue *Q)   //队列判空的算法

{

       return(Q->front==Q->rear? 1:0);

}



void DeQueue(LinkQueue *Q,int *e)    //出队

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

 void BFS(Graph G, int e)
 {
     LinkQueue *Q;
     ArcNode *w;
     int i;
     for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
     {
         visited[i] = FALSE;   //标志初始化
     }
     InitQueue(Q);
     for(e = 0 ; e < G.vexnum ; e++)
     {
         visited[e] = TRUE;
         printf("%d\n",G.vertices[e].number);
         EnQueue(Q,e);
     }
     if(!visited[e])
     {
         while(!QueueEmpty(Q))
         {
             int u;
             DeQueue(Q, u);
             for(w = G.vertices[u].firstarc ; w != NULL ; w = w->nextarc)
             {
                 if(!visited[u])
                 {
                     visited[u] = TRUE;
                     printf("%d\n",w->value);
                     EnQueue(Q,e);
                 }
             }
         }
     }

 }
int main()
{
    printf("Hello world!\n");
    return 0;
}
