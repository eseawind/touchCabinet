#include "dis_fuction.h"
#include "Display.h"
#include "string.h"
#include "box_operate.h"
//#include "wordlib.h"

#include "stdio.h"
extern u8 *pboxStatus;
extern u8 const noGood16[];
extern u8 const haveGood16[];

void Dis1LineMid(char *str , u8 y)
{
	u8 char_length , x_start;
	char_length = strlen(str);
	x_start = (128 - char_length*6)/2; //����е�λ��
	Display1Line(x_start , y ,(const u8 *)str);
}
/*
������ʾ
��Ի������ܺ�����������ʾ
*/
void DisplayFull(DIS_SING *pDisFull , u8 flag)
{
	Dis1LineMid(pDisFull->y1 , 0);
	Dis1LineMid(pDisFull->y2 , 1);
	if(flag != XINGNUM)
	{
	Dis1LineMid(pDisFull->y3 , 2);
	}
	else
	if(flag == XINGNUM)
	{
		u8 xing_count;
		u8 linebuf[LINE_LENGTH];

		memset(linebuf , 0 , LINE_LENGTH);
		xing_count = strlen(pDisFull->y3);
		memset(linebuf , '*' , xing_count);
		Dis1LineMid((char *)linebuf , 2);
	}
	Dis1LineMid(pDisFull->y4 , 3);
}

/*�˵�������ʾ*/
void DisplayMenu(FUN_BLOCK *phead ,FUN_BLOCK *ptail , FUN_BLOCK *pfunDisplay)
{
	u8 i;
	FUN_BLOCK *pLCDtemp;
	for(pLCDtemp = phead ,i=0; i<4 ; pLCDtemp = pLCDtemp->pnext_block)
	{
		if(pLCDtemp == pfunDisplay)
		{
			LCDPutChar(0 , i*2 ,"*");	//��ѡ�������������
		}
		Display1Line(LCD_XSTART , i++ ,(const u8 *)pLCDtemp->current_display);
		if(pLCDtemp == ptail)
		{
			break;
		}
	}	
}

void GetTimeStr(char *timebuf , struct rtc_time *systmtime)
{
	sprintf(timebuf , "%02d_%02d_%02d %02d:%02d" , systmtime->tm_year%100 , systmtime->tm_mon , 
	                               systmtime->tm_mday , systmtime->tm_hour , systmtime->tm_min);
}

/*ʱ����ʾ*/
void DisplayTime(struct rtc_time *systmtime)
{
	static int last_min = 255;
	char timeBuf[LINE_LENGTH];
	u8 length,x_start,x_end;
	memset(timeBuf , 0 , LINE_LENGTH);
	if(last_min == systmtime->tm_min)
	{
		return;
	}
	last_min = systmtime->tm_min;
	GetTimeStr(timeBuf , systmtime);
	/*������ʾ*/
//	Dis1LineMid(timeBuf , 1);
	length = strlen(timeBuf);
	x_start = (128 - length*6)/2; //����ʼλ��
	x_end = x_start + length*6;//����λ��
	Display1Line(x_start , 1 ,(const u8 *)timeBuf);
	/*ˢ��һ��*/
	RefreshOneLine(x_start , x_end, 1);
}

/*��ʾһ�����ӣ�һ������ռһ�У�8������
y 0-3   x 0-15*/
void displayOneBox16(u8 x,u8 y,u8 const *p)
{
	  u8 i;
   for (i=0;i<8;i++)
   {
     LCDbuf[y*2][x*8+i] = p[i];
   }

   for (i=0;i<8;i++)
   {
     LCDbuf[y*2+1][x*8+i] = p[i+8];                   //��ʾ�°벿��
   }
}

/*��������ʾ��
��ҪΪʱ����ʾ �����������ʾ*/
void MainDisplay(DIS_SING *pLCDAllTemp)
{
	u8 i=0,j=0,box_num=0;
    GetTimeStr(pLCDAllTemp->y2 , &systmtime);
	box_num = strlen((char *)pboxStatus);
	if(box_num <= 16)
	{
		for(i=0;i<4;i++)
		{
			pboxStatus[j++]!=BOX_IDLE ? displayOneBox16(0 , i , haveGood16) : displayOneBox16(0 , i , noGood16);
			pboxStatus[j++]!=BOX_IDLE ? displayOneBox16(1 , i , haveGood16) : displayOneBox16(1 , i , noGood16);
		
			pboxStatus[j++]!=BOX_IDLE ? displayOneBox16(14 , i , haveGood16) : displayOneBox16(14 , i , noGood16);
			pboxStatus[j++]!=BOX_IDLE ? displayOneBox16(15 , i , haveGood16) : displayOneBox16(15 , i , noGood16);
		}
	}
}





