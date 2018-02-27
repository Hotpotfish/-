#include <stdio.h>
#include <stdlib.h>

#define F 3  //�����ڴ�֡
#define P 10 //���
#define RS  1000 //���ô�


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



int isFull()  //�ж�ջ�Ƿ�����
{
    if(M[F - 1] != -1)
    {
       //printf("ջ��,����ջ��:");
        return 0; //��ʱջ��
    }
    return -1;  //ջδ��

}

int is_in_M(int n)
{
    int i;
    for(i = 0 ; i < F ; i++)
    {
        if(M[i] == n)
        {
            return 0; //��ʱ���ָ�����ջ��
        }

    }
    return -1; //����ջ��

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

    if(is_in_M(p) == -1) //�������������ջ��
    {
        count ++;
        if(isFull() == 0)
        {

            printf("ջ��,����ҳ:%d\n",M[F - 1]);
        }

        int i = 0;
        int tmp[F];
        for(i = 0 ; i < F ; i++)
        {
            tmp[i]  = M[i];
        }
        M[0] = p; //ջ��

        for(i = 1 ; i < F ; i++)
        {
            M[i] = tmp[i - 1];  //��λ
        }

    }
    else
    {
        int index = seek(p); //���ظ�������λ�õı��
        int tmp[F];     //�˶δ������˼���ǽ������ͬ������ǰ
        int j;
        tmp[0] = p;
        for(j = 1 ; j < F ; j++)
        {
            if(j < index + 1)  //δ����Ŵ�
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
