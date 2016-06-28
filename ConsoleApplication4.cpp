// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "alpha_table.h"
#include <string.h>


#define CUR_HANDLE_NUM  100


typedef struct
{
	unsigned char alphabet[50];
	unsigned int addr;
}node_param_t;


node_param_t list_queue[1000];

unsigned int input_unicode[100] = 
{
	0
};

//二分查找
unsigned int getAlphaByUnicode(unsigned int key_code,unsigned char *p_alpha)
{
	#define F_PRINT_STEPNUM  0
	#define F_PRINT_RESULT   0

	unsigned int i;
	unsigned int start_index;
	unsigned int mid_index;
	unsigned int end_index;
	unsigned int count;
	count = 0;
	start_index = 0;
	end_index = ALPHA_TOTAL_NUM - 1;

	mid_index = (start_index + end_index)/2; 

	while(start_index!= end_index)
	{
			//从flash读取unicode
		if(key_code == alpha_table[mid_index].unicode)
		{
			//strcpy_s((char *)p_alpha,50,(char *)alpha_table[mid_index].p_alpha);
			//从flash读取音标
			memcpy(p_alpha,alpha_table[mid_index].p_alpha,50);
#if F_PRINT_RESULT
			printf("unicode : 0x%04x,alpha is:%s\r\n",key_code,p_alpha);
#endif
#if F_PRINT_STEPNUM
		printf("find success!step num is %d\r\n",count);
#endif
			return 1;
		}
		else if(key_code > alpha_table[mid_index].unicode)
		{
			count++;
			start_index = mid_index+1;
			mid_index = (start_index + end_index)/2; 
		}
		else
		{
			count++;
			end_index = mid_index - 1;
			mid_index = (start_index + end_index)/2; 
		}
	}

	if(key_code == alpha_table[mid_index].unicode)
	{

#if F_PRINT_STEPNUM
		printf("find success!step num is %d\r\n",count);
#endif
		memcpy(p_alpha,alpha_table[mid_index].p_alpha,50);

#if F_PRINT_RESULT
			printf("unicode : 0x%04x,alpha is:%s\r\n",key_code,p_alpha);
#endif
		return 1;//find success
	}
	else
	{
		return 0;//find fail
	}
}

int my_strcmp(unsigned char *p_str1,unsigned char *p_str2)
{
	while((*p_str1 == *p_str2)&&((*p_str1)!='\0')&&((*p_str2)!='\0'))
	{
		p_str1++;
		p_str2++;
	}
	return (*p_str1 - *p_str2);
}

void quick_sort(node_param_t *p_buf,unsigned int start_index,unsigned int end_index)
{
	unsigned int i;
	unsigned int j;
	node_param_t node_temp;
	i = start_index;
	j = end_index;

	while(i!=j)
	{
		//从后面开始找出找出第一个比自己小的
		while((my_strcmp(p_buf[i].alphabet,p_buf[j].alphabet)<0)&&(i!=j))
		{
			j--;
		}

		//交换数据
		if(i < j)
		{
			memcpy(node_temp.alphabet,p_buf[i].alphabet,50);
			node_temp.addr = p_buf[i].addr;

			memcpy(p_buf[i].alphabet,p_buf[j].alphabet,50);
			p_buf[i].addr = p_buf[j].addr;

			memcpy(p_buf[j].alphabet,node_temp.alphabet,50);
			p_buf[j].addr = node_temp.addr;
			i++;
		}

		//从前面向后面找出第一个比自己大的
		while((my_strcmp(p_buf[j].alphabet,p_buf[i].alphabet)>0)&&(i!=j))
		{
			i++;
		}

		//交换数据
		if(i < j)
		{
			memcpy(node_temp.alphabet,p_buf[i].alphabet,50);
			node_temp.addr = p_buf[i].addr;

			memcpy(p_buf[i].alphabet,p_buf[j].alphabet,50);
			p_buf[i].addr = p_buf[j].addr;

			memcpy(p_buf[j].alphabet,node_temp.alphabet,50);
			p_buf[j].addr = node_temp.addr;
			j--;
		}
	}

//	printf("cur start_index is %d\r\n",start_index);
	//printf("cur end_index is %d\r\n",end_index);
	//printf("cur i is %d\r\n",i);
	if(i > start_index)
	{
		quick_sort(p_buf,start_index,i-1);
	}

	if(i < end_index)
	{
		quick_sort(p_buf,i+1,end_index);
	}

	return;
}

int getAddrByAlphaBet(unsigned char *p_alpha)
{
	unsigned int i;
	for(i = 0; i < CUR_HANDLE_NUM;i++)
	{
		if(my_strcmp(p_alpha,list_queue[i].alphabet) == 0)
		{
			printf("find success,addr is :%d\r\n",list_queue[i].addr);
			return 1;
		}
	}

	if(i == 100)
	{
		printf("fail!\r\n");
		return -1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	char input_buf[10];
	unsigned char p_exit[5] = "exit";

	//1,存好名字,ok

	//2，通过名字查找unicode,模拟,记录写入flash的地址,记录转换后的unicode的长度
	for(i = 0;i < CUR_HANDLE_NUM;i++)
	{
		input_unicode[i] = 0x4E19+i;
		//插入地址
		list_queue[i].addr = 1+i;
	}

	//3,通过unicode 查找音标,考虑最后转换后的unicode的长度来确定有几个音标
	for(i = 0;i < CUR_HANDLE_NUM;i++)
	{
		if(getAlphaByUnicode(input_unicode[i],list_queue[i].alphabet))
		{
	
			//printf("%s\r\n",list_queue[i].alphabet);
		}
	}

	printf("before sort!\r\n");
	for(i = 0;i < CUR_HANDLE_NUM;i++)
	{
		printf("%s\r\n",list_queue[i].alphabet);
	}

	//4,下载完成后，进行排序
	quick_sort(&list_queue[0],0,CUR_HANDLE_NUM-1);

	printf("after sort!\r\n");

	for(i = 0;i < CUR_HANDLE_NUM;i++)
	{
		printf("alphabet:%s, addr is:%d\r\n",list_queue[i].alphabet,list_queue[i].addr);
	}

	//printf("hello,world!\r\n");

	//模拟查找
	while(1)
	{
		printf("输入你想要查找的音标，输入'exit'退出：" );
		gets_s(input_buf);
		if(my_strcmp((unsigned char*)input_buf,p_exit) == 0)
		{
			break;
		}
		else
		{
			getAddrByAlphaBet((unsigned char*)input_buf);
		}
	}
	system("PAUSE");
	return 0;
}

