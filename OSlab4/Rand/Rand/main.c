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

int Rand_p()
{
    int i;
    for(i = 0 ; i < RS ; i++)
    {
        printf("%d:\n",reference_string[i]);
        if(isfull() == -1)  //ÄÚ´æÎ´Âú
        {
            printf("Ò³ÃæÈ±Ê§\n");
            count ++;
            M[i] = reference_string[i];
        }
        else  //ÄÚ´æÂú
        {
            if(seek(reference_string[i]) != -1) //ÔÚÄÚ´æ ²»ÓÃÌæ»»
            {
                continue;
            }


            while(1)
            {
                int r = 0;
                r = rand();
                if(r >= 0 && r < F)
                {
                    printf("Ò³ÃæÈ±Ê§\n");
                    M[r] = reference_string[i];
                    count ++;

                    break;
                }
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
    print_reference_string();
    // print_reference_string();
    // print_M();
    Rand_p();
    printf("%d",count);
    // print_reference_string();
    //print_M();
    return 0;

}
