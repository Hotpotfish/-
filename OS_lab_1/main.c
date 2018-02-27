#include <stdio.h>
#include <stdlib.h>
#define DNUM 12

char Idisk[DNUM][512];

void read_block(int i, char *p)   //���ڴ����
{
    p = Idisk[i][0];
}

void write_block(int i, char *p)//д���ڴ���
{
    Idisk[i][0] = p;
}

int read_from_file(char *file_name)  //���ļ����������Ϊ��ȡ�ļ���·��
{
    FILE *f = NULL;
    //  char ch;
    int i,j;

    f = fopen(file_name,"r");
    if(f == NULL)
    {
        return -1;
    }
    while(fgetc(f) != EOF)
    {
        if(j == 512)
        {
            i++;
            j = 0;

        }
        Idisk[i][j] = fgetc(f);
        // ch = fgetc(f);
    }
    return 0;
}

int  write_to_file(char *file_name)//д���ļ��������Ϊд��·��
{
    FILE *f = NULL;
    int i;
    f = fopen(file_name,"w");
    if(f == NULL)
    {
        return -1;
    }
    for(i = 0 ; i <DNUM ; i++)
    {
        fputs(Idisk[i],f);
    }
    return 0;
}

void create(char *filename)
{
    {
        FILE *f;
        f = fopen(filename, "w" );
        if( f != NULL )
        {
            printf( "%s has been created!\n", filename );
        }
        else
        {
            printf( "Cannot create %s\n", filename );
        }
        return f;
    }

}

int destroy(char *filename)
{
    if(remove(filename) == 0)
    {
        printf("%s is removed\n",filename);

    }
    else
    {
        printf("remove");
    }


}

int open(char *filename)
{

}







int main()
{

}
