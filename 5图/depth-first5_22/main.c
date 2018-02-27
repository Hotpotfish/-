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

void Initvisited(int *visited[MAX_VERTEX_NUM])
{
    int i;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        visited[i] = 0;
    }
    return;
}

void DFS(Graph G, int v)   //从某个结点开始
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
