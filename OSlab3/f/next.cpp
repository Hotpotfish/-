#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "next.h"

using namespace std;
int BinToInt(unsigned char *s)
{
	int i;
	char tmp[4];
	int t;

	for(i = 0; i < 4; i++)
	{
		tmp[3 - i] = s[i];
	}

	memcpy(&t,tmp,4);

	return t;
}

void IntToBin(int s, unsigned char *t)
{
	int i;
	char tmp[4];
	memcpy(tmp,&s,4);

	for(i = 0; i < 4; i++)
	{
		t[i] = tmp[3 - i];
	}
}

int mm_init()
{
	memset(mm, 0, 65536);
	IntToBin(-1, mm);
	IntToBin(65536, &mm[4]);
	IntToBin(-1, &mm[65536-4]);

	return 0;
}

int mm_request(int n)
{

	//四字节前向指针、四字节块大小、一字节状态、N字节可用内存、四字节后向指针
	int pointer;
	step = 0;
	pointer = next;
	while(pointer != -1)
	{
		if((mm[pointer + 8] != 1) && ((n + 26) < BinToInt(&mm[pointer + 4])))
		{
			break;
		}
		pointer = BinToInt(&mm[pointer + BinToInt(&mm[pointer + 4]) - 4]);
		//step++;
		if(mm[pointer + 8] != 1)
		{
			step++;
		}
	}
	if(pointer == -1)
	{
		pointer = 0;

		while(pointer != end)
		{
			if((mm[pointer + 8] != 1) && ((n + 26) < BinToInt(&mm[pointer + 4])))
			{
				break;
			}
			pointer = BinToInt(&mm[pointer + BinToInt(&mm[pointer + 4]) - 4]);
			if(mm[pointer + 8] != 1)
			{
				step++;
			}
			//step++;
		}
	}
	if(pointer == end)
	{
		return -1;
	}

	mm[pointer+8] = 1; //修改本块标志位
	IntToBin(pointer + 4 + 4 + 1 + n + 4, &mm[pointer + 9 + n]); //修改本块后向指针
	IntToBin(pointer, &mm[pointer + 4 + 4 + 1 + n + 4]); //修改后块前向指针
	IntToBin(BinToInt(&mm[pointer + 4]) - n - 13, &mm[pointer + 4 + 4 + 1 + n + 4 + 4]); //修改后块大小
	IntToBin(n + 13, &mm[pointer + 4]); //修改本块大小
	end = pointer;
	next = pointer + 4 + 4 + 1 + n + 4;
	return pointer;
}

void mm_release(int p)
{
	int pre;
	int bac;
	pre = BinToInt(&mm[p]);
	bac = BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4]);
	mm[p + 8] = 0; //修改本块标志位
	if(BinToInt(&mm[bac + 8]) == 0) //如果后块未使用
	{
		IntToBin(0, &mm[p + BinToInt(&mm[p + 4]) - 4]); //清空本块后向指针
		IntToBin(0, &mm[bac]); //清空后块前向指针
		IntToBin(BinToInt(&mm[p + 4]) + BinToInt(&mm[bac + 4]), &mm[p + 4]); //修改本块大小

		if(BinToInt(&mm[bac + BinToInt(&mm[bac + 4]) - 4]) != -1) //如果后块不是最后一块
		{
			IntToBin(p, &mm[BinToInt(&mm[bac + BinToInt(&mm[bac + 4]) - 4])]); //修改后块的后块前向指针
		}
		IntToBin(0, &mm[bac + 4]); //清空后块大小
	}
	if(pre == -1)
	{
		return;
	}
	if(BinToInt(&mm[pre + 8]) == 0) //如果前块未使用
	{
		IntToBin(0, &mm[pre + BinToInt(&mm[pre + 4]) - 4]); //清空前块后向指针
		IntToBin(0, &mm[p]); //清空本块前向指针
		IntToBin(BinToInt(&mm[pre + 4]) + BinToInt(&mm[p + 4]), &mm[pre + 4]); //修改前块大小
		IntToBin(pre, &mm[BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4])]); //修改后块前向指针
		IntToBin(0, &mm[p + 4]); //清空本块大小

	}
}



int main()
{
	int i;
	int j = 0; //分配指针数
	int p[1000]; //用于存放分配出的指针
	int tmp;
	int requestsize = 0; //统计申请空间
	int k = 0; //统计搜索步数
	srand((unsigned char)time(NULL));
	step = 0;
	next = 0;
	end = -1;
	mm_init();

	for(i = 0; i < 30; i++)//模拟30步
	{
		cout << "这是第 " << i + 1 << " 步" << endl;
		do
		{
			tmp = (rand() % 1024) + 1; //最大申请1024
			cout << "申请空间 " << tmp << " 字节" << endl;
			p[j] = mm_request(tmp);

			if(p[j] != -1)
			{
				requestsize = requestsize + tmp;
				k = k + step;

				cout << "分配指针：" << p[j] << endl;
				cout << endl;
				j++;
			}
			else
			{
				cout << "剩余空间不足，分配失败。" << endl;
			}
		}
		while(p[j] != -1);

		tmp = (rand() % j);

		while(p[tmp] == -1)
		{
			tmp = rand() % j;
		}
		requestsize = requestsize - BinToInt(&mm[p[tmp] + 4]);
		mm_release(p[tmp]);

		cout << "释放指针：" << p[tmp] << endl;
		p[tmp] = -1;

		//以下为性能统计指标
		cout << endl;

		cout << "平均申请空间：" << (double)requestsize/(double)j << " 字节" << endl;

		cout << "平均空间利用率：" << (double)requestsize/(double)65536 << endl;

		cout << "平均搜索步数：" << (double)k/(double)j << endl;

		cout << endl;

		if((i + 1) % 5 == 0)
		{
			system("pause");
		}
	}
}

