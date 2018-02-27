#include <stdio.h>
#include <stdlib.h>
#define L 20
#define B 512
#define k 3
/*0块存储位图  1到k-1块存储目录,则存储文件的磁盘块有L-k个*/

char ldisk[L][B];  //磁盘模型

int read_block(int i, char *p)
{
    int n;
    for(n = 0 ; n < B ; n++)
    {
        p = ldisk[i][n];
        p++;
    }
    return 0;

}

int write_block(int i, char *p)
{
    int n;
    for(n = 0 ; n < B ; n++)
    {
        ldisk[i][n] = *p;
        p++;
    }
    return 0;



}

int write_ldisk_to_File(char *path)  //ldisk写入文件
{
    FILE *fp;
    fp = fopen(path,"w");
    if(fp == NULL)
    {
        printf("文件不能打开，或者未存在\n");
        return -1;
    }
    int i,j;
    for(i = 0 ; i < L ; i++)
    {
        fprintf(fp,"%s",ldisk[i]);
    }
    fclose(fp);
    return 0;
}
int read_ldisk_from_File(char *path)
{
    FILE *fp;
    fp = fopen(path,"r");
    if(fp == NULL)
    {
        printf("文件不能打开，或者未存在\n");
        return -1;
    }
    int i,j;
    for(i = 0 ; i < L ; i++)
    {
        for(j = 0 ; j < B ; j++)
        {
            fscanf(fp,"%c",&ldisk[i][j]);
        }

    }
    fclose(fp);
    return 0;
}

int Init_ldisk()
{
    int i,j;
    for(i = 0 ; i < L ; i++)
    {
        for(j = 0 ; j < B ; j++)
        {
            ldisk[i][j] = '0';
        }
    }
    return 0;

}



int main()
{
    /*const char *path = "F:\\a.txt";
    //Init_ldisk();
    //write_ldisk_to_File(path);
    read_ldisk_from_File(path);
    return 0;*/
    char *p;
    char p1 = 'd';


}
