#include <stdio.h>
#include <stdlib.h>
#define INFINITY    100000   // 最大值∞
#define MAX_VERTEX_NUM  10+1    //最大顶点个数


typedef struct ArcCell// 弧的定义
{
     int  adj;          // VRType是顶点关系类型，
                             // 对无权图，用1或0表示相邻否，
                         // 对带权网，则为权值类型
     int  *info;   // 该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct
{                           // 图的定义
      char  vexs[MAX_VERTEX_NUM];// 顶点向量
      AdjMatrix  arcs;                     // 邻接矩阵
      int  vexnum, arcnum;       // 图的当前顶点数和弧数
      //GraphKind  kind;                  // 图的种类标志
}Graph;

struct closedge
{
     int  adjvex;  // U集中的顶点序号
     int lowcost;  // 边的权值
}closedge [MAX_VERTEX_NUM];

int LocateVex (Graph G, char u)
{
    int i;
    for(i = 1 ; i < MAX_VERTEX_NUM ; i++)
    {
        if(G.vexs[i] == u)
        {
            return i;
        }
    }
    printf("没有找到相关点\n");
    return -1;
}

int minimun(closedge)
{
    int i, j;
    int min = 1000;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        if(min > closedge[i].lowcost && closedge[i].lowcost != -1) // 标记若两个点不相邻则权值为-1
        {
            min = closedge[i].lowcost;
            j = i;
        }
    }
    return j;
}

/*void MiniSpanTree_P(Graph G, int u) //用普里姆算法从顶点u出发构造网G的最小生成树
{
    int start;
    int i, k, j;
    start = u;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        closedge[i].lowcost = G.arcs[start][i].adj;
        closedge[i].adjvex = -1;    //初始化该点还未加入到生成树中
    }
    closedge[start].adjvex = 0;    //将初始点加入到生成树中
    G.vexs[start] = start;
    for(i = 1 ; i < MAX_VERTEX_NUM - 1 ; i++)
    {
        int min = INFINITY;
        int v = -1;
        for(j = 1 ; j <  MAX_VERTEX_NUM ; j++)
        {
            if(closedge[j].adjvex != -1 && closedge[j].lowcost < min)
            {
                min = closedge[j].lowcost;
                v = j;
            }

        }
        if(v != -1)
        {
            printf("%d %d %d\n",G.vexs[v],v,closedge[v].lowcost);
            closedge[v].adjvex = 0; //V点已被标记

        }
        for(j = 1 ; j < MAX_VERTEX_NUM ; j++)
        {
            if( closedge[j].adjvex != -1 && G.arcs[v][j].adj < closedge[j].lowcost )
            {
                closedge[j].lowcost =  G.arcs[v][j].adj;
                G.vexs[j] = v;
            }
        }

    }


   /* k = LocateVex ( G, u );

    if(k == -1)
    {
        return;
    }
    for ( j=0; j < G.vexnum; j++)  // 辅助数组初始化
    {

        if (j!=k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }
                                    // {adjvex, lowcost}
    closedge[k].lowcost = 0;          // 初始，U＝{u}
    for (i=1; i<G.vexnum; ++i) {//选择其余N-1个顶点
        k = minimum(closedge);
                            // 求出加入生成树的下一个顶点(k)
        // 此时closedge[k].lowcost=
        // MIN{closedge[vi ].lowcost|closedge[vi].lowcost>0, Vi∈V-U}
  printf(closedge[k].adjvex, G.vexs[k]);
                               // 输出生成树上一条边的两个顶点
  closedge[k].lowcost = 0;    // 第k顶点并入U集
  for (j=0; j<G.vexnum; ++j)
                           // 修改其它顶点的最小边
     if (G.arcs[k][j].adj < closedge[j].lowcost)
                                       // 新顶点并入U后重新选择最小边
        closedge[j] = { G.vexs[k], G.arcs[k][j].adj };

    }

}*/

void MiniSpanTree_P(Graph G, char start)
{
    int i, j, k, mark[MAX_VERTEX_NUM];
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        mark[i] = -1;
    }
    k = LocateVex(G,start);
    for(j = 0 ; j < G.vexnum ; j++)
    {
        if(j != k)
        {
            closedge[j].adjvex = k;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }
    mark[k] = 0; //标记初始点被访问过了
    closedge[k].lowcost = 0;
    for(j = 0 ; j < G.vexnum ; j++)
    {
        k = minimun(closedge);
        if(G.arcs[k][j].adj < closedge[j].lowcost && mark[k] == -1)
        {
            closedge[j].adjvex = k;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }


}



int main()
{
    int i;
}
