#include <stdio.h>
#include <stdlib.h>

#define F 3
#define P 10
#define RS 1000


int reference_string[RS]; //= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
int M[F];
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

int Init_pointer()
{
    pointer = M;
    return 0;

}

int seek(int p)
{
    int i = 0;
    for(i = 0 ; i < F ; i++)
    {
        if(M[i] == p)
        {
            return 0;
        }
    }
    return -1;  //未在队列
}

int seek_rs(int rs,int p)
{
    int i;
    for(i = rs ; i < RS ; i++)
    {
        if(reference_string[i] == p) //找到该数
        {
            return (i - rs);
        }
    }
    return -1;
}

int isfull()
{
    if(M[F - 1] != -1)
    {
        return 0; //满
    }
    return -1;
}

int best()
{
    int i;
    int n = 0;
    for(i = 0 ; i < RS ; i++)
    {
        if(isfull() == -1) //若数组没满
        {

            if(seek(reference_string[i]) == -1)  //且没在内存中
            {
                printf("%d :缺页\n",reference_string[i]);
                count++;
                M[n] = reference_string[i]; //填入
                print_M();
                n++;
            }
        }
        else
        {
            if(seek(reference_string[i]) == -1) //没在内存中
            {
                printf("%d :缺页\n",reference_string[i]);
                count ++;
                int j ;
                int nu  = -1;
                int max = -999;
                for(j =  0 ; j < F ; j++)
                {
                    int c;
                    c = seek_rs(i + 1,M[j]);
                    if(c == -1)   //该数不会再出现
                    {
                        M[j] = reference_string[i]; //替换
                        print_M();
                        nu = -1;
                        break;
                    }
                    if(c > max)
                    {
                        max = c;
                        nu = j;
                    }

                }
                if(nu != -1)
                {
                    M[nu] = reference_string[i];
                    print_M();
                }

            }
            print_M();

        }

    }
    return 0;
}



int main()
{

    Init_reference_string();
    Init_M();
    Init_pointer();
    print_reference_string();
    // print_reference_string();
    // print_M();
    best();

    // print_reference_string();
    print_M();
    printf("%d\n",count);
    return 0;

}
