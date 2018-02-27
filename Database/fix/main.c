
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
        //exit(1);   //������䲻�ɹ�
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
void PrintList(workerList *L){
	int i=0;
	for (;i<L->length;i++){
		//printf("%s\n",L->w[i].name);
		printf("%d : %s %d %s\n",i+1 ,L->w[i].name,L->w[i].number,L->w[i].position);
	//printf ("%d\n",i);
	}
}

int ListInsert_wk(workerList *L,int i,worker w)
{
    worker *p,*q;
    q = &(L->w[i - 1]);     //qָʾ�����λ��
    for(p = &(L->w[L->length - 1]) ; p >= q ; --p)
        *(p + 1) = *p;
    *q = w;
    ++L->length;
    printf("%s %d %s\n",w.name,w.number,w.position);
	printf("done!\n");
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
     //exit(1);
     printf("�б���չʧ��!\n")  ;
    }
    else{
        printf("�б���չ�ɹ�!\n\n\n");
    }
        L->listsize += LISTINCREMENT;
		return 0;
}

int main()
{

    workerList wl;
    InitList_wk(&wl);
	int i=1;
	//char ch;
    worker w;
    FILE *fp;
    fp = fopen("text.txt","a+");
    if(fp == NULL)
	{
		printf("this file is empty!!!\n");
		return 0;
	}
	while(fscanf(fp,"%s %d %s",w.name,&w.number,w.position)!=EOF)
	{

		ListInsert_wk(&wl,i,w);
		i++;

	}
    for(;;)
	{
		int sel;
		printf("Which fuction do you want ?\n");
		printf("1.Insert a worker.\n");
		printf("2.Delete a worker.\n");
		printf("3.print workerlist!\n");
		printf("4.exit.\n");
		scanf("%d",&sel);
		switch(sel)
		{
		case 1:
			{
				FILE *fp1;
				worker w1;
				int i;
				fp1 = fopen("text.txt","w");
				printf("please enter your worker's information !\n");
				printf("name :\n");
				scanf("%s",w1.name);
				fflush(stdin);
				printf("number :\n");
				scanf("%d",&w1.number);
				fflush(stdin);
				printf("postion :\n");
				scanf("%s",w1.position);
				fflush(stdin);
				ListInsert_wk(&wl,wl.length + 1,w1);
				PrintList(&wl);
				for(i = 0 ; i < wl.length ;i++)
				{
					printf("%d %s  %d  %s  \t\n",i ,wl.w[i].name,wl.w[i].number,wl.w[i].position);
					fprintf(fp1," %d %s  %d  %s", i ,wl.w[i].name,wl.w[i].number,wl.w[i].position);
				}
				fclose(fp1);
				break;
			}
		case 2:
			{
				FILE *fp1;
				int i;
				worker w1;
				int number = 0;
				fp1 = fopen("text.txt","w");
				printf("please enter the worker 's ���.\n");
				scanf("%d",&number);
				ListDelete_wk(&wl,number,w);
				for(i = 0 ; i < wl.length ;i++)
				{
					printf("%d %s  %d  %s  \t\n" ,i+1,wl.w[i].name,wl.w[i].number,wl.w[i].position);
					fprintf(fp1," %s  %d  %s" ,wl.w[i].name,wl.w[i].number,wl.w[i].position);
				}
				fclose(fp1);


				break;
			}
		case 3:
			{
				PrintList(&wl);
				break;
			}

		case 4:
			{
				return 0;
			}


		}
	}

	fclose(fp);


    return 0;
}

//���⣺�����ԭ�������ļ�������һ�����Բ�ʹ�����ܹ���������
//������:�޸�ԭ�д�������ݽṹʹ����и�����
//½������ѧ������м���һ���ַ������͵����ݼ��ᣬͬʱ�ļ�������һ����ڼ����ַ����Ķ��룬��֮��������ӡ������ͬ����Լ��뼮��Ĳ�����
//���մ�:ԭ�����ݵ����Լ��ýṹ����д��Ҫ�������ԵĻ����ڽṹ��������һ�����ԣ�����Ҫע������ı�ʾ��Χ����Ҫ�����
//������:ԭ�����ļ����ı��ļ������е�ÿ��Ԫ�����ļ��и�ռһ�У�Ԫ���е�����ֵ�Կո������ÿ���һ�����ԣ����ڴ���Ķ�д���������һ��������c����������������ʽ����������ĺ����ֱ�Ϊfscanf,fprintf ������ʵ�ֶ������Ե�������ȡ
//��ӯ�أ������ļ�����Ҫ����ѧ���ļ������ԣ�Ȼ�󽫴��������ݽṹ�ı䣬�ڶ�ȡ�ļ�ʱ����Ҫ�������ı��������ȥ��Ȼ����Ҫ���Ӵ������������ĺ�����
