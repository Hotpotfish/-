#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 5
#define TRUE 1;
#define FALSE 0;
int visited[MAX_VERTEX_NUM];
int level = 1;

typedef struct ArcNode //���ڵ�
{
    int adjvex;     // �û���ָ��Ķ����λ��
    struct ArcNode  *nextarc; // ָ����һ������ָ��
    int value;   //�û���Ȩֵ
}ArcNode;

typedef struct VNode   //ͷ���
{
    int number;   // ������Ϣ
    ArcNode *firstarc; // ָ���һ�������ö���Ļ�
} VNode, AdjList[MAX_VERTEX_NUM];

  typedef struct
{
     AdjList vertices;   // ��ͷ�������
     int vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ���
}Graph;

typedef struct Qnode{       //���ӽ�������

    int data;

    struct Qnode *next;

}Qnode,*QueuePtr;



typedef struct

{         //����ָ������
   QueuePtr front;

   QueuePtr rear;

}LinkQueue;



void InitQueue(LinkQueue *Q)

{

  Q->front=Q->rear=(QueuePtr)malloc(sizeof(Qnode));

  if(!Q->front) exit(1); //�洢����ʧ��

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
                 //   printf("->%c",G.vertices[u].data);//visitһ��
                    for(w=G.vertices[u].firstarc;w;w=w->nextarc)
                    if(!visited[w->adjvex]) EnQueue(Q,w->adjvex);
                }
           }//if

}

int main()
{

}
