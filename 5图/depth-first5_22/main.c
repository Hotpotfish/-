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

void Initvisited(int *visited[MAX_VERTEX_NUM])
{
    int i;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        visited[i] = 0;
    }
    return;
}

void DFS(Graph G, int v)   //��ĳ����㿪ʼ
{
    ArcNode *p;
    visited[v] = TRUE;
    printf("%d\n",G.vertices[v].number);
    for(p = G.vertices[v].firstarc ; p != NULL ; p = p->nextarc)
    {
        if(!visited[p->adjvex])
        {
            DFS(G,p->adjvex);
        }
    }
}


int main()
{
    printf("Hello world!\n");
    return 0;
}
