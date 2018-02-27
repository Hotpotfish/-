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

	//���ֽ�ǰ��ָ�롢���ֽڿ��С��һ�ֽ�״̬��N�ֽڿ����ڴ桢���ֽں���ָ��
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

	mm[pointer+8] = 1; //�޸ı����־λ
	IntToBin(pointer + 4 + 4 + 1 + n + 4, &mm[pointer + 9 + n]); //�޸ı������ָ��
	IntToBin(pointer, &mm[pointer + 4 + 4 + 1 + n + 4]); //�޸ĺ��ǰ��ָ��
	IntToBin(BinToInt(&mm[pointer + 4]) - n - 13, &mm[pointer + 4 + 4 + 1 + n + 4 + 4]); //�޸ĺ���С
	IntToBin(n + 13, &mm[pointer + 4]); //�޸ı����С
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
	mm[p + 8] = 0; //�޸ı����־λ
	if(BinToInt(&mm[bac + 8]) == 0) //������δʹ��
	{
		IntToBin(0, &mm[p + BinToInt(&mm[p + 4]) - 4]); //��ձ������ָ��
		IntToBin(0, &mm[bac]); //��պ��ǰ��ָ��
		IntToBin(BinToInt(&mm[p + 4]) + BinToInt(&mm[bac + 4]), &mm[p + 4]); //�޸ı����С

		if(BinToInt(&mm[bac + BinToInt(&mm[bac + 4]) - 4]) != -1) //�����鲻�����һ��
		{
			IntToBin(p, &mm[BinToInt(&mm[bac + BinToInt(&mm[bac + 4]) - 4])]); //�޸ĺ��ĺ��ǰ��ָ��
		}
		IntToBin(0, &mm[bac + 4]); //��պ���С
	}
	if(pre == -1)
	{
		return;
	}
	if(BinToInt(&mm[pre + 8]) == 0) //���ǰ��δʹ��
	{
		IntToBin(0, &mm[pre + BinToInt(&mm[pre + 4]) - 4]); //���ǰ�����ָ��
		IntToBin(0, &mm[p]); //��ձ���ǰ��ָ��
		IntToBin(BinToInt(&mm[pre + 4]) + BinToInt(&mm[p + 4]), &mm[pre + 4]); //�޸�ǰ���С
		IntToBin(pre, &mm[BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4])]); //�޸ĺ��ǰ��ָ��
		IntToBin(0, &mm[p + 4]); //��ձ����С

	}
}



int main()
{
	int i;
	int j = 0; //����ָ����
	int p[1000]; //���ڴ�ŷ������ָ��
	int tmp;
	int requestsize = 0; //ͳ������ռ�
	int k = 0; //ͳ����������
	srand((unsigned char)time(NULL));
	step = 0;
	next = 0;
	end = -1;
	mm_init();

	for(i = 0; i < 30; i++)//ģ��30��
	{
		cout << "���ǵ� " << i + 1 << " ��" << endl;
		do
		{
			tmp = (rand() % 1024) + 1; //�������1024
			cout << "����ռ� " << tmp << " �ֽ�" << endl;
			p[j] = mm_request(tmp);

			if(p[j] != -1)
			{
				requestsize = requestsize + tmp;
				k = k + step;

				cout << "����ָ�룺" << p[j] << endl;
				cout << endl;
				j++;
			}
			else
			{
				cout << "ʣ��ռ䲻�㣬����ʧ�ܡ�" << endl;
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

		cout << "�ͷ�ָ�룺" << p[tmp] << endl;
		p[tmp] = -1;

		//����Ϊ����ͳ��ָ��
		cout << endl;

		cout << "ƽ������ռ䣺" << (double)requestsize/(double)j << " �ֽ�" << endl;

		cout << "ƽ���ռ������ʣ�" << (double)requestsize/(double)65536 << endl;

		cout << "ƽ������������" << (double)k/(double)j << endl;

		cout << endl;

		if((i + 1) % 5 == 0)
		{
			system("pause");
		}
	}
}

