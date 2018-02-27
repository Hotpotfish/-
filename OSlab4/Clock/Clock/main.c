#include <stdio.h>
#include <stdlib.h>

#define F 3
#define P 10
#define RS 1000



int reference_string[RS]; //= {3,4,2,6,4,3,7,4,3,6,3,4,8,4,6};;
int M[F]; //内存数组
int V[F];  //内存使用情况
int *pointer;
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
    //printf("M :");
    int i = 0;
    for(i = 0 ; i < F ; i++)
    {
        printf("%d ",M[i]);

    }
    printf("\n");

}
void print_V()
{
    printf("V :");
    int i;
    for(i = 0 ; i < F; i++)
    {
        printf("%d ",V[i]);
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

int Init_V()
{
    int i = 0;
    while(i < F)
    {
        V[i] = 0;
        i++;
    }
    return 0;
}

int Init_pointer()
{
    pointer = V;
    return 0;

}

int seek(int p)
{
    int i = 0;
    for(i = 0 ; i < F ; i++)
    {
        if(M[i] == p)
        {
            return i;
        }
    }
    return -1;
}

int is_visit()
{
    int i;
    for(i = 0 ; i < F ; i++)
    {
        V[i] = 0;
    }
    return 0;
}


int isfull()
{
    if(M[F - 1] != -1)
    {
        return 0; //满
    }
    return -1;
}

int Clock()
{
    int i;
    int n = 0;
    for(i = 0 ; i < RS ; i++)
    {
        printf("%d :",reference_string[i]);
        int isin_M = seek(reference_string[i]);
        if(isin_M == -1)  //未在内存中
        {
            count ++;
            printf("页面缺失\n");
            int j = n;  //遍历数组中的空位
            while(1)
            {

                if(V[j] == 0)
                {
                    V[j] = 1;
                    M[j] = reference_string[i];  //填入

                    n = (j+1) % F;   //更新指针的值
                    break;
                }
                if(V[j] == 1)
                {
                    V[j] = 0;
                }
                j = (j + 1) % F;

            }


        }
        else
        {
            V[isin_M] = 1;
            n =  (isin_M + 1) % F;
        }

        print_M();
    }
}



int main()
{

    Init_reference_string();

    Init_M();
    Clock();
    printf("%d\n",count);
    print_reference_string();
    return 0;


}
