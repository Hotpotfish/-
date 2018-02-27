// Weijiniya.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define KEY   "guozhixiu"
#define KeyNum 9

int main(int argc, char* argv[])
{
	int choise;
	char text[100];
	char newKey[100];
	int key[10]={6,20,14,25,7,8,23,8,20};
	while(1){
		printf("(密钥为guozhixiu,内容不分大小写,加密/解密后的内容均以小写表示)\n");
		printf("1.加密\n");
		printf("2.解密\n");
		printf("0.退出\n");
		printf("请输入您的选项：\n");
		scanf("%d",&choise);
		fflush(stdin);
		switch(choise){
		case 1:
			printf("请输入您要加密的明文(仅限英文字符):\n");
			gets(text);
			printf("%s\n",text);
			Encode(text,key);
			continue;
		case 2:
			printf("请输入您要解密的密文(仅限英文字符):\n");
			scanf("%s",&text);
			Decode(text,key);
			continue;
		case 0:
			return 0;
		default:
			printf("您的输入有误，请重新输入！\n");
			continue;
		}
	}
	return 0;
}
//将A-Z以0-25编号
int *Number(char *texts,int s){
	int i;
	int *a = (int *)malloc(sizeof(int) * (s));
	for(i=0;i<s;i++){
		if(texts[i]>=65 && texts[i]<=90){//是大写字母
			a[i]=texts[i]-65;
		}
		else if(texts[i]>=97 && texts[i]<=122){
			a[i]=texts[i]-97;
		}
		else {
			printf("您输入的字符串中包含了除英文字母的其它字符,已默认删去\n");
			break;
		}
	}
	return a;
}
//去空格
char *DeleteSpace(char *texts){
	int s=strlen(texts);
	int i,j;
	for( i=0;i<s;i++){
		if(texts[i]==' '){
			for( j=i;j<s;j++){
			texts[j]=texts[j+1];//删除空格
			}
			s=s-1;
		}
	}
	return texts;
}
//将密钥重复至与输入的明文/密文长度一致
int *RepeatKey(int *texts,int *key,int s){
	int *newKey=(int*)malloc(sizeof(int)*s);
	int j=0;
	int m=s/9;//密钥重复的次数
	int n=s%9;//密钥的最后几位
	int i,k,l;
	for( i=0;i<m;i++){
		j=j+i*s;
		for( k=0;k<KeyNum;k++,j++){
			newKey[j]=key[k];
		}
	}
	for( l=0;l<n;l++,j++){
		newKey[j]=key[l];
	}
	return newKey;
}
//转化字符输出
void printOut(int *texts,int s){
	char *answer = (char *)malloc(sizeof(char)*s);
	int i;
	printf("%d\n",s);
	for( i=0;i<s;i++){
			answer[i]=texts[i]+97;
			printf("%c%d ",answer[i],texts[i]);
	}
	//printf("\n加密/解密后得到：%s\n",answer);
	int j;
	for(j = 0 ; j < s ; j++)
	{
		printf("%c",answer[j]);
	}
	printf("\n\n");
	free(answer);
}

//加密函数
void Encode(char *texts,int *key){
	int ciphertext[100];
	int ch;
	for(ch = 0 ; ch < 100 ; ch++)
	{
		ciphertext[ch] = 0;
	}
	texts=DeleteSpace(texts);//明文处理(去空格)
	printf("%s\n",texts);
	int s=strlen(texts);
	int *newTexts=Number(texts,s);//将明文编号
	int *newKey=RepeatKey(newTexts,key,s);//密钥处理
	int i;
	for( i=0;i<strlen(texts);i++){
		ciphertext[i]=newTexts[i]+newKey[i % KeyNum];
		if(ciphertext[i]>25){
			ciphertext[i]-=26;
		}
		else if(ciphertext[i]<0){
			ciphertext[i]+=26;
		}
	}
	printf("%d",s);
	printOut(ciphertext,s);
	return;
}

//解密函数
void Decode(char *texts,int *key){
	int plaintext[100];
	texts=DeleteSpace(texts);//密文处理(去括号)
	int s=strlen(texts);
	int *newTexts=Number(texts,s);//将密文编号
	int *newKey=RepeatKey(newTexts,key,s);//密钥处理
	int i;
	for( i=0;i<strlen(texts);i++){
		plaintext[i]=newTexts[i]-newKey[i %KeyNum];
		if(plaintext[i]<0){
			plaintext[i]+=26;
		}
		else if(plaintext[i]>25){
			plaintext[i]-=26;
		}
	}
	//printf("%d",s);
	printOut(plaintext,s);
	return;
}

