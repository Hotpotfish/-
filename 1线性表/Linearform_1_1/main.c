#include "stdio.h"
#include "malloc.h"

#define  LIST_INIT_SIZE     30
#define  LISTINCREMENT    10


typedef struct Worker
{
    char name[20];
    long number;
    char position[20];
}worker;


typedef struct
{
    worker *w; //存储空间的基址
    int length ;
    int listsize ;
}workerList;

int InitList_wk(workerList *L) //初始化员工列表
{
    printf("初始化员工列表\n");
    printf("......\n");
    L->w = (worker*)malloc(LIST_INIT_SIZE * sizeof(worker)); //为员工的数组分配空间
    if (!L->w)
    {
        exit(1);   //如果分配不成功
        printf("分配不成功!\n");
    }
    else
    {
        printf("员工列表初始化成功！\n");
    }
        L->length = 0;
        L->listsize = LIST_INIT_SIZE;
       // exit(1);   //如果分配不成功

    return 0;
}

int ListInsert_wk(workerList *L,int i,worker w)
{
    worker *p,*q;
    q = &(L->w[i - 1]);     //q指示插入的位置
    for(p = &(L->w[L->length - 1]) ; p >= q ; --p)
        *(p + 1) = *p;
    *q = w;
    ++L->length;
    printf("员工插入成功!\n");
    return 0;
}

int ListDelete_wk(workerList *L, int i, worker w)
{
    worker *p,*q;
    if ((i < 1) || (i > L->length))
    {
        printf("删除失败!\n");
        return 1;

    }
    p = &(L->w[i-1]);
    w = *p;
    q = L->w + L->length - 1;
    for (++p; p <= q; ++p)
    {
        *(p-1) = *p;
    }
    --L->length;
    printf("员工删除成功!\n\n\n");
    return 0;
}
int ExtendList_wk(workerList *L)
{
    L->w = (worker*)realloc(L->w, (L->listsize + LISTINCREMENT)*sizeof(worker));

    if (!L->w)
    {
     exit(1);
     printf("列表扩展失败!\n")  ;
    }
    else{
        printf("列表扩展成功!\n\n\n");
    }
        L->listsize += LISTINCREMENT;
}

int main()
{
    workerList wk;
    InitList_wk(&wk);
    for(;;)
    {
        int ch;
        printf("选择将要进行的操作:\n");
        printf("1.添加员工\n");
        printf("2.删除员工\n");
        printf("3.显示员工列表\n");
  //      printf("3.扩展一个单位(10人次)员工列表\n");
        scanf("%d", &ch);
        switch(ch)
        {
        case 1:
            {
                worker wo;
                printf("请录入当前员工信息:\n");
                printf("姓名:\n");
                scanf("%s", wo.name);
                fflush(stdin);
                printf("工号:\n");
                scanf("%ld", &wo.number);
                fflush(stdin);
                printf("职务:\n");
                scanf("%s",wo.position);
                fflush(stdin);
                printf("员工信息录入成功！\n\n");
                int nu;
                printf("请输入要添加的位置(当前员工数:%d):\n",wk.length);
                scanf("%d",&nu);
                while(nu > wk.listsize)
                {
                    ExtendList_wk(&wk);
                }
                ListInsert_wk(&wk,nu,wo);
            }
            break;
        case 2:
            {
                worker wo;
                int nu;
                printf("请输入您要删除第几个员工:\n");
                scanf("%d", &nu);
                ListDelete_wk(&wk,nu,wo);
                break;
            }
        case 3:
            {
                int i;
                if(wk.length == 0)
                {
                    printf("暂无员工信息\n");
                    return;
                }
                for(i = 0 ; i < wk.length ; i++)
                {
                   printf("\n\n\n");
                    printf("第%d位员工相关信息:\n",i);
                    printf("姓名:\n");
                    printf("%s\n",wk.w[i].name);
                    printf("工号:\n");
                    printf("%ld\n",wk.w[i].number);
                    printf("职务:\n");
                    printf("%s\n",wk.w[i].position);
                    printf("------------\n");

                }


            }

        }
    }
    return 0;
}



