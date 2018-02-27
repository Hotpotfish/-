#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int accnt1 = 0;
int accnt2 = 0;
double begin=0,end=0,time=0;
HANDLE hMutex ;
int i=1;
DWORD WINAPI run( LPVOID p)
{

    int counter=0 ;
    int tmp1, tmp2, r;
    WaitForSingleObject(hMutex,INFINITE);
    begin=GetTickCount();
    do
    {
        tmp1 = accnt1;
        tmp2 = accnt2;
        r = rand();
        accnt1 = tmp1 + r;
        accnt2 = tmp2 - r;
        counter++;

    }
    while ( accnt1 + accnt2 == 0 &&counter<50000000);
    end=GetTickCount();
    time=end-begin;
    printf ("进程%d 用时 %lf \n", i,time);
    printf ("%d\n", counter);
    i++;
    ReleaseMutex(hMutex);
    counter =0;
}

int main(int argc, char *argv[])
{
    hMutex = CreateMutex(NULL,FALSE,NULL);
    CreateThread(NULL,0,run,NULL,0,NULL);
    CreateThread(NULL,0, run,NULL,0,NULL);


    system("PAUSE");
    return 0;
}
