#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "first.h"
using namespace std;
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
	mm_init();

	for(i = 0; i < 30; i++) //模拟30步
	{
		cout << "第 " << i + 1 << " 步" << endl;
		do
		{
			tmp = (rand() % 1024) + 1; //最大申请1024

			cout << "申请空间 " << tmp << " 字节" << endl;

			p[j] = mm_request(tmp);
			if(p[j] != -1)
			{
				requestsize = requestsize+tmp;
				k = k + step;

				cout << "分配指针 " << p[j] << endl;
				cout << endl;
				j++;
			}
			else
			{
				cout << "剩余空间不足，分配失败" << endl;
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

		cout << "释放指针 " << p[tmp] << endl;

		p[tmp] = -1;

		//以下为性能统计指标
		cout << endl;
		cout << "平均申请空间：" << (double)requestsize / (double)j << " 字节" << endl;
		cout << "平均空间利用率：" << (double)requestsize/(double)65536 << endl;
		cout << "平均搜索步数：" << (double)k/(double)j << endl;
		cout << endl;
		if((i + 1) % 5 == 0)
		{
			system("pause");
		}
	}
}
