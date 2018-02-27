#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#define   MAXQSIZE  4

typedef struct Member
{
    int Subscript;
    int Value;
}Member;

typedef struct seQueuetp
{
    Member *base;
    int front;
    int rear;
}seQueuetp;

int InitQueue(seQueuetp *Q)
{
    Q->base = (Member *)malloc(MAXQSIZE * sizeof(Member));
    if(!Q->base)
    {
        exit(0);
    }
    Q->front = Q->rear = 0;
    return 1;
}

int QueueLength(seQueuetp Q)
{
    return(Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;

}

int enterQueue(seQueuetp *Q, Member m)
{
   /* if((Q->rear + 1) % MAXQSIZE == Q->front)
    {
        printf("队列满,f%d拒绝入队\n",m.Subscript);
        return 0;
    }
    */

        printf("f%d入队(值：%d)\n",m.Subscript,m.Value);
        Q->base[Q->rear] = m;
        Q->rear = (Q->rear + 1) % MAXQSIZE;
        return 1;
}

int delQueue(seQueuetp *Q, Member *m)
{


        printf("f%d出队\n",Q->base[Q->front].Subscript);
        *m = Q->base[Q->front];
        Q->front = (Q->front + 1) % MAXQSIZE;
        return 1;
}



int main()
{
    int i, j;
    seQueuetp Q;
    InitQueue(&Q);
    Member f0, f1, f2, f3, fi;
    f0.Subscript = 0;
    f0.Value = 0;
    f1.Subscript = 1;
    f1.Value = 0;
    f2.Subscript = 2;
    f2.Value = 0;
    f3.Subscript = 3;
    f3.Value = 1;
    enterQueue(&Q, f0);
    enterQueue(&Q, f1);
    enterQueue(&Q, f2);
    enterQueue(&Q, f3);
    i = 4;
    while(1)
    {
        fi.Value = 0;
        fi.Subscript = i;
        for(j = 0 ; j < 4 ; j++)
        {
            fi.Value += Q.base[j].Value;
        }
        if(fi.Value > 200)
        {
            printf("fn+1的值为%d",fi.Value);
            return 0;
        }
        enterQueue(&Q, fi);
        i++;


    }

   /* while(1)
    {
        fi.Subscript = i;
        for(j = 0 ; j < MAXQSIZE ; j++)
        {
            fi.Value += Q.me[j].Value;
        }
        if(Q.me[Q->front].Value > 200 && Q->me[Q->rear].Value <= 200)
        {
            printf("fn+1 = %d fn = %d\n", Q->me[Q->front].Value, Q->me[Q->rear].Value);
            return 0 ;

        }
        enterQueue(&Q, &fi);
    }
    //return 0;
    */

}
