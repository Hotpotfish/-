#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "string.h"
/*ĳ����Ӫҵ������6��Ӫҵ���ڣ������Ŷ�ϵͳ�㲥�кţ������е�ҵ���Ϊ���������п�����ƿ������֡�
������ҵ��ָ��1�Ŵ��ڣ����п�ҵ��ָ��2��3��4�Ŵ��ڣ���ƿ�ҵ��ָ��5��6�Ŵ��ڡ�
�����5��6�Ŵ���ȫæ����2��3��4�Ŵ����п���ʱ����ƿ�ҵ��Ҳ�����ڿ��е�2��3��4�Ŵ���֮һ����
�ͻ���š�ҵ����ɿ�����Ϊ������Ϣ��Ҫ�������ʱ��ʾ6��Ӫҵ���ڵ�״̬�������ӣ�ѡ����*/

typedef struct Customer
{
    char whichCard[30];       //�û�Ҫ�����ҵ��
  //  char name[10];
    int Number;
}Customer;

struct Customer *rec;
int number, read;
number = 0;
read = 0;




typedef struct accumulationFundWindow   //������
{
    int serialNumber;                   //���ڵı��
    int isBusy;
    Customer *now;

}accumulationFundWindow;

typedef struct debitCardWindow   //���п�
{
    int serialNumber;
    int isBusy;
    Customer *now;
}debitCardWindow;

typedef struct financeCardWindow   //��ƿ�
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

typedef struct CustomerNode             //�û����еĽ��
{
    Customer c;
    struct Node *next;
}Node;

typedef struct linkQueue     //�û��ŶӶ���
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
    printf("���г�ʼ���ɹ�!\n");
}

int  InitQueue(linkQueue *Q)   //���ֿ��Ķ���
{
        // Q = (linkQueue *)malloc(sizeof(linkQueue) * 3);
      //  Q = (linkQueue *)malloc(sizeof(linkQueue));
        Q->front = (Node *)malloc(sizeof(Node));
        Q->numberofCustomer = 0;
        if(Q->front == NULL)
        {
            printf("�ڴ�ռ���䲻��!\n");
            return 1;
        }
        Q->rear = Q->front;
        Q->front->next = NULL;

      //  printf("�ͻ����г�ʼ���ɹ�!\n");
     printf("�ͻ����г�ʼ���ɹ�!\n");
    return 0;
}

int enQueue(linkQueue Q[3], Customer c)  //�ͻ��ȴ�����(�ź�)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->c.Number = number;
    c.Number = number;
    customerCopy(&(p->c), c);//��¼�û������
    customerCopy(&(rec[number]), c);
    printf("���Ϊ%d���û��Ѿ���¼���ҽ���%s����\n",number,&(c.whichCard));
    number++;
    if(strcmp(c.whichCard,"accumulationFund") == 0)
    {

        if(p == NULL)
        {
            printf("�ڴ����ʧ��!\n");
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
                printf("�ڴ����ʧ��!\n");
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
                printf("�ڴ����ʧ��!\n");
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
        printf("�ӿ�!\n");
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
            printf("�û�����%d�Ŵ��ڰ���ҵ��!\n",B->afw.serialNumber);
        }
        else
        {
             printf("����æ��ʱ�޷�����ҵ��!\n");
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
                printf("�û�����%d�Ŵ��ڰ���ҵ��!\n",B->dcw[j].serialNumber);
                return;
            }
            else
                printf("%d�Ŵ���æ���޷�����ҵ��!\n",B->dcw[j].serialNumber);
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
                printf("�û�����%d�Ŵ��ڰ���ҵ��!\n",B->fcw[j].serialNumber);
                return;
            }
            else
            {
                 printf("%d�Ŵ���æ���޷�����ҵ��!\n",B->fcw[j].serialNumber);
            }
        } //���5,6ȫ��æ��Ѱ2,3,4���Ƿ��п�
        for(j = 0 ; j < 3 ; j++)
        {

            if(B->dcw[j].isBusy == 0)
            {
                customerCopy((B->dcw->now ), delQueue(Q[2]));
                B->dcw->isBusy = 1;
                read ++;
                printf("�û�����%d�Ŵ��ڰ���ҵ��!\n",B->dcw[j].serialNumber);
                return;
            }
            else
                printf("%d�Ŵ���æ���޷�����ҵ��!\n",B->dcw[j].serialNumber);
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
        printf("%d�Ŵ��ڵ��û��Ѿ�������ҵ���뿪��̨!\n",B->afw.serialNumber);
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
                printf("%d�Ŵ��ڵ��û��Ѿ�������ҵ���뿪��̨!\n",B->dcw[i].serialNumber);
                return;
            }
            else if(B->dcw[i].serialNumber == Number && B->dcw[i].isBusy == 0)
            {
                printf("%d�Ŵ��ڿ�����...!\n",B->dcw[i].serialNumber);
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
                printf("%d�Ŵ��ڵ��û��Ѿ�������ҵ���뿪��̨!\n",B->fcw[i].serialNumber);
                return;
            }
            else if(B->fcw[i].serialNumber == Number && B->fcw[i].isBusy == 0)
            {
                printf("%d�Ŵ��ڿ�����...!\n",B->fcw[i].serialNumber);
            }
        }
    }

}
void printfBank(Bank *B)
{
    int i;
    printf("----------\n");
    printf("%d�Ŵ���״̬:\n",B->afw.serialNumber);
    printf("�Ƿ�æµ:%d\n",B->afw.isBusy);
    for(i = 0 ; i < 3 ; i++)
    {
        printf("%d�Ŵ���״̬:\n",B->dcw[i].serialNumber);
        printf("�Ƿ�æµ:%d\n",B->dcw[i].isBusy);
    }
    for(i = 0 ; i < 2 ; i++)
    {
        printf("%d�Ŵ���״̬:\n",B->fcw[i].serialNumber);
        printf("�Ƿ�æµ:%d\n",B->fcw[i].isBusy);
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
