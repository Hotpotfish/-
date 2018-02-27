#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



static int accnt1 = 0;
static int accnt2 = 0;

DWORD WINAPI run(LPVOID p)
{
    HANDLE hMute = CreateMutex(NULL,FALSE,"po");
    WaitForSingleObject(hMute,INFINITE);
    int counter = 0;
    int temp1,temp2;
    int r;
    do
    {

        temp1 = accnt1;
        temp2 = accnt2;
        r = rand();
        accnt1 = temp1 + r;
        accnt2 = temp2 - r;
        counter ++;
    }while(accnt1 + accnt2 == 0);
    printf("%d\n",counter);
    ReleaseMutex(hMute);
}

DWORD WINAPI runp(LPVOID p)
{

    int counter = 0;
    int temp1,temp2;
    int r;
    do
    {

        temp1 = accnt1;
        temp2 = accnt2;
        r = rand();
        accnt1 = temp1 + r;
        accnt2 = temp2 - r;
        counter ++;
    }while(accnt1 + accnt2 == 0);
    printf("%d\n",counter);

}
DWORD WINAPI runq(LPVOID p)
{

    int counter = 0;
    int temp1,temp2;
    int r;
    do
    {

        temp1 = accnt1;
        temp2 = accnt2;
        r = rand();
        accnt1 = temp1 + r;
        accnt2 = temp2 - r;
        counter ++;
    }while(accnt1 + accnt2 == 0);
    printf("%d\n",counter);

}







int main()
{
    CreateThread(NULL,0,run,NULL,0,NULL);
    CreateThread(NULL,0,run,NULL,0,NULL);
    system("PAUSE");
    return 0;

}
