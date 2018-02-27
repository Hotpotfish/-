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



int exist_path_DFS(Graph G,int i,int j) // 从顶点v出发，深度优先搜索遍历连通图 G
{
    if(i == j)
    {
        printf("存在路径\n");
        return TRUE;
    }
    ArcNode *p;
    visited[i] = TRUE;
    for(p = G.vertices[i].firstarc; p != NULL ; p = p->nextarc)
    {
        int k;
        k = p->adjvex;
        if(!visited[k] && !visited[j])   //此时k节点未被访问
        {
            exist_path_DFS(G,k,j);
        }
        else
        {
            printf("存在路径!\n");
            return TRUE;
        }

     //   exist_path(k,j)
       // if()
    }
    printf("不存在路径!\n");
    return 0;
}


int main()
{

}
