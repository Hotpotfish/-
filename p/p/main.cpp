#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctime>
#include <algorithm>
#include <cmath>

//c++ 11
#include <random>
#include <chrono>
using namespace std;

#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0
#define MAXPARTITION 200
#define first_fit 1
#define next_fit 2
#define best_fit 3
#define worst_fit 4

typedef unsigned long DIZHI; // DIZHI的定义

int mem_size = DEFAULT_MEM_SIZE;
int ma_algorithm;
int mem_index = 0;//next-fit的查询指针
int mem_used = 0;//已用内存
int mem_total;//总内存
int cnt = 0;//内存分配失败次数
float mem_use_ratio = 0;//内存利用率
int cmp_cnt = 0;//分配查找分区总比较次数

//描述空闲分区表项的数据结构
struct block
{
    int start_addr;//起始地址
    int size;//分区大小
};

block free_table[MAXPARTITION];//空闲分区表，分区表的序号用数组下标表示
int freeNum=0; //当前空闲分区表有效长度，初始化为0

block used_table[MAXPARTITION];//占用分区表
int usedNum=0; //当前占用分区表有效长度，初始化为0

void show_usedTable()
{
    mem_used = 0;

    for(int i = 1;i < usedNum;i++)
    {
        mem_used += used_table[i].size;
    }
}

//内存初始化
void ChuShiHua (DIZHI KS_KYNC,DIZHI JS_KYNC)
{
    used_table[0]={0, KS_KYNC};
    usedNum=1;
    free_table[0]={KS_KYNC, JS_KYNC-KS_KYNC};
    freeNum=1;
    mem_total = JS_KYNC-KS_KYNC;
}

//首次适应
bool cmp_ff(block A,block B)
{
    return A.start_addr < B.start_addr;
}

//最佳适应
bool cmp_bf(block A,block B)
{
    return A.size < B.size;
}

//最坏适应
bool cmp_wf(block A,block B)
{
    return A.size > B.size;
}

//内存分配
DIZHI ShenQingNC(unsigned long DX)
{
    int index = 0;
    int t;
    switch(ma_algorithm)
    {
    case 1:
        sort(free_table,free_table+freeNum,cmp_ff);
        break;
    case 2:
        index = mem_index;
        sort(free_table,free_table+freeNum,cmp_ff);
        break;
    case 3:
        sort(free_table,free_table+freeNum,cmp_bf);
        break;
    case 4:
        sort(free_table,free_table+freeNum,cmp_wf);
        break;
    }
	// 搜索空闲分区表，并修改
	for(t = 0;t< freeNum;t++)
    {
        int i = (t+index)%freeNum;
        if(free_table[i].size >= DX)//找到了一个合适的空闲分区
        {
            used_table[usedNum] = {free_table[i].start_addr,DX};//在占用分区表尾追加一个表项
            usedNum++;
            if(free_table[i].size == DX)//恰好相等，全部分配出去
            {
                freeNum--;
                for(int j = i;j < freeNum;j++)//在free中删除该表项，且后续的表项前移一项
                {
                    free_table[j] = free_table[j+1];
                }
                mem_index = i;
            }else               // 否则，改变free中该表项的size和起始地址
            {
                free_table[i].size = free_table[i].size - DX;
                free_table[i].start_addr = free_table[i].start_addr + DX;
                mem_index = i+1;
            }
            cmp_cnt = cmp_cnt+t+1;//记录比较次数
            return used_table[usedNum-1].start_addr;//返回首地址
        }else if(ma_algorithm == 4)
            break;
    }
    //计算内存利用率
    show_usedTable();
//    printf("内存利用率：%f\n",(float)mem_used/mem_total);
    mem_use_ratio += (float)mem_used/mem_total;
    cnt++;

    cmp_cnt = cmp_cnt+t+1;//记录比较次数
    return NULL;
}

//内存回收
void HuiShouNC (DIZHI KSDZ)
{
    int flag = 0;
    int size;
    int befor = -1,after = -1;
    for(int i = 0;i < usedNum;i++)// 查找占用分区表，删除表项
    {
        if(KSDZ == used_table[i].start_addr)
        {
            size = used_table[i].size;
            usedNum--;
            for(int j = i;j<usedNum;j++)//删除该项，后面的项前移一位，有效表项数减1
                used_table[j] = used_table[j+1];
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("内存首地址错误！无法回收\n");
    }else
    {
        for(int i = 0;i < freeNum;i++)//查找空闲分区表，将该回收的分区与其相邻分区合并后，更新空闲分区表
        {
            if(free_table[i].start_addr + free_table[i].size == KSDZ)//与前一个分区相邻
            {
                befor = i;
            }
            if(KSDZ + size == free_table[i].start_addr)//与后一个分区相邻
            {
                after = i;
            }
        }

        if(befor != -1 && after != -1)//与前后分区都相邻
        {
            free_table[befor].size = free_table[befor].size + free_table[after].size + size;//将三个分区合并
            freeNum--;
            for(int j = after;j < freeNum;j++)
                free_table[j] = free_table[j+1];
        }else if(befor != -1)//只与前一分区相邻
        {
            free_table[befor].size = free_table[befor].size + size;//与前一个分区合并，只需修改其大小
        }else if(after != -1)//只与后一分区相邻
        {
            free_table[after].size = free_table[after].size + size;
            free_table[after].start_addr = KSDZ;
        }else//不与任何空闲分区相邻
        {
            free_table[freeNum] = {KSDZ,size};
            freeNum++;
        }
    }
}


int main()
{
    int ran;
    srand(time(NULL));
    int total_cnt;
    for(int i = 1;i<=4;i++)
    {
        ChuShiHua(56*1024,256*1024);//初始化内存
        ma_algorithm = i;
        mem_used = 0;//已用内存
        cnt = 0;//内存分配失败次数
        mem_use_ratio = 0;//内存利用率
        cmp_cnt = 0;
        total_cnt = 0;
        while(cnt <=10000)
        {
            ran = rand()%10;
            if(ran <7)//申请内存
            {
                //取时间种子
                unsigned seed = chrono::system_clock::now().time_since_epoch().count();
                default_random_engine generator(seed);
                //正态分布
                normal_distribution<double> distribution(20*1024,6*1024);

                int x = (int)distribution(generator);
                if(x <=0 ||x >=200*1024)
                    continue;
                ShenQingNC(x);
                total_cnt++;
            }
            else//回收内存
            {
                if(usedNum == 1)
                    continue;
                int w = rand()%(usedNum-1)+1;
                HuiShouNC(used_table[w].start_addr);

            }
        }
        printf("算法%d的平均内存利用率为：%f\n",ma_algorithm,(float)mem_use_ratio/cnt);
        printf("算法%d的平均比较次数为：%f\n",ma_algorithm,(float)cmp_cnt/total_cnt);
    }
    system("pause");
}
