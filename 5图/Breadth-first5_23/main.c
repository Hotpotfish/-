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



void InitQueue(LinkQueue *Q)   //��ʼ������

{

  Q->front=Q->rear=(QueuePtr)malloc(sizeof(Qnode));

  if(!Q->front) exit(1); //�洢����ʧ��

  Q->front->next=NULL;

 }



void EnQueue(LinkQueue *Q,int e)    //�����㷨

{ QueuePtr p;

  p=(QueuePtr)malloc(sizeof(Qnode));

  p->data=e;

  p->next=NULL;

  Q->rear->next=p;

  Q->rear=p;

}



int QueueEmpty(LinkQueue *Q)   //�����пյ��㷨

{

       return(Q->front==Q->rear? 1:0);

}



void DeQueue(LinkQueue *Q,int *e)    //����

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
         visited[i] = FALSE;   //��־��ʼ��
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
