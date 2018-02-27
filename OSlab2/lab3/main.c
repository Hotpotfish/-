#include <stdio.h>
#include <stdlib.h>

#define mem_size 200
#define dis_size 30

char mm[mem_size];
int mm_size[dis_size];
char *head[dis_size];
int nu;
int move;
int count1;


char *mm_request(int n)
{

    if(n < 0)
        return NULL;
    int count = 0;
    char *p = &mm[0];
    char *t = &mm[mem_size];

    while(count < n && p != t)
    {
        if(*p == '0')
        {
            count ++;

            p++;
        }
        else
        {
            count = 0;

            p++;
        }
        move++;//指针移动
    }
    if(count < n && p == t)
    {
        return NULL;
    }
    else
    {
        p = p - n;
        char *point;
        point = p;
        int i;
        for(i = 0 ; i < n ; i++)
        {
            *p = '1';

            p++;
        }

        return point;

    }


}

void mm_release(char * p)
{
    int i;
    for(i = 0 ; i < dis_size ; i++)
    {
        if(p == head[i]) //找到具体的块然后释放
        {
            int j;
            for(j = 0 ; j < mm_size[i] ; j++)
            {
                *p = '0';
                p++;
            }
            return;
        }
    }
    return;
}
void mm_init()
{
    int i = 0;
    for( i = 0 ; i < mem_size ; i++)
    {
        mm[i] = '0';
    }
}

void o_init()
{
    int i;
    count1 = 0;
    move = 0;
    for(i = 0 ; i < dis_size ; i++)
    {
        mm_size[i] = 0;
       // head[i] = '0';
    }
    nu = -1;
}

int dis_test()
{
    nu++;
    int r = 0;
    do
    {
        r = rand();
    }
    while(r <= 2 || r >= 15);
    mm_size[nu] = r;
    head[nu] = mm_request(mm_size[nu]);

    if(head[nu] == '0'||head[nu] == NULL)
    {
        printf("error!!内存未分配\n");
        nu--;
        return -1;
    }
    else
    {
        printf("number %d block dis, size = %d\n",nu,r);
        int i;
        for(i = 0 ; i < mem_size ; i++)
        {
            if(i %10 == 0)
                printf("\n");
            printf("%c",mm[i]);

        }
        printf("\n");
        count1 ++;
        return 0;

    }



}


void rel_test(int n)
{
    if(nu == -1)
    {
        printf("所有块已释放或者未分配!\n");
        return;
    }
    if(n >= dis_size)
    {
        printf("不存在该块!\n");
        return;

    }
    if(head[n] == '0' && mm_size[n] == 0)
    {
        printf("该块为空!\n");
        return;
    }
    mm_release(head[n]);
    int tmp;
    tmp = mm_size[n];
    mm_size[n] = 0; //维护列表
    printf("number %d block release ,size: %d",n,tmp);
    nu--;
    int i;
    for(i = 0 ; i < mem_size ; i++)
    {
        if(i %10 == 0)
            printf("\n");
        printf("%c",mm[i]);

    }
    printf("\n");


}



int main()
{
    mm_init();
    o_init();
    while(dis_test() != -1)
    {
        dis_test();
    }
    printf("内存为%d个单位 \n一共分配%d次\n 指针寻找了%d次\n每次分配，平均指针寻找%d次",mem_size,count1 , move,move/count1);
    int m = 0;
    int i = 0;

    for(m =  mem_size - 1; m >= 0 ; m--)
    {
        if(mm[m] == '1')
            continue;
            i++;

    }
    printf("空内存为:%d\n",i);


    /*
    int choose = 0;
    for(;;)
    {
        printf("choose an option\n");
        printf("1.distribute memory\n");
        printf("2.release memory\n");
        scanf("%d",&choose);
        switch(choose)
        {
        case 1:
            dis_test();
            break;
        case 2:
            printf("which block do you want to release\n");
            int block;
            scanf("%d",&block);
            rel_test(block);
            break;
        default:
            printf("wrong choose\n");
            break;
        }


    }*/

  //  distrib_test();
    //rel_test(0);
   // rel_test(0);



    /*  mm_init();
      char *p;
      p = mm_request(7);
      printf("%s\n\n\n",mm); */ //mm_request test
    /* mm_release(p,6);
     printf("%s\n",mm); */ //mm_request test


    return 0;
}
