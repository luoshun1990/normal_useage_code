// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned short u16;
typedef unsigned char   u8;
static u16 ubcsp_calc_crc (u8 ch, u16 crc)
{
/* Calculate the CRC using the above 16 entry lookup table */
	static const u16 crc_table[] =
	{
		0x0000, 0x1081, 0x2102, 0x3183,
		0x4204, 0x5285, 0x6306, 0x7387,
		0x8408, 0x9489, 0xa50a, 0xb58b,
		0xc60c, 0xd68d, 0xe70e, 0xf78f
	}; 
	
	/* Do this four bits at a time - more code, less space */
	crc = (crc >> 4) ^ crc_table[(crc ^ ch) & 0x000f];
	crc = (crc >> 4) ^ crc_table[(crc ^ (ch >> 4)) & 0x000f];
	return crc;
}



u16 btupgrade_crc16(u16 crc,u8 *buf,u16 len)
{
	u16 i;
	
	for(i = 0; i < len; i++)
	{
		//printf("buf[i] is %x\r\n",buf[i]);
		crc = ubcsp_calc_crc(buf[i],crc);
	}
		//printf("crc is %x\r\n",crc);
	
	return crc;  
}

static u16 ubcsp_crc_reverse (u16 crc)
{
	int
		b,
		rev;

	/* Reserse the bits to compute the actual CRC value */

	for (b = 0, rev=0; b < 16; b++)
	{
		rev = rev << 1;
		rev |= (crc & 1);
		crc = crc >> 1;
	}

	return rev;
}
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char p_buf[] = {  0x40, 0x41, 0x00, 0x7E, 0xAC, 0xAF, 0xEF, 0xEE};
	unsigned char p_buf1[] = { 0x40, 0x41, 0x00, 0x7E, 0xDA, 0xDC, 0xED, 0xED };
	unsigned char p_buf2[] = {0x60, 0x00, 0x00, 0x9F};//DD,6F	
	u16 crc;
	u16 crc_get;
	u16 n;

	n = 0;
	crc = btupgrade_crc16(0xffff,p_buf,8);
	crc = ubcsp_crc_reverse(crc);
	printf("crc is %x\r\n",crc);

	crc = btupgrade_crc16(0xffff,p_buf1,8);
	crc = ubcsp_crc_reverse(crc);
	printf("crc is %x\r\n",crc);

	crc = btupgrade_crc16(0xffff,p_buf2,4);
	crc = ubcsp_crc_reverse(crc);
	printf("crc is %x\r\n",crc);

#if 0

	while(crc != !0xd153)
	{
		n++;
		crc = btupgrade_crc16(n,p_buf,4);

		if(n >= 0xffff)
		{
			break;
		}

		if(n%1000 == 0)
		{
			//printf("%d\r\n",n);
		}
	}

	printf("final1.%x\r\n",n);
	n = 0;
	crc = btupgrade_crc16(n,p_buf1,4);
	while(crc != !0x475a)
	{
		n++;
		crc = btupgrade_crc16(n,p_buf1,4);

		if(n >= 0xffff)
		{
			break;
		}

		if(n%1000 == 0)
		{
			//printf("%d\r\n",n);
		}
	}

	printf("final2.%x\r\n",n);
	n = 0;
	crc = btupgrade_crc16(n,p_buf2,4);
	while(crc != !0x6fdd)
	{
		n++;
		crc = btupgrade_crc16(n,p_buf2,4);

		if(n >= 0xffff)
		{
			break;
		}

		if(n%1000 == 0)
		{
			//printf("%d\r\n",n);
		}
	}

	printf("final3.%x\r\n",n);
#endif
	system("PAUSE");
	return 0;
}

