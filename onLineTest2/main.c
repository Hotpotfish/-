#include "stdio.h"

#include "conio.h"

#define MAX_VERTEX_NUM 30

typedef struct ArcNode{

     int adjvex;

     struct ArcNode *nextarc;

}ArcNode;

typedef struct VNode{

     int data;

     ArcNode *firstarc;

}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{

     AdjList vertices;

     int vexnum,arcnum;

}ALGraph;

creat_DG_ALGraph(ALGraph *G){

   int i,j,k;ArcNode *p;

   p=NULL;

   printf("Please input: vexnum ,arcnum=:");

   scanf("%d,%d",&G->vexnum,&G->arcnum);

   printf("Please input VNode:\n");

   for(i=0;i<G->vexnum;i++)

     {scanf("%d",&G->vertices[i].data);

      G->vertices[i].firstarc=NULL;

     }

   for(i=0;i<G->vexnum;i++)

     printf("%d ",G->vertices[i].data);

   printf("\n");

   for(k=0;k<G->arcnum;k++)

       {p=(ArcNode*)malloc(sizeof(ArcNode));

        printf("please input edge <i,j>: ");

        scanf("%d,%d", &i, &j);

        printf("\n");

        p->adjvex = j;

        p->nextarc=G->vertices[i].firstarc;

        G->vertices[i].firstarc=p;

       }

}

int exist_path_DFS(ALGraph G,int i,int j){

    ArcNode *p;

    int k,visited[MAX_VERTEX_NUM];

    p=NULL;

    if(i==j) return 1;

    else {visited[i]=1;

          for(p=G.vertices[i].firstarc;p;p=p->nextarc)

             {k=p->adjvex;

              if(!visited[k]&&exist_path_DFS(G,k,j));

             }

          }

}

main()

{ALGraph *G;

int i,j;

G=NULL;

creat_DG_ALGraph(G);

printf("Please input i->j you want to find:\n");

scanf("%d,%d",&i,&j);

if(exist_path_DFS(*G,i,j)) printf("Exist the path!");

else printf("Not exist the path");

getch();

}
