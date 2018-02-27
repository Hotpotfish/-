#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 6+1
typedef struct record
{
    int key;

} record;

typedef  struct SqList
{
    record r[MAXSIZE+1];   // r[0]闲置
    int length;                   // 顺序表长度
} SqList;                                      // 顺序表类型

void BiInsertionSort (SqList *L)    // 对顺序表 L 作折半插入排序
{
    int low, high;
    int m, i, j;
    for ( i=2; i<=L->length; ++i )
    {
        L->r[0] = L->r[i];      // 将 L.r[i] 暂存到 L.r[0]
        low = 1;
        high = i - 1;
        while(low <= high)
        {
            m = (low+high)/2;      // 折半
            if (L->r[0].key < L->r[m].key)
                high = m-1;        // 插入点在低半区
            else  low = m+1;        // 插入点在高半区
        }
        for ( j=i-1;  j>=high+1;  --j )
        {
            L->r[j+1] = L->r[j];
        }
        L->r[high+1] = L->r[0];   // 插入
    }

} // BInsertSort
void Bubblesort(SqList *L) //冒泡排序(从小到大)
{
    int i,j;
    int temp;
    for(i = 1 ; i < MAXSIZE-1 ; i++)
    {
        for(j = i+1 ; j < MAXSIZE ; j++)
        {
            if(L->r[i].key > L->r[j].key)
            {
                temp = L->r[j].key;
                L->r[j].key = L->r[i].key;
                L->r[i].key = temp;
            }
        }

    }

}

int Partition(SqList *L, int low, int high)
{
    int temp;
    L->r[0].key = L->r[low].key;
    temp = L->r[low].key;
    while (low<high)
    {
        while(low < high && L->r[high].key >= temp)
        {
            --high;
        }
        L->r[low].key = L->r[high].key; // 比枢轴小的交换到低端
        while (low<high && L->r[low].key <= temp)
            ++low;
        L->r[high].key = L->r[low].key; // 比枢轴大的交换到高端
    }
    L->r[low].key = L->r[0].key;
    return low;
}

void Qsort(SqList *L, int s, int t)  //快速排序
{

    int temp;
    if(s < t)
    {
        temp = Partition(L, s, t);
        Qsort(L, s, temp - 1);
        Qsort(L, temp + 1, t);
    }

}

int SelectMinKey(SqList *L, int i)
{
    int min;
    int number;
    min = 10000;
    int j;
    for(j = i ; j < MAXSIZE ; j++)
    {
        if(L->r[j].key < min)
        {
            min = L->r[j].key;
            number = j;
        }
    }
    return number;

}
void SelectSort(SqList *L, int n)
{
    int i, j;
    int temp;
    for(i = 1 ; i < n ; i++)
    {
        j = SelectMinKey(L,i);
        if(i != j)
        {
            temp = L->r[i].key;
            L->r[i].key = L->r[j].key;
            L->r[j].key = temp;
        }
    }

}

void HeapAdjust (SqList *L, int s, int m)// 大顶堆
{
    int rc;
    int j;
    rc = L->r[s].key;
    for ( j = 2*s ; j <=m ; j*=2 )    // j 初值指向左孩子
    {
        if(j < m  && L->r[j].key < L->r[j + 1].key)
        {
            j++;
        }
        if(rc >= L->r[j].key)
        {
            break;
        }
        L->r[s].key = L->r[j].key;
        s = j;
    }
    L->r[s].key = rc;
} // HeapAdjust

void HeapSort(SqList *L)
{
    int i;
    for(i = MAXSIZE / 2; i > 0 ; i--)
    {
        HeapAdjust(L,i,MAXSIZE);

    }
    for(i = MAXSIZE; i > 1 ; i--)
    {
        int temp;
        temp = L->r[1].key;
        L->r[i].key = L->r[1].key;
        L->r[1].key = temp;
        HeapAdjust(L, 1, i-1);
    }
}

/*void Merge(int arr[],int low,int mid,int high)
{
    int i=low,j=mid+1,p=0;
    int *newarr = (int *)malloc((high-low+1)*sizeof(int));//用来暂存排序好的数据
    if(!newarr)
    {
        printf("malloc error!\n");
        exit(1);
    }

    while(i<=mid && j<=high)     //以下过程很类似两个有序字符串合并成一个有序字符串
    {
        if(arr[i] < arr[j])
            newarr[p++] = arr[i++];
        else
            newarr[p++] = arr[j++];
    }

    while(i<=mid)
        newarr[p++] = arr[i++];
    while(j<=high)
        newarr[p++] = arr[j++];

    for(i=low,p=0; p<(high-low+1); i++,p++) //将结果复制到原数组当中
        arr[i] = newarr[p];
    free(newarr);
}*/

void mergeSort(int a[],int left,int right)
{
	int i;
	// 保证至少有两个元素
	if(left < right)
	{
		i = (left+right)/2;
		mergeSort(a,left,i);
		mergeSort(a,i+1,right);
		merge(a,left,right);
	}
}

void merge(int a[],int left,int right)
{
	int begin1 = left;
	int mid = (left+right)/2 ;
	int begin2 = mid+1;
	int k=0;
	int newArrayLen = right-left+1;
	int *b = (int*)malloc(newArrayLen*sizeof(int));
	while(begin1<=mid && begin2<=right)
	{
		if(a[begin1]<=a[begin2])
			b[k++] = a[begin1++];
		else
			b[k++] = a[begin2++];
	}
	while(begin1<=mid)
		b[k++] = a[begin1++];
	while(begin2<=right)
		b[k++] = a[begin2++];
	copyArray(b,a,newArrayLen,left);
	free(b);
}

/**
 * 复制数组
 * source:源数组
 * dest:目标数组
 * len:源数组长度
 * first:目标数组起始位置
 *
 */
void copyArray(int source[], int dest[],int len,int first)
{
	int i;
	int j=first;
	for(i=0;i<len;i++)
	{
		dest[j] = source[i];
		j++;
	}

}
void showArray(int Arr[], int len)
{
    int i;
    for(i = 0 ; i < len ; i++)
    {
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

void pirntfNumber(SqList L)
{
    int i;
    for(i = 1 ; i < MAXSIZE ; i++)
    {
        printf("%d ",L.r[i].key);
    }
    printf("\n");
}
int main()
{
    int i;
    SqList *sq;
    sq = (SqList *)malloc(sizeof(SqList));
    sq->length = MAXSIZE;
    sq->r[1].key = 18;
    sq->r[2].key = 12;
    sq->r[3].key = 10;
    sq->r[4].key = 12;
    sq->r[5].key = 30;
    sq->r[6].key = 16;
    printf("排序前:\n");
    pirntfNumber(*sq);
    BiInsertionSort(sq);
    printf("排序后:\n");
    pirntfNumber(*sq);
    sq->r[1].key = 65;
    sq->r[2].key = 97;
    sq->r[3].key = 76;
    sq->r[4].key = 13;
    sq->r[5].key = 27;
    sq->r[6].key = 49;
    printf("排序前:\n");
    pirntfNumber(*sq);
    Bubblesort(sq);
    printf("排序后:\n");
    pirntfNumber(*sq);
    sq->r[1].key = 18;
    sq->r[2].key = 12;
    sq->r[3].key = 10;
    sq->r[4].key = 12;
    sq->r[5].key = 30;
    sq->r[6].key = 16;
    printf("排序前:\n");
    pirntfNumber(*sq);
    Qsort(sq,1,6);
    printf("排序后:\n");
    pirntfNumber(*sq);
    sq->r[1].key = 65;
    sq->r[2].key = 97;
    sq->r[3].key = 76;
    sq->r[4].key = 13;
    sq->r[5].key = 27;
    sq->r[6].key = 49;
    printf("排序前:\n");
    pirntfNumber(*sq);
    SelectSort(sq,MAXSIZE);
    printf("排序后:\n");
    pirntfNumber(*sq);
    sq->r[1].key = 18;
    sq->r[2].key = 12;
    sq->r[3].key = 10;
    sq->r[4].key = 12;
    sq->r[5].key = 30;
    sq->r[6].key = 16;
    printf("排序前:\n");
    pirntfNumber(*sq);
   Qsort(sq,1,6);
    printf("排序后:\n");
    pirntfNumber(*sq);
    int a[] = {5, 18, 151, 138, 160, 63, 174, 169, 79, 200};
	int len = sizeof(a)/sizeof(int);
    printf("排序前:\n");
	showArray(a,len);
	mergeSort(a,0,len-1);
    printf("排序后:\n");
	showArray(a,len);







    return 0;
}
