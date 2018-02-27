#include <stdio.h>
#include <stdlib.h>

#define F 3
#define P 10
#define RS 1000


int reference_string[RS];
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
    return -1;
}

int isfull()
{
    if(M[F - 1] != -1)
    {
        return 0; //Âú
    }
    return -1;
}

int FIFO()
{
    int i;
    for(i = 0 ; i < RS ; i++)
    {
        printf("%d :",reference_string[i]);

        if(seek(reference_string[i]) == -1)  //È±Ò³
        {
            count ++;
            printf("Ò³ÃæÈ±Ê§\n",reference_string[i]);
            if(isfull() == -1)  //Î´Âú
            {

                *pointer = reference_string[i];
                pointer += 1;

            }
            else  //Âú
            {

                int j;
                for(j = 0 ; j < F - 1; j++)
                {
                    M[j] = M[j + 1];
                }
                M[F - 1] = reference_string[i];
            }


        }
        print_M();

    }
    return 0;
}



int main()
{

    Init_reference_string();
    Init_M();
    Init_pointer();
    // print_reference_string();
    // print_M();
    FIFO();
    printf("%d",count);
    // print_reference_string();
    //print_M();
    return 0;

}
