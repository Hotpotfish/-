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
    worker *w; //�洢�ռ�Ļ�ַ
    int length ;
    int listsize ;
}workerList;

int InitList_wk(workerList *L) //��ʼ��Ա���б�
{
    printf("��ʼ��Ա���б�\n");
    printf("......\n");
    L->w = (worker*)malloc(LIST_INIT_SIZE * sizeof(worker)); //ΪԱ�����������ռ�
    if (!L->w)
    {
        exit(1);   //������䲻�ɹ�
        printf("���䲻�ɹ�!\n");
    }
    else
    {
        printf("Ա���б��ʼ���ɹ���\n");
    }
        L->length = 0;
        L->listsize = LIST_INIT_SIZE;
       // exit(1);   //������䲻�ɹ�

    return 0;
}

int ListInsert_wk(workerList *L,int i,worker w)
{
    worker *p,*q;
    q = &(L->w[i - 1]);     //qָʾ�����λ��
    for(p = &(L->w[L->length - 1]) ; p >= q ; --p)
        *(p + 1) = *p;
    *q = w;
    ++L->length;
    printf("Ա������ɹ�!\n");
    return 0;
}

int ListDelete_wk(workerList *L, int i, worker w)
{
    worker *p,*q;
    if ((i < 1) || (i > L->length))
    {
        printf("ɾ��ʧ��!\n");
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
    printf("Ա��ɾ���ɹ�!\n\n\n");
    return 0;
}
int ExtendList_wk(workerList *L)
{
    L->w = (worker*)realloc(L->w, (L->listsize + LISTINCREMENT)*sizeof(worker));

    if (!L->w)
    {
     exit(1);
     printf("�б���չʧ��!\n")  ;
    }
    else{
        printf("�б���չ�ɹ�!\n\n\n");
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
        printf("ѡ��Ҫ���еĲ���:\n");
        printf("1.���Ա��\n");
        printf("2.ɾ��Ա��\n");
        printf("3.��ʾԱ���б�\n");
  //      printf("3.��չһ����λ(10�˴�)Ա���б�\n");
        scanf("%d", &ch);
        switch(ch)
        {
        case 1:
            {
                worker wo;
                printf("��¼�뵱ǰԱ����Ϣ:\n");
                printf("����:\n");
                scanf("%s", wo.name);
                fflush(stdin);
                printf("����:\n");
                scanf("%ld", &wo.number);
                fflush(stdin);
                printf("ְ��:\n");
                scanf("%s",wo.position);
                fflush(stdin);
                printf("Ա����Ϣ¼��ɹ���\n\n");
                int nu;
                printf("������Ҫ��ӵ�λ��(��ǰԱ����:%d):\n",wk.length);
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
                printf("��������Ҫɾ���ڼ���Ա��:\n");
                scanf("%d", &nu);
                ListDelete_wk(&wk,nu,wo);
                break;
            }
        case 3:
            {
                int i;
                if(wk.length == 0)
                {
                    printf("����Ա����Ϣ\n");
                    return;
                }
                for(i = 0 ; i < wk.length ; i++)
                {
                   printf("\n\n\n");
                    printf("��%dλԱ�������Ϣ:\n",i);
                    printf("����:\n");
                    printf("%s\n",wk.w[i].name);
                    printf("����:\n");
                    printf("%ld\n",wk.w[i].number);
                    printf("ְ��:\n");
                    printf("%s\n",wk.w[i].position);
                    printf("------------\n");

                }


            }

        }
    }
    return 0;
}



