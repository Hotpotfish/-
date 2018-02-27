#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "malloc.h"
#include "string.h"
#define MAXSIZE 4
typedef struct Lot     //ͣ��������ĳ�λ
{
    char License[6];
    clock_t startTime, leaveTime;
    int isThereACar;
}Lot;
typedef struct ParkingLot     //ͣ����
{
    Lot *L;
    int numberOfCars;
} ParkingLot;
typedef struct car     //����  ֻ�г��ƺ�
{
    char License[6];
}car;
typedef struct qNode     //�����еĳ������
{
    car c;
    struct qNode *next;
}qNode;
typedef struct linkQueue    //��ʽ��������
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
        printf("�����ڴ����ʧ��!\n");
        return;
    }
    Q->rear = Q->front;
    Q->front->next = NULL;
    Q->NumberOfCar = 0;
    printf("���г�ʼ���ɹ�!\n");
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
        printf("�ڴ����ʧ��\n");
        return ;
    }
    pl->numberOfCars = 0;
    printf("ͣ������ʼ���ɹ�!\n");
    return;
}

int  enQueue(linkQueue *Q, car c)   //����
{
    qNode *p;
    p = (qNode *)malloc(sizeof(qNode));
    if(p == NULL)
    {
        printf("���н���ڴ����ʧ��!\n");
        return 1;
    }
    p->c = c;
    p->next = NULL;
  //  Q->rear->next = (qNode *)malloc(sizeof(qNode));
    Q->rear->next = p;
    Q->rear = p;
    Q->NumberOfCar ++;
    printf("���ƺ�Ϊ\"%s\"�ĳ��Ѿ��������\n",c.License);
    return 0;
}
car delQueue(linkQueue *Q)  //����
{
    qNode *p;
    car c;
    if(Q->front == Q->rear)
    {
        printf("���пշ��ض���ͷָ��\n");
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
    printf("���ƺ�Ϊ\"%s\"�ĳ��Ѿ��뿪����\n",c.License);
    return c;
}
int isQueueEm(linkQueue *Q)
{
    if(Q->front == Q->rear)
    {
        printf("���д�ʱ��״Ϊ:��\n");
        return 1;
    }
    else
    {
        printf("���д�ʱ��״Ϊ:�ǿ�!\n");
        printf("�ȴ��ĳ�����Ϊ%d\n",Q->NumberOfCar);
        return 0;
    }

}
int findEmLot(ParkingLot *pl,linkQueue *Q, car c)
{
    if(pl->numberOfCars == MAXSIZE)   //��ʱͣ�����ĳ����Ѿ����������ͣ�����ĳ�������еȴ�
    {
        printf("ͣ��������,��������еȴ�\n");
        enQueue(Q, c);
        return 0;
    }
    else if(pl->numberOfCars < MAXSIZE)   //��ʱͣ�����пգ�Ҳ���пյĻ�������ֱ�ӽ���ͣ����
    {
            int i;
            for(i = 0 ; i < 100 ; i++)
            {
                if(pl->L[i].isThereACar == 0)
                {
                    strcpy(pl->L[i].License, c.License);        //(delQueue(Q).License);
                    pl->L[i].startTime = clock();
                    pl->L[i].isThereACar = 1;
                    printf("���ƺ�Ϊ%s�ĳ��Ѿ�����ͣ����[%d]ͣ��λ���Ҽ�ʱ�շ�\n",c.License,i);
                    pl->numberOfCars ++;
                    return 0;
                }
            }
      /*  for(i = 0 ; i < 100 ; i++)
        {
            if(pl->L[i]->isThereACar == 0)
            {
                *(pl->L[i]->License) = c.License;
                printf("����Ϊ%c�ĳ�����ͣ����\n",pl->L[i]->License);
                pl->L[i]->startTime = clock();
                return 0;
            }
        }*/
    }

    /*else if(isQueueEm(Q) == 0)   //��ʱ���в���
    {                            //��ͣ�������п�λ
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
                    printf("���ƺ�Ϊ%s�ĳ��Ѿ�����ͣ������%d��ͣ��λ���Ҽ�ʱ�շ�\n",enter.License,i);
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
    if(isQueueEm(Q) == 0)  //��ʱ�ӷǿգ���������ȥ���������ĳ�������
    {
        for(i = 0 ; i < MAXSIZE ; i++)
        {
            if(strcmp(pl->L[i].License, c.License) == 0)
            {
                pl->L[i].License= delQueue(Q).License;
                pl->L[i].startTime = clock();
                printf("���ƺ�Ϊ%s�ĳ��Ѿ���[%d]��ͣ��λ�뿪",c.License,i);
            }
        }

    }
    else if(isQueueEm(Q) == 1)  //��ʱ�ӿ�
    {
        for(i = 0 ; i < MAXSIZE ; i++)
        {
            if(strcmp(pl->L[i].License, c.License) == 0)
            {
               strcpy(pl->L[i].License,"00000");
               pl->L[i].isThereACar = 0;
               pl->L[i].startTime = 0;
               printf("���ƺ�Ϊ%s�ĳ��Ѿ���[%d]��ͣ��λ�뿪\n",c.License,i);
            }
        }

    }
}
void printfParkingLot(ParkingLot *pl)
{
    int i;
    printf("ͣ������Ϣ:\n");
    for(i = 0 ; i < MAXSIZE ; i++)
    {
        if(pl->L[i].isThereACar == 1)
        {
            printf("������Ϣ:\n");
            printf("����:%s\n",pl->L[i].License);
            printf("����ʱ��:");
       //     printf(pl->L[i].startTime);
            printf("\n");
            printf("ͣ��λ:[%d]",i);
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
