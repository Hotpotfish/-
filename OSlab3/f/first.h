unsigned char mm[65536];
int step; //记录搜索步数
int BinToInt(unsigned char *s) //把char类型变成int
{
	int i;
	char tmp[4];
	int t;
	for(i = 0; i < 4; i++)
	{	tmp[3 - i] = s[i];	}
	memcpy(&t,tmp,4);
	return t;
}
void IntToBin(int s, unsigned char *t) //把int类型变成char
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
	IntToBin(-1, mm); //前向指针 置-1 放在数组的第一个位置
	IntToBin(65536, &mm[4]); //整个块大小，放在第四个位置
	IntToBin(-1, &mm[65536-4]); //后向指针 置-1 放在数组的倒数第四个位置
	return 0;
}

int mm_request(int n)
{	//四字节前向指针、四字节块大小、一字节状态、N字节可用内存、四字节后向指针
	int pointer = 0;
	step = 0;

	while((mm[pointer+8]==1)||((n+26)>=BinToInt(&mm[pointer+4]))) //pointer+4 表示块大小
	{
		//mm[pointer+8]==1 状态位是一，说明这一块已经被分配
		//n+26 申请的空间+管理开销
		pointer=BinToInt(&mm[pointer+BinToInt(&mm[pointer+4])-4]); //找到后向指针
		if(mm[pointer+8] != 1)
		{step++;//非空闲块不在链内，不计步数}
		if(pointer == -1)
		{
			return -1;
		}
	}
	mm[pointer + 8] = 1; //修改本块标志位
	IntToBin(pointer + 4 + 4 + 1 + n + 4, &mm[pointer + 9 + n]); //修改本块后向指针
	IntToBin(pointer, &mm[pointer + 4 + 4 + 1 + n + 4]); //修改后块前向指针
	IntToBin(BinToInt(&mm[pointer + 4]) - n - 13, &mm[pointer + 4 + 4 + 1 + n + 4 + 4]); //修改后块大小
	IntToBin(n + 13,&mm[pointer + 4]); //修改本块大小
	return pointer;
}
}

void mm_release(int p)
{
	int pre;
	int bac;
	pre = BinToInt(&mm[p]);
	bac = BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4]);
	mm[p + 8] = 0; //修改本块标志位
	if(BinToInt(&mm[bac+8]) == 0) //如果后块未使用
	{
		IntToBin(0,&mm[p+BinToInt(&mm[p + 4]) - 4]); //清空本块后向指针
		IntToBin(0,&mm[bac]); //清空后块前向指针
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
		IntToBin(BinToInt(&mm[pre + 4]) + BinToInt(&mm[p + 4]), &mm[pre + 4]); //修改前块大小
		IntToBin(pre, &mm[BinToInt(&mm[p + BinToInt(&mm[p + 4]) - 4])]); //修改后块前向指针
		IntToBin(0, &mm[p + 4]); //清空本块大小
		IntToBin(0, &mm[p]); //清空本块前向指针
	}

}
