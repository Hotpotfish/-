#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "string.h"
/*某银行营业厅共有6个营业窗口，设有排队系统广播叫号，该银行的业务分为公积金、银行卡、理财卡等三种。
公积金业务指定1号窗口，银行卡业务指定2、3、4号窗口，理财卡业务指定5、6号窗口。
但如果5、6号窗口全忙，而2、3、4号窗口有空闲时，理财卡业务也可以在空闲的2、3、4号窗口之一办理。
客户领号、业务完成可以作为输入信息，要求可以随时显示6个营业窗口的状态。（复杂，选作）*/

typedef struct Customer
{
    char whichCard[30];       //用户要办理的业务
  //  char name[10];
    int Number;
}Customer;

struct Customer *rec;
int number, read;
number = 0;
read = 0;




typedef struct accumulationFundWindow   //公积金
{
    int serialNumber;                   //窗口的编号
    int isBusy;
    Customer *now;

}accumulationFundWindow;

typedef struct debitCardWindow   //银行卡
{
    int serialNumber;
    int isBusy;
    Customer *now;
}debitCardWindow;

typedef struct financeCardWindow   //理财卡
{
    int serialNumber;
    int isBusy;
    Customer *now;

}financeCardWindow;

typedef struct Bank
{
    accumulationFundWindow afw;
    debitCardWindow dcw[3];
    financeCardWindow fcw[2];
}Bank;

typedef struct CustomerNode             //用户队列的结点
{
    Customer c;
    struct Node *next;
}Node;

typedef struct linkQueue     //用户排队队列
{
    Node *front;
    Node *rear;
    int numberofCustomer;
}linkQueue;

int InitBank(Bank *B)
{
    int i;
    B->afw.isBusy = 0;
    B->afw.serialNumber = 1;
    B->afw.now =(Customer *)malloc(sizeof(Customer));
    rec = (Customer *)malloc(sizeof(Customer) * 100);
    for(i = 0 ; i < 3 ; i++)
    {
        B->dcw[i].isBusy = 0;
        B->dcw[i].serialNumber = i + 2;
        B->dcw[i].now = (Customer *)malloc(sizeof(Customer));
    }
    for(i = 0 ; i < 2 ; i++)
    {
        B->fcw[i].isBusy = 0;
        B->fcw[i].serialNumber = i + 5;
        B->fcw[i].now = (Customer *)malloc(sizeof(Customer));
    }
    printf("银行初始化成功!\n");
}

int  InitQueue(linkQueue *Q)   //三种卡的队列
{
        // Q = (linkQueue *)malloc(sizeof(linkQueue) * 3);
      //  Q = (linkQueue *)malloc(sizeof(linkQueue));
        Q->front = (Node *)malloc(sizeof(Node));
        Q->numberofCustomer = 0;
        if(Q->front == NULL)
        {
            printf("内存空间分配不足!\n");
            return 1;
        }
        Q->rear = Q->front;
        Q->front->next = NULL;

      //  printf("客户队列初始化成功!\n");
     printf("客户队列初始化成功!\n");
    return 0;
}

int enQueue(linkQueue Q[3], Customer c)  //客户等待队列(排号)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->c.Number = number;
    c.Number = number;
    customerCopy(&(p->c), c);//记录用户的情况
    customerCopy(&(rec[number]), c);
    printf("编号为%d的用户已经记录并且进入%s队列\n",number,&(c.whichCard));
    number++;
    if(strcmp(c.whichCard,"accumulationFund") == 0)
    {

        if(p == NULL)
        {
            printf("内存分配失败!\n");
            return 0;
        }
        p->c = c;
        p->next = NULL;
        Q[0].rear->next = p;
        Q[0].rear = p;
        Q[0].numberofCustomer ++;
    }
    else if(strcmp(c.whichCard,"debitCard") == 0)
    {

        if(p == NULL)
            {
                printf("内存分配失败!\n");
                return 0;
            }
        p->c = c;
        p->next = NULL;
        Q[1].rear->next = p;
        Q[1].rear = p;
        Q[1].numberofCustomer ++;
    }
     else if(strcmp(c.whichCard,"financeCard") == 0)
    {

        if(p == NULL)
            {
                printf("内存分配失败!\n");
                return 0;
            }
        p->c = c;
        p->next = NULL;
        Q[2].rear->next = p;
        Q[2].rear = p;
        Q[2].numberofCustomer ++;
    }
}

Customer delQueue(linkQueue Q)
{
    Node *p;
    Customer x;
    p = (Node *)malloc(sizeof(Node));
    if(Q.front == Q.rear)
    {
        printf("队空!\n");
        return Q.front->c;
    }
    else
    {
        p->next = Q.front->next;
        x = p->c;
        if(Q.rear == p)
        {
            Q.rear = Q.front;
        }
        free(p);
        return x;
    }
    Q.numberofCustomer --;
}

void customerCopy(Customer *c0, Customer c1)
{
    c0->Number = c1.Number;
    strcpy(c0->whichCard, c1.whichCard);
    return;
}

void work(Bank *B, linkQueue Q[3])
{
    int i;
    Customer cu;
    customerCopy(&cu,rec[read]);   //
    if(strcmp(cu.whichCard,"accumulationFund") == 0)
    {
        if(B->afw.isBusy == 0)
        {
            customerCopy((B->afw.now), delQueue(Q[0]));
            B->afw.isBusy = 1;
            read ++;
            printf("用户进入%d号窗口办理业务!\n",B->afw.serialNumber);
        }
        else
        {
             printf("窗口忙暂时无法办理业务!\n");
             return;
        }

    }
    else if(strcmp(cu.whichCard,"debitCard") == 0)
    {
        int j;
        for(j = 0 ; j < 3 ; j++)
        {

            if(B->dcw[j].isBusy == 0)
            {
                customerCopy((B->dcw[j].now), delQueue(Q[1]));
                B->dcw[j].isBusy = 1;
                read ++;
                printf("用户进入%d号窗口办理业务!\n",B->dcw[j].serialNumber);
                return;
            }
            else
                printf("%d号窗口忙暂无法办理业务!\n",B->dcw[j].serialNumber);
        }
        return;
    }
    else if(strcmp(cu.whichCard,"financeCard") == 0)
    {
        int j;
        for(j = 0 ; j < 2 ; j++)
        {
            if(B->fcw[j].isBusy == 0)
            {
                customerCopy((B->fcw[j].now), delQueue(Q[2]));
                B->fcw[j].isBusy = 1;
                read ++;
                printf("用户进入%d号窗口办理业务!\n",B->fcw[j].serialNumber);
                return;
            }
            else
            {
                 printf("%d号窗口忙暂无法办理业务!\n",B->fcw[j].serialNumber);
            }
        } //入过5,6全部忙找寻2,3,4号是否有空
        for(j = 0 ; j < 3 ; j++)
        {

            if(B->dcw[j].isBusy == 0)
            {
                customerCopy((B->dcw->now ), delQueue(Q[2]));
                B->dcw->isBusy = 1;
                read ++;
                printf("用户进入%d号窗口办理业务!\n",B->dcw[j].serialNumber);
                return;
            }
            else
                printf("%d号窗口忙暂无法办理业务!\n",B->dcw[j].serialNumber);
        }
        return;
    }
}

void finishjob(Bank *B, linkQueue Q[3], int Number)
{
    if(Number == 1)
    {
        B->afw.isBusy = 0;
        B->afw.now = (Customer *)malloc(sizeof(Customer));
        printf("%d号窗口的用户已经办理完业务离开柜台!\n",B->afw.serialNumber);
        return;
    }
    else if(Number > 1 && Number < 5)
    {
        int i;
        for(i = 0 ; i < 3 ; i++)
        {
            if(B->dcw[i].serialNumber == Number && B->dcw[i].isBusy == 1)
            {
                B->dcw[i].isBusy = 0;
                B->dcw[i].now = (Customer *)malloc(sizeof(Customer));
                printf("%d号窗口的用户已经办理完业务离开柜台!\n",B->dcw[i].serialNumber);
                return;
            }
            else if(B->dcw[i].serialNumber == Number && B->dcw[i].isBusy == 0)
            {
                printf("%d号窗口空闲中...!\n",B->dcw[i].serialNumber);
            }
        }

    }
    else if(Number == 5 || Number == 6)
    {
        int i;
        for(i = 0 ; i < 2 ;i++)
        {
             if(B->fcw[i].serialNumber == Number && B->fcw[i].isBusy == 1)
            {
                B->fcw[i].isBusy = 0;
                B->fcw[i].now = (Customer *)malloc(sizeof(Customer));
                printf("%d号窗口的用户已经办理完业务离开柜台!\n",B->fcw[i].serialNumber);
                return;
            }
            else if(B->fcw[i].serialNumber == Number && B->fcw[i].isBusy == 0)
            {
                printf("%d号窗口空闲中...!\n",B->fcw[i].serialNumber);
            }
        }
    }

}
void printfBank(Bank *B)
{
    int i;
    printf("----------\n");
    printf("%d号窗口状态:\n",B->afw.serialNumber);
    printf("是否忙碌:%d\n",B->afw.isBusy);
    for(i = 0 ; i < 3 ; i++)
    {
        printf("%d号窗口状态:\n",B->dcw[i].serialNumber);
        printf("是否忙碌:%d\n",B->dcw[i].isBusy);
    }
    for(i = 0 ; i < 2 ; i++)
    {
        printf("%d号窗口状态:\n",B->fcw[i].serialNumber);
        printf("是否忙碌:%d\n",B->fcw[i].isBusy);
    }
    printf("----------\n");

}

int main()
{
    int i;
    Bank B;
    linkQueue Q[3];
    InitBank(&B);
    for(i = 0 ; i < 3 ; i++)
    {

        InitQueue(&Q[i]);
    }
    Customer c0, c1, c2, c3, c4, c5, c6;
    strcpy(c0.whichCard,"accumulationFund");
    strcpy(c1.whichCard,"debitCard");
    strcpy(c2.whichCard,"debitCard");
    strcpy(c3.whichCard,"debitCard");
    strcpy(c4.whichCard,"financeCard");
    strcpy(c5.whichCard,"financeCard");
    strcpy(c6.whichCard,"financeCard");
  //  strcpy(c7.whichCard,"")
    enQueue(Q,c0);
    enQueue(Q,c1);
    enQueue(Q,c2);
    enQueue(Q,c3);
    enQueue(Q,c4);
    enQueue(Q,c5);
    enQueue(Q,c6);
    printfBank(&B);
    work(&B, Q);
    work(&B, Q);
    work(&B, Q);
    work(&B, Q);
    work(&B, Q);
    work(&B, Q);
    work(&B, Q);
    printfBank(&B);
    finishjob(&B, Q, 5);
    finishjob(&B, Q, 5);
 //   work(&B, Q);
    printfBank(&B);

    work(&B, Q);
    printfBank(&B);
    finishjob(&B, Q, 1);
    printfBank(&B);
    finishjob(&B, Q, 2);
    printfBank(&B);
    finishjob(&B, Q, 3);
    printfBank(&B);
    finishjob(&B, Q, 4);
    printfBank(&B);
    finishjob(&B, Q, 5);
    printfBank(&B);
    finishjob(&B, Q, 6);
    printfBank(&B);

    //finishjob(&B, Q, 5);
    printf(" ");

}
