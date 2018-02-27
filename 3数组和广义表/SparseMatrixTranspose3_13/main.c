#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100  // �������Ԫ���������ֵΪ100

typedef struct Triple
{
    int i, j;
    int value;
}Triple;

typedef struct
{
    Triple data[MAXSIZE];    // ����Ԫ��Ԫ���
    int mu, nu, tu;    // ����������������ͷ���Ԫ����
} TSMatrix;        //  ϡ���������

void Transmat(TSMatrix M, TSMatrix *N)
{
    int col, q, p;
    N->mu=M.nu; N->nu=M.mu; N->tu=M.tu; //��ʼ��
    if (M.tu!=0)
    {
       q=0;
       for (col=0;col < M.nu; col++)    //��M����ת
        for (p = 0;p <= M.tu; p++)   // ��M��Ԫ���ɨ��һ��
            if (M.data[p].j == col)
            {
            //    N->data = (Triple)malloc(sizeof(Triple));
                N->data[q].i=M.data[p].j;
                N->data[q].j=M.data[p].i;
                N->data[q].value=M.data[p].value;
                q++;
            }
    }
    return;
}
int main()
{
    int j;
    TSMatrix before, after;
    before.tu = 4;
    before.mu = 9;  //9��
    before.nu = 9;   //9��
    before.data[0].i = 1;
    before.data[0].j = 3;
    before.data[0].value = 9;
    before.data[1].i = 2;
    before.data[1].j = 4;
    before.data[1].value = 1;
    before.data[2].i = 3;
    before.data[2].j = 2;
    before.data[2].value = 2;
    before.data[3].i = 4;
    before.data[3].j = 7;
    before.data[3].value = 3;
    printf("before:\n");
    for( j = 0 ; j < before.tu ; j++)
    {
        printf("��: %d ��: %d ֵ: %d\n", before.data[j].i,before.data[j].j,before.data[j].value);
    }
    Transmat(before,&after);
    printf("after:\n");
     for( j = 0 ; j < after.tu ; j++)
    {
        printf("��: %d ��: %d ֵ: %d\n", after.data[j].i,after.data[j].j,after.data[j].value);
    }
    return 0;
}
