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

typedef unsigned long DIZHI; // DIZHI�Ķ���

int mem_size = DEFAULT_MEM_SIZE;
int ma_algorithm;
int mem_index = 0;//next-fit�Ĳ�ѯָ��
int mem_used = 0;//�����ڴ�
int mem_total;//���ڴ�
int cnt = 0;//�ڴ����ʧ�ܴ���
float mem_use_ratio = 0;//�ڴ�������
int cmp_cnt = 0;//������ҷ����ܱȽϴ���

//�������з�����������ݽṹ
struct block
{
    int start_addr;//��ʼ��ַ
    int size;//������С
};

block free_table[MAXPARTITION];//���з����������������������±��ʾ
int freeNum=0; //��ǰ���з�������Ч���ȣ���ʼ��Ϊ0

block used_table[MAXPARTITION];//ռ�÷�����
int usedNum=0; //��ǰռ�÷�������Ч���ȣ���ʼ��Ϊ0

void show_usedTable()
{
    mem_used = 0;

    for(int i = 1;i < usedNum;i++)
    {
        mem_used += used_table[i].size;
    }
}

//�ڴ��ʼ��
void ChuShiHua (DIZHI KS_KYNC,DIZHI JS_KYNC)
{
    used_table[0]={0, KS_KYNC};
    usedNum=1;
    free_table[0]={KS_KYNC, JS_KYNC-KS_KYNC};
    freeNum=1;
    mem_total = JS_KYNC-KS_KYNC;
}

//�״���Ӧ
bool cmp_ff(block A,block B)
{
    return A.start_addr < B.start_addr;
}

//�����Ӧ
bool cmp_bf(block A,block B)
{
    return A.size < B.size;
}

//���Ӧ
bool cmp_wf(block A,block B)
{
    return A.size > B.size;
}

//�ڴ����
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
	// �������з��������޸�
	for(t = 0;t< freeNum;t++)
    {
        int i = (t+index)%freeNum;
        if(free_table[i].size >= DX)//�ҵ���һ�����ʵĿ��з���
        {
            used_table[usedNum] = {free_table[i].start_addr,DX};//��ռ�÷�����β׷��һ������
            usedNum++;
            if(free_table[i].size == DX)//ǡ����ȣ�ȫ�������ȥ
            {
                freeNum--;
                for(int j = i;j < freeNum;j++)//��free��ɾ���ñ���Һ����ı���ǰ��һ��
                {
                    free_table[j] = free_table[j+1];
                }
                mem_index = i;
            }else               // ���򣬸ı�free�иñ����size����ʼ��ַ
            {
                free_table[i].size = free_table[i].size - DX;
                free_table[i].start_addr = free_table[i].start_addr + DX;
                mem_index = i+1;
            }
            cmp_cnt = cmp_cnt+t+1;//��¼�Ƚϴ���
            return used_table[usedNum-1].start_addr;//�����׵�ַ
        }else if(ma_algorithm == 4)
            break;
    }
    //�����ڴ�������
    show_usedTable();
//    printf("�ڴ������ʣ�%f\n",(float)mem_used/mem_total);
    mem_use_ratio += (float)mem_used/mem_total;
    cnt++;

    cmp_cnt = cmp_cnt+t+1;//��¼�Ƚϴ���
    return NULL;
}

//�ڴ����
void HuiShouNC (DIZHI KSDZ)
{
    int flag = 0;
    int size;
    int befor = -1,after = -1;
    for(int i = 0;i < usedNum;i++)// ����ռ�÷�����ɾ������
    {
        if(KSDZ == used_table[i].start_addr)
        {
            size = used_table[i].size;
            usedNum--;
            for(int j = i;j<usedNum;j++)//ɾ������������ǰ��һλ����Ч��������1
                used_table[j] = used_table[j+1];
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("�ڴ��׵�ַ�����޷�����\n");
    }else
    {
        for(int i = 0;i < freeNum;i++)//���ҿ��з��������û��յķ����������ڷ����ϲ��󣬸��¿��з�����
        {
            if(free_table[i].start_addr + free_table[i].size == KSDZ)//��ǰһ����������
            {
                befor = i;
            }
            if(KSDZ + size == free_table[i].start_addr)//���һ����������
            {
                after = i;
            }
        }

        if(befor != -1 && after != -1)//��ǰ�����������
        {
            free_table[befor].size = free_table[befor].size + free_table[after].size + size;//�����������ϲ�
            freeNum--;
            for(int j = after;j < freeNum;j++)
                free_table[j] = free_table[j+1];
        }else if(befor != -1)//ֻ��ǰһ��������
        {
            free_table[befor].size = free_table[befor].size + size;//��ǰһ�������ϲ���ֻ���޸����С
        }else if(after != -1)//ֻ���һ��������
        {
            free_table[after].size = free_table[after].size + size;
            free_table[after].start_addr = KSDZ;
        }else//�����κο��з�������
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
        ChuShiHua(56*1024,256*1024);//��ʼ���ڴ�
        ma_algorithm = i;
        mem_used = 0;//�����ڴ�
        cnt = 0;//�ڴ����ʧ�ܴ���
        mem_use_ratio = 0;//�ڴ�������
        cmp_cnt = 0;
        total_cnt = 0;
        while(cnt <=10000)
        {
            ran = rand()%10;
            if(ran <7)//�����ڴ�
            {
                //ȡʱ������
                unsigned seed = chrono::system_clock::now().time_since_epoch().count();
                default_random_engine generator(seed);
                //��̬�ֲ�
                normal_distribution<double> distribution(20*1024,6*1024);

                int x = (int)distribution(generator);
                if(x <=0 ||x >=200*1024)
                    continue;
                ShenQingNC(x);
                total_cnt++;
            }
            else//�����ڴ�
            {
                if(usedNum == 1)
                    continue;
                int w = rand()%(usedNum-1)+1;
                HuiShouNC(used_table[w].start_addr);

            }
        }
        printf("�㷨%d��ƽ���ڴ�������Ϊ��%f\n",ma_algorithm,(float)mem_use_ratio/cnt);
        printf("�㷨%d��ƽ���Ƚϴ���Ϊ��%f\n",ma_algorithm,(float)cmp_cnt/total_cnt);
    }
    system("pause");
}
