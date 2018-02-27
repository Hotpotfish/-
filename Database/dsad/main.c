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
		printf("(��ԿΪguozhixiu,���ݲ��ִ�Сд,����/���ܺ�����ݾ���Сд��ʾ)\n");
		printf("1.����\n");
		printf("2.����\n");
		printf("0.�˳�\n");
		printf("����������ѡ�\n");
		scanf("%d",&choise);
		fflush(stdin);
		switch(choise){
		case 1:
			printf("��������Ҫ���ܵ�����(����Ӣ���ַ�):\n");
			gets(text);
			printf("%s\n",text);
			Encode(text,key);
			continue;
		case 2:
			printf("��������Ҫ���ܵ�����(����Ӣ���ַ�):\n");
			scanf("%s",&text);
			Decode(text,key);
			continue;
		case 0:
			return 0;
		default:
			printf("���������������������룡\n");
			continue;
		}
	}
	return 0;
}
//��A-Z��0-25���
int *Number(char *texts,int s){
	int i;
	int *a = (int *)malloc(sizeof(int) * (s));
	for(i=0;i<s;i++){
		if(texts[i]>=65 && texts[i]<=90){//�Ǵ�д��ĸ
			a[i]=texts[i]-65;
		}
		else if(texts[i]>=97 && texts[i]<=122){
			a[i]=texts[i]-97;
		}
		else {
			printf("��������ַ����а����˳�Ӣ����ĸ�������ַ�,��Ĭ��ɾȥ\n");
			break;
		}
	}
	return a;
}
//ȥ�ո�
char *DeleteSpace(char *texts){
	int s=strlen(texts);
	int i,j;
	for( i=0;i<s;i++){
		if(texts[i]==' '){
			for( j=i;j<s;j++){
			texts[j]=texts[j+1];//ɾ���ո�
			}
			s=s-1;
		}
	}
	return texts;
}
//����Կ�ظ��������������/���ĳ���һ��
int *RepeatKey(int *texts,int *key,int s){
	int *newKey=(int*)malloc(sizeof(int)*s);
	int j=0;
	int m=s/9;//��Կ�ظ��Ĵ���
	int n=s%9;//��Կ�����λ
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
//ת���ַ����
void printOut(int *texts,int s){
	char *answer = (char *)malloc(sizeof(char)*s);
	int i;
	printf("%d\n",s);
	for( i=0;i<s;i++){
			answer[i]=texts[i]+97;
			printf("%c%d ",answer[i],texts[i]);
	}
	//printf("\n����/���ܺ�õ���%s\n",answer);
	int j;
	for(j = 0 ; j < s ; j++)
	{
		printf("%c",answer[j]);
	}
	printf("\n\n");
	free(answer);
}

//���ܺ���
void Encode(char *texts,int *key){
	int ciphertext[100];
	int ch;
	for(ch = 0 ; ch < 100 ; ch++)
	{
		ciphertext[ch] = 0;
	}
	texts=DeleteSpace(texts);//���Ĵ���(ȥ�ո�)
	printf("%s\n",texts);
	int s=strlen(texts);
	int *newTexts=Number(texts,s);//�����ı��
	int *newKey=RepeatKey(newTexts,key,s);//��Կ����
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

//���ܺ���
void Decode(char *texts,int *key){
	int plaintext[100];
	texts=DeleteSpace(texts);//���Ĵ���(ȥ����)
	int s=strlen(texts);
	int *newTexts=Number(texts,s);//�����ı��
	int *newKey=RepeatKey(newTexts,key,s);//��Կ����
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

