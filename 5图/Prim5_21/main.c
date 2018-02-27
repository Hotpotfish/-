#include <stdio.h>
#include <stdlib.h>
#define INFINITY    100000   // ���ֵ��
#define MAX_VERTEX_NUM  10+1    //��󶥵����


typedef struct ArcCell// ���Ķ���
{
     int  adj;          // VRType�Ƕ����ϵ���ͣ�
                             // ����Ȩͼ����1��0��ʾ���ڷ�
                         // �Դ�Ȩ������ΪȨֵ����
     int  *info;   // �û������Ϣ��ָ��
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct
{                           // ͼ�Ķ���
      char  vexs[MAX_VERTEX_NUM];// ��������
      AdjMatrix  arcs;                     // �ڽӾ���
      int  vexnum, arcnum;       // ͼ�ĵ�ǰ�������ͻ���
      //GraphKind  kind;                  // ͼ�������־
}Graph;

struct closedge
{
     int  adjvex;  // U���еĶ������
     int lowcost;  // �ߵ�Ȩֵ
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
    printf("û���ҵ���ص�\n");
    return -1;
}

int minimun(closedge)
{
    int i, j;
    int min = 1000;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        if(min > closedge[i].lowcost && closedge[i].lowcost != -1) // ����������㲻������ȨֵΪ-1
        {
            min = closedge[i].lowcost;
            j = i;
        }
    }
    return j;
}

/*void MiniSpanTree_P(Graph G, int u) //������ķ�㷨�Ӷ���u����������G����С������
{
    int start;
    int i, k, j;
    start = u;
    for(i = 0 ; i < MAX_VERTEX_NUM ; i++)
    {
        closedge[i].lowcost = G.arcs[start][i].adj;
        closedge[i].adjvex = -1;    //��ʼ���õ㻹δ���뵽��������
    }
    closedge[start].adjvex = 0;    //����ʼ����뵽��������
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
            closedge[v].adjvex = 0; //V���ѱ����

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
    for ( j=0; j < G.vexnum; j++)  // ���������ʼ��
    {

        if (j!=k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }
                                    // {adjvex, lowcost}
    closedge[k].lowcost = 0;          // ��ʼ��U��{u}
    for (i=1; i<G.vexnum; ++i) {//ѡ������N-1������
        k = minimum(closedge);
                            // �����������������һ������(k)
        // ��ʱclosedge[k].lowcost=
        // MIN{closedge[vi ].lowcost|closedge[vi].lowcost>0, Vi��V-U}
  printf(closedge[k].adjvex, G.vexs[k]);
                               // �����������һ���ߵ���������
  closedge[k].lowcost = 0;    // ��k���㲢��U��
  for (j=0; j<G.vexnum; ++j)
                           // �޸������������С��
     if (G.arcs[k][j].adj < closedge[j].lowcost)
                                       // �¶��㲢��U������ѡ����С��
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
    mark[k] = 0; //��ǳ�ʼ�㱻���ʹ���
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
