// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned int u32;

int insert_sort(unsigned int *p_buf,unsigned int cnt)
{
	unsigned int *p_tmp;
	unsigned int i,j,z;
	unsigned int tmp;
	for(i = 1; i<cnt; i++)
	{
		for(j = 0;j<i;j++)
		{
			if(p_buf[i] < p_buf[j])
			{
				tmp = p_buf[i];
				for(z = i;z>j;z--)
				{
					p_buf[z] = p_buf[z-1];
				}
				p_buf[j] = tmp;
				break;
			}
		}
	}
	return 0;
}

int mearge_sort(unsigned int *p_buf,unsigned int index_start,unsigned int index_end)
{
	u32 len;
	u32 index_middle;
	u32 tmp;
	u32 i,j,k;
	u32 *p_tmp;
	len = index_end - index_start+1;

	p_tmp = (unsigned int *)malloc(len*sizeof(unsigned int));

	k = 0;

	if(len > 2)
	{

		index_middle = index_start+len/2 - 1;
		mearge_sort(p_buf,index_start,index_middle);
		mearge_sort(p_buf,index_middle+1,index_end);
		//将两个排好序的队列合并为一个队列
		for(i = index_start,j=index_middle+1; i<=index_middle&&j<=index_end;)
		{
			if(p_buf[i] <= p_buf[j])
			{
				p_tmp[k] = p_buf[i];
				//printf("i is %d,p_tmp[%d] is %d\r\n",i,k,p_tmp[k]);
				i++;
				k++;
			}
			else
			{
				p_tmp[k] = p_buf[j];
				//printf("j is %d,p_tmp[%d] is %d\r\n",j,k,p_tmp[k]);
				j++;
				k++;
			}
		}

		while(i<=index_middle)
		{

			p_tmp[k] = p_buf[i];
			//printf("i is %d,p_tmp[%d] is %d\r\n",i,k,p_tmp[k]);
			i++;
			k++;
		}

		while(j<=index_end)
		{
			p_tmp[k] = p_buf[j];
				//printf("j is %d,p_tmp[%d] is %d\r\n",j,k,p_tmp[k]);
			j++;
			k++;
		}
		//(&p_buf[index_start],0,len);
		for(i = index_start,k=0;i<=index_end;i++,k++)
		{
			p_buf[i] = p_tmp[k];
			//printf("%2d\r\n",p_buf[i]);
		}

		//memcpy(&p_buf[index_start],&p_tmp[0],len);,这里有点问题


	}
	else
	{	

		if(2 == len)
		{
			if(p_buf[index_start] > p_buf[index_end])
			{
				tmp = p_buf[index_start];
				p_buf[index_start] = p_buf[index_end];
				p_buf[index_end] = tmp;
			}
		}
	}

	free(p_tmp);
	return 0;
}
void test()
{
	static unsigned char i = 0;
	i++;

	printf("%d",i);
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	for(i = 0;i<10;i++)
	{
		test();
	}
#if 0
	int i;
	unsigned int data_buf[] = {6,4,8,3,2,5,0,67,7,78};
	mearge_sort(data_buf,0,9);

	for(i = 0;i<10;i++)
	{
		printf("%2d\r\n",data_buf[i]);
	}

#endif
	system("PAUSE");
	return 0;
}

