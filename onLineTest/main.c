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



int exist_path_DFS(Graph G,int i,int j) // �Ӷ���v�����������������������ͨͼ G
{
    if(i == j)
    {
        printf("����·��\n");
        return TRUE;
    }
    ArcNode *p;
    visited[i] = TRUE;
    for(p = G.vertices[i].firstarc; p != NULL ; p = p->nextarc)
    {
        int k;
        k = p->adjvex;
        if(!visited[k] && !visited[j])   //��ʱk�ڵ�δ������
        {
            exist_path_DFS(G,k,j);
        }
        else
        {
            printf("����·��!\n");
            return TRUE;
        }

     //   exist_path(k,j)
       // if()
    }
    printf("������·��!\n");
    return 0;
}


int main()
{

}
