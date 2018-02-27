#include <stdio.h>
#include <stdlib.h>

#define F 3  //物理内存帧
#define P 10 //标号
#define RS  1000 //引用串


int reference_string[RS];
int M[F];
int count;


void print_reference_string()
{
    int i = 0;
    for(i = 0 ; i < RS ; i++)
    {
        printf("%d ",reference_string[i]);

    }
    printf("\n");

}
void print_M()
{
    int i = 0;
    for(i = 0 ; i < F ; i++)
    {
        printf("%d ",M[i]);

    }
    printf("\n");

}


int Init_reference_string()
{
    int i = 0;
    int r = 0;
    while(i < RS )
    {
        r = rand();
        if(r >= 0 && r < P)
        {
            reference_string[i] = r;
            i++;
        }
    }
    return 0;
}


int Init_M()
{
    int i = 0;

    while(i < F )
    {
        M[i] = -1;
        i++;
    }
    return 0;

}



int isFull()  //判断栈是否已满
{
    if(M[F - 1] != -1)
    {
       //printf("栈满,舍弃栈底:");
        return 0; //此时栈满
    }
    return -1;  //栈未满

}

int is_in_M(int n)
{
    int i;
    for(i = 0 ; i < F ; i++)
    {
        if(M[i] == n)
        {
            return 0; //此时发现该数在栈中
        }

    }
    return -1; //不在栈中

}

int seek(int p)
{
    int i;
    for(i = 0 ; i < F ; i++)
    {
        if(M[i] == p)
        {
            return i;
        }
    }
    return -1;

}


int update_M(int p)
{
    print_M();

    if(is_in_M(p) == -1) //将插入的数不在栈中
    {
        count ++;
        if(isFull() == 0)
        {

            printf("栈满,舍弃页:%d\n",M[F - 1]);
        }

        int i = 0;
        int tmp[F];
        for(i = 0 ; i < F ; i++)
        {
            tmp[i]  = M[i];
        }
        M[0] = p; //栈顶

        for(i = 1 ; i < F ; i++)
        {
            M[i] = tmp[i - 1];  //移位
        }

    }
    else
    {
        int index = seek(p); //返回该数所在位置的编号
        int tmp[F];     //此段代码的意思就是将这个相同的数提前
        int j;
        tmp[0] = p;
        for(j = 1 ; j < F ; j++)
        {
            if(j < index + 1)  //未到标号处
            {
                tmp[j] = M[j - 1];
            }
            else
            {
                tmp[j] = M[j];
            }
        }
        for(j = 0 ; j < F ; j++)
        {
            M[j] = tmp[j];
        }
    }
    return 0;
}

void LRU()
{
    int i;
    for(i = 0 ; i < RS ; i++)
    {
        update_M(reference_string[i]);
    }

}


int main()
{
    Init_reference_string();
    Init_M();
    LRU();
    printf("%d\n",count);
}
