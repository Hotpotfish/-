#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100  // 假设非零元个数的最大值为100

typedef struct Triple
{
    int i, j;
    int value;
}Triple;

typedef struct
{
    Triple data[MAXSIZE];    // 非零元三元组表
    int mu, nu, tu;    // 矩阵的行数、列数和非零元个数
} TSMatrix;        //  稀疏矩阵类型

void Transmat(TSMatrix M, TSMatrix *N)
{
    int col, q, p;
    N->mu=M.nu; N->nu=M.mu; N->tu=M.tu; //初始化
    if (M.tu!=0)
    {
       q=0;
       for (col=0;col < M.nu; col++)    //按M的列转
        for (p = 0;p <= M.tu; p++)   // 对M三元组表扫描一遍
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
    before.mu = 9;  //9行
    before.nu = 9;   //9列
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
        printf("行: %d 列: %d 值: %d\n", before.data[j].i,before.data[j].j,before.data[j].value);
    }
    Transmat(before,&after);
    printf("after:\n");
     for( j = 0 ; j < after.tu ; j++)
    {
        printf("行: %d 列: %d 值: %d\n", after.data[j].i,after.data[j].j,after.data[j].value);
    }
    return 0;
}
