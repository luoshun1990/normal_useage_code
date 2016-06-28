// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

enum 
{
	status_idle = 0,
	status_getTab,
	status_getNewLine
};

#define SYMBOL1 0x09
#define SYMBOL2 0x0A

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp1;
	FILE *fp2;
	char  temp;
	unsigned int i;
	unsigned int read_status = status_idle;
	unsigned char cnt = 0;
	fp1 = fopen("data.txt","r");
	fp2 = fopen("data_finale.txt","w");

	if(fp1 == NULL)
	{
		printf("11");
		system("PAUSE");
		return 0;
	}

	if(fp2 == NULL)
	{
		printf("2");
		system("PAUSE");
		return 0;
	}

	while(!feof(fp1))
	{
		temp = fgetc(fp1);
		//fputc(temp,fp2);
#if 1
		if(temp == SYMBOL1)
		{
			read_status = status_getTab;
			cnt = 0;
		}

		if(temp == SYMBOL2)
		{
			read_status = status_getNewLine;
		}

		if(read_status == status_getTab)
		{
			fputc(temp,fp2);
			if(temp!=SYMBOL1)
			{
				cnt++;
			}
		}
		else if(read_status == status_getNewLine)
		{
			if(cnt<=7)
			{
				for(i = 0;i<7-cnt;i++)//音标不足7的不足7位
				{
					fputc('\0',fp2);
				}
			}
			else
			{
				printf("get longer alpha,cnt is %d",cnt);
				cnt = 0;
			}
			read_status = status_idle;
			fputc(temp,fp2);
		}
		else
		{
			fputc(temp,fp2);
		}
#endif
	}

	fclose(fp1);
	fclose(fp2);
	system("PAUSE");
	return 0;
}

