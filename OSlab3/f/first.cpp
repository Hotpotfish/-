#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "first.h"
using namespace std;
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
	mm_init();

	for(i = 0; i < 30; i++) //ģ��30��
	{
		cout << "�� " << i + 1 << " ��" << endl;
		do
		{
			tmp = (rand() % 1024) + 1; //�������1024

			cout << "����ռ� " << tmp << " �ֽ�" << endl;

			p[j] = mm_request(tmp);
			if(p[j] != -1)
			{
				requestsize = requestsize+tmp;
				k = k + step;

				cout << "����ָ�� " << p[j] << endl;
				cout << endl;
				j++;
			}
			else
			{
				cout << "ʣ��ռ䲻�㣬����ʧ��" << endl;
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

		cout << "�ͷ�ָ�� " << p[tmp] << endl;

		p[tmp] = -1;

		//����Ϊ����ͳ��ָ��
		cout << endl;
		cout << "ƽ������ռ䣺" << (double)requestsize / (double)j << " �ֽ�" << endl;
		cout << "ƽ���ռ������ʣ�" << (double)requestsize/(double)65536 << endl;
		cout << "ƽ������������" << (double)k/(double)j << endl;
		cout << endl;
		if((i + 1) % 5 == 0)
		{
			system("pause");
		}
	}
}
