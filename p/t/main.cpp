#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include <queue>
#include <algorithm>
#include <stack>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;

struct node
{
	int id;
	int need;
	bool operator < (struct node tmp)const
	{
		return need < tmp.need;
	}

}que[4][50010];

int n,m;
int allo[4][50010];
int ava[4];
int outque[50010];//��¼ÿ�����̳����еĴ���
int p[4];

bool solve()
{
	int flag = 1;
	int i,j,k;
	int sum = 0;

	while(flag == 1)
	{
		flag = 0;
		for(i = 1; i <= m; i++) //�ӵ�һ�����п�ʼö��
		{
			for( ; p[i] <= n; p[i]++)
			{
				if(ava[i] < que[i][p[i]].need)
					break;

				flag = 1;
				outque[ que[i][p[i]].id ]++;
 				if(outque[ que[i][p[i]].id ] == m) //�����Ӵ�������mʱ��˵���ý��̿���ִ��
				{
					sum++;
					for(j = 1; j <= m; j++) //����vav[]��
						ava[j] += allo[j][ que[i][p[i]].id ];
				}
			}
		}
	}

	if(sum == n)
		return true;
	return false;
}

void debug()
{
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
			printf("i :%d need: %d ",que[i][j].id,que[i][j].need);
		printf("\n");
	}
}

int main()
{
	while(~scanf("%d %d",&n,&m))
	{
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= n; j++)
				scanf("%d",&allo[i][j]);

		for(int i = 1; i <= m; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				que[i][j].id = j;
				scanf("%d",&que[i][j].need); //�Ȱ�ÿ�����̶�Ӧ��m����Դ�Ž�����
			}
		}

		//debug();
		for(int i = 1; i <= m; i++)
		{
			scanf("%d",&ava[i]);
			p[i] = 1;
			sort(que[i]+1,que[i]+1+n); //��ÿ����Դ����������������
		}
		//debug();
		memset(outque,0,sizeof(outque));

		if(solve())
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}


