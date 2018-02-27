
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
        //exit(1);   //如果分配不成功
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
    q = &(L->w[i - 1]);     //q指示插入的位置
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
     //exit(1);
     printf("列表扩展失败!\n")  ;
    }
    else{
        printf("列表扩展成功!\n\n\n");
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
				printf("please enter the worker 's 编号.\n");
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

//问题：如何在原有数据文件中增加一列属性并使程序能够正常运行
//王功举:修改原有代码的数据结构使其具有该属性
//陆瑶：在学生结点中加入一个字符串类型的数据籍贯，同时文件操作多一项对于籍贯字符串的读入，在之后的输出打印操作中同样需对加入籍贯的操作。
//熊艺纯:原有数据的属性集用结构体书写，要增添属性的话，在结构体中增添一个属性，并且要注意数组的表示范围，不要溢出。
//王传仁:原数据文件是文本文件，表中的每个元组在文件中各占一行，元组中的属性值以空格隔开，每添加一列属性，就在代码的读写函数中添加一个参数，c语言中用于向流格式化输入输出的函数分别为fscanf,fprintf ，可以实现对列属性的添加与读取
//王盈地：首先文件里面要新增学生的籍贯属性，然后将代码中数据结构改变，在读取文件时，需要将新增的变量储存进去，然后需要增加处理新增变量的函数。
