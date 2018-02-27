#include "stdio.h"

int Insert(int a[], int k)
{
    int key = k % 11;
    while(a[key] != 0)
        key++;
    a[key] = k;
    return key;
}

int Find(int a[], int k)
{
    int key = k % 11;
    while(a[key] != k)
        key++;
    if (a[key] == k)
        return key;
    return 11;
}

int main()
{
    int arr[11] = {0};
    for(int i = 0; i < 11; ++i)
    {
        int t;
        scanf("%d", &t);
        Insert(arr, t);
    }

    for(int i = 0; i < 11; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    int t;
    scanf("%d", &t);
    printf("%d", Find(arr, t));

}
