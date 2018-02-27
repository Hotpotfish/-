#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "malloc.h"
#include "string.h"
#define MAXSIZE 4
typedef struct Lot     //停车场里面的车位
{
    char License[6];
    clock_t startTime, leaveTime;
    int isThereACar;
}Lot;
typedef struct ParkingLot     //停车场
{
    Lot *L;
    int numberOfCars;
} ParkingLot;
typedef struct car     //车辆  只有车牌号
{
    char License[6];
}car;
typedef struct qNode     //队列中的车辆结点
{
    car c;
    struct qNode *next;
}qNode;
typedef struct linkQueue    //链式车辆队列
{
    qNode *front;
    qNode *rear;
    int NumberOfCar;
} linkQueue;


void InitQueue(linkQueue *Q)
{
    Q->front = (qNode *)malloc(sizeof(qNode));
    //Q->rear = (qNode *)malloc(sizeof(qNode));
    if(Q->front == NULL)
    {
        printf("队列内存分配失败!\n");
        return;
    }
    Q->rear = Q->front;
    Q->front->next = NULL;
    Q->NumberOfCar = 0;
    printf("队列初始化成功!\n");
}

void InitParkingLot(ParkingLot *pl)
{
    int i;
    pl->L= (Lot *)malloc(MAXSIZE * sizeof(Lot));
    for(i = 0 ; i < MAXSIZE ; i++)
    {
        strcpy(pl->L[i].License,"00000");
        pl->L[i].isThereACar = 0;
    }
    if(pl->L == NULL)
    {
        printf("内存分配失败\n");
        return ;
    }
    pl->numberOfCars = 0;
    printf("停车场初始化成功!\n");
    return;
}

int  enQueue(linkQueue *Q, car c)   //进队
{
    qNode *p;
    p = (qNode *)malloc(sizeof(qNode));
    if(p == NULL)
    {
        printf("队列结点内存分配失败!\n");
        return 1;
    }
    p->c = c;
    p->next = NULL;
  //  Q->rear->next = (qNode *)malloc(sizeof(qNode));
    Q->rear->next = p;
    Q->rear = p;
    Q->NumberOfCar ++;
    printf("车牌号为\"%s\"的车已经进入队列\n",c.License);
    return 0;
}
car delQueue(linkQueue *Q)  //出队
{
    qNode *p;
    car c;
    if(Q->front == Q->rear)
    {
        printf("队列空返回队列头指针\n");
        return Q->front->c;
    }
    p = Q->front->next;
    Q->front->next = p->next;
    c = p->c;
    if(Q->rear == p)
    {
        Q->rear = Q->front;
    }
    free(p);
    Q->NumberOfCar --;
    printf("车牌号为\"%s\"的车已经离开队列\n",c.License);
    return c;
}
int isQueueEm(linkQueue *Q)
{
    if(Q->front == Q->rear)
    {
        printf("队列此时现状为:空\n");
        return 1;
    }
    else
    {
        printf("队列此时现状为:非空!\n");
        printf("等待的车辆数为%d\n",Q->NumberOfCar);
        return 0;
    }

}
int findEmLot(ParkingLot *pl,linkQueue *Q, car c)
{
    if(pl->numberOfCars == MAXSIZE)   //此时停车场的车辆已经满了想进入停车场的车进入队列等待
    {
        printf("停车场已满,车进入队列等待\n");
        enQueue(Q, c);
        return 0;
    }
    else if(pl->numberOfCars < MAXSIZE)   //此时停车场有空，也队列空的话，车辆直接进入停车场
    {
            int i;
            for(i = 0 ; i < 100 ; i++)
            {
                if(pl->L[i].isThereACar == 0)
                {
                    strcpy(pl->L[i].License, c.License);        //(delQueue(Q).License);
                    pl->L[i].startTime = clock();
                    pl->L[i].isThereACar = 1;
                    printf("车牌号为%s的车已经进入停车场[%d]停车位并且计时收费\n",c.License,i);
                    pl->numberOfCars ++;
                    return 0;
                }
            }
      /*  for(i = 0 ; i < 100 ; i++)
        {
            if(pl->L[i]->isThereACar == 0)
            {
                *(pl->L[i]->License) = c.License;
                printf("车牌为%c的车进入停车场\n",pl->L[i]->License);
                pl->L[i]->startTime = clock();
                return 0;
            }
        }*/
    }

    /*else if(isQueueEm(Q) == 0)   //此时队列不空
    {                            //且停车场还有空位
        enQueue(Q, c);
        car enter;
        enter = delQueue(Q);
        int i;

        while(pl->numberOfCars <= MAXSIZE)
        {
            for(i = 0 ; i < 100 ; i++)
            {
                if(pl->L[i].isThereACar == 0)
                {
                    strcpy(pl->L[i].License, enter.License);        //(delQueue(Q).License);
                    pl->L[i].startTime = clock();
                    pl->L[i].isThereACar = 1;
                    printf("车牌号为%s的车已经进入停车场第%d个停车位并且计时收费\n",enter.License,i);
                    pl->numberOfCars ++;
                    return 0;
                }
            }
        }

    }
    */
}

int leaveParkingLot(ParkingLot *pl,linkQueue *Q, linkQueue *CQ, car c)
{
    int i;
    Lot l;
    if(isQueueEm(Q) == 0)  //此时队非空，当车辆出去后队列里面的车辆进队
    {
        for(i = 0 ; i < MAXSIZE ; i++)
        {
            if(strcmp(pl->L[i].License, c.License) == 0)
            {
                pl->L[i].License= delQueue(Q).License;
                pl->L[i].startTime = clock();
                printf("车牌号为%s的车已经从[%d]号停车位离开",c.License,i);
            }
        }

    }
    else if(isQueueEm(Q) == 1)  //此时队空
    {
        for(i = 0 ; i < MAXSIZE ; i++)
        {
            if(strcmp(pl->L[i].License, c.License) == 0)
            {
               strcpy(pl->L[i].License,"00000");
               pl->L[i].isThereACar = 0;
               pl->L[i].startTime = 0;
               printf("车牌号为%s的车已经从[%d]号停车位离开\n",c.License,i);
            }
        }

    }
}
void printfParkingLot(ParkingLot *pl)
{
    int i;
    printf("停车场信息:\n");
    for(i = 0 ; i < MAXSIZE ; i++)
    {
        if(pl->L[i].isThereACar == 1)
        {
            printf("车辆信息:\n");
            printf("车牌:%s\n",pl->L[i].License);
            printf("进入时间:");
       //     printf(pl->L[i].startTime);
            printf("\n");
            printf("停车位:[%d]",i);
        }
    }
}
int main()
{
    car c1, c2, c3, c4, c5;
   // c1.License[0]='a';
    strcpy(c1.License,"aaaaa");
    strcpy(c2.License,"bbbbb");
    strcpy(c3.License,"ccccc");
    strcpy(c4.License,"ddddd");
    strcpy(c5.License,"eeeee");
    ParkingLot pl;
    InitParkingLot(&pl);
    linkQueue Q, CQ;
    InitQueue(&Q);
    findEmLot(&pl,&Q,c1);
    findEmLot(&pl,&Q,c2);
    findEmLot(&pl,&Q,c3);
    findEmLot(&pl,&Q,c4);
    findEmLot(&pl,&Q,c5);
    leaveParkingLot(&pl,&Q, &CQ, c1);
    printfParkingLot(&pl);

    return 0;
}
