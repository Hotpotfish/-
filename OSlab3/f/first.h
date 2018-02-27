unsigned char mm[65536];
int step; //��¼��������
int BinToInt(unsigned char *s) //��char���ͱ��int
{
	int i;
	char tmp[4];
	int t;
	for(i = 0; i < 4; i++)
	{	tmp[3 - i] = s[i];	}
	memcpy(&t,tmp,4);
	return t;
}
void IntToBin(int s, unsigned char *t) //��int���ͱ��char
{
	int i;
	char tmp[4];
	memcpy(tmp,&s,4);

	for(i = 0; i < 4; i++)
	{t[i] = tmp[3 - i];	}
}

int mm_init()
{
	memset(mm, 0, 65536);
	IntToBin(-1, mm); //ǰ��ָ�� ��-1 ��������ĵ�һ��λ��
	IntToBin(65536, &mm[4]); //�������С�����ڵ��ĸ�λ��
	IntToBin(-1, &mm[65536-4]); //����ָ�� ��-1 ��������ĵ������ĸ�λ��
	return 0;
}

int mm_request(int n)
{	//���ֽ�ǰ��ָ�롢���ֽڿ��С��һ�ֽ�״̬��N�ֽڿ����ڴ桢���ֽں���ָ��
	int pointer = 0;
	step = 0;

	while((mm[pointer+8]==1)||((n+26)>=BinToInt(&mm[pointer+4]))) //pointer+4 ��ʾ���С
	{
		//mm[pointer+8]==1 ״̬λ��һ��˵����һ���Ѿ�������
		//n+26 ����Ŀռ�+������
		pointer=BinToInt(&mm[pointer+BinToInt(&mm[pointer+4])-4]); //�ҵ�����ָ��
		if(mm[pointer+8] != 1)
		{step++;//�ǿ��п鲻�����ڣ����Ʋ���}
		if(pointer == -1)
		{
			return -1;
		}
	}
	mm[pointer + 8] = 1; //�޸ı����־λ
	IntToBin(pointer + 4 + 4 + 1 + n + 4, &mm[pointer + 9 + n]); //�޸ı������ָ��
	IntToBin(pointer, &mm[pointer + 4 + 4 + 1 + n + 4]); //�޸ĺ��ǰ��ָ��
	IntToBin(BinToInt(&mm[pointer + 4]) - n - 13, &mm[pointer + 4 + 4 + 1 + n + 4 + 4]); //�޸ĺ���С
	IntToBin(n + 13,&mm[pointer + 4]); //�޸ı����С
	return pointer;
}
}

void mm_release(int p)
{
	int pre;
	int bac;
	pre = BinToInt(&mm[p]);
	bac = BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4]);
	mm[p + 8] = 0; //�޸ı����־λ
	if(BinToInt(&mm[bac+8]) == 0) //������δʹ��
	{
		IntToBin(0,&mm[p+BinToInt(&mm[p + 4]) - 4]); //��ձ������ָ��
		IntToBin(0,&mm[bac]); //��պ��ǰ��ָ��
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
		IntToBin(BinToInt(&mm[pre + 4]) + BinToInt(&mm[p + 4]), &mm[pre + 4]); //�޸�ǰ���С
		IntToBin(pre, &mm[BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4])]); //�޸ĺ��ǰ��ָ��
		IntToBin(0, &mm[p + 4]); //��ձ����С
		IntToBin(0, &mm[p]); //��ձ���ǰ��ָ��
	}

}
