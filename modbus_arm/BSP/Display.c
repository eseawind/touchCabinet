#include "Display.h"
#include "wordlib.h"
#include "string.h"

void LCDPutChar(u8 x , u8 y , u8 *data);
void LCDPutCH(u8 x , u8 y , u8 *data);

u8 LCDbuf[8][128];//��ʾӳ�仺����

void GPIO_Configuration(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_GPIO_RS | RCC_GPIO_RW | RCC_GPIO_EN |
	                           RCC_GPIO_CS1 | RCC_GPIO_CS2 | RCC_GPIO_DATA , ENABLE);  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                 //����GPIO�Ĺ���״̬ 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                               //����GPIO���ٶ� 

	GPIO_InitStructure.GPIO_Pin=RS_PIN;
  GPIO_Init(GPIO_RS, &GPIO_InitStructure);
	                                 
	GPIO_InitStructure.GPIO_Pin=RW_PIN;
  GPIO_Init(GPIO_RW, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=EN_PIN;
  GPIO_Init(GPIO_EN, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=CS1_PIN;
  GPIO_Init(GPIO_CS1, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=CS2_PIN;
  GPIO_Init(GPIO_CS2, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin=DATA_PIN;
  GPIO_Init(GPIO_DATA, &GPIO_InitStructure); 
}

void Delay(u32 z) 
{ 
          u32 x,y;  
        for(x=z;x>0;x--) 
                for(y=27;y>0;y--); 
} 

void OutPutData(u8 data)	 //�������
{
	GPIO_DATA->BSRR = 0x00ff0000;	//�����Ӧλ
	GPIO_DATA->BSRR = (data);//  |0x00ff0000
}
 
void lcd_busy(void) 
{
		OutPutData(0xff);
    Delay(1);
}

/*дָ��*/
void WriteComm(u8 comm)
{
	lcd_busy();
	RSL;
	 RWL;
	OutPutData(comm);  //�е�ַ��ֵ��xȡֵ0----64
	ENH;
	 Delay(2);
	 ENL;
}

/*д����*/
void WriteData(u8 data)
{
	lcd_busy(); 
	RSH;
	RWL;
	OutPutData(data);  //��������
	ENH;
	 Delay(2);
	ENL;
	OutPutData(0xff);
}   

/*��λx0-127 y0-7*/
void set_xy(u8 x,u8 y) 
{
   if (x>=64)   
   	{
   		CS1H;
   		Delay(1);
   		CS2L;
   	} 
   else         
   	{
   		CS1L;
   		Delay(1);
   		CS2H;
   	}
	WriteComm(0x40|x);
    WriteComm(0xb8|y);
    OutPutData(0xff);  //�б���������������Ұ���
}

/*��ָ��λ��д����*/
void lw(u8 x,u8 y,u8 dd) 
{
	set_xy(x,y);
	WriteData(dd);
}

/*ˢ��һ����Ļ*/
void RefreshOneLine(u8 x_start , u8 x_end , u8 y)
{
	u8 *pLCD;
	set_xy(x_start,y*2);
	for(pLCD = &LCDbuf[y*2][x_start] ; pLCD<&LCDbuf[y*2][64];)
	{
		WriteData(*pLCD++);
	}
	set_xy(x_start,y*2+1);
	for(pLCD = &LCDbuf[y*2+1][x_start] ; pLCD<&LCDbuf[y*2+1][64];)
	{
		WriteData(*pLCD++);
	}

	set_xy(64,y*2);
	for(pLCD = &LCDbuf[y*2][64] ; pLCD<&LCDbuf[y*2][x_end];)
	{
		WriteData(*pLCD++);
	}
	set_xy(64,y*2+1);
	for(pLCD = &LCDbuf[y*2+1][64] ; pLCD<&LCDbuf[y*2+1][x_end];)
	{
		WriteData(*pLCD++);
	}
	memset(LCDbuf[y*2] , 0 ,128);
	memset(LCDbuf[y*2+1] , 0 ,128);
}

/*ˢ����Ļ*/
void RefreshLCD(void)
{
	u8 *pLCD;
	u8 i;

	for(i=0;i<8;i++)//ˢ�������
	{
		set_xy(0,i);
		for(pLCD = &LCDbuf[i][0] ; pLCD<&LCDbuf[i][64];)
		{
			WriteData(*pLCD++);
		}
	}

	for(i=0;i<8;i++) //ˢ���Ұ���
	{
		set_xy(64,i);
		for(pLCD = &LCDbuf[i][64] ; pLCD<=&LCDbuf[i][127];)
		{
			WriteData(*pLCD++);
		}
	}
	memset(LCDbuf , 0 , 1024);//ˢ������ӳ����
}

/*��ʾһ�У������ֿ⽫��Ӧ��ģ���뵽LCDbuf��
x0-127  y0-3
*/
void Display1Line(u8 x , u8 y ,const u8 *buf)
{
	u8 *tempbuf;
	u8 i=0;
	for(tempbuf = (u8 *)buf ; *tempbuf!='\0';)
	{
		if(*tempbuf < 0x80)	  
		{
			LCDPutChar(6*i+x , 2*y ,tempbuf);  //asc���ַ���
			tempbuf++;
			i++;
		}
		else
		{
			LCDPutCH(6*i+x , 2*y , tempbuf);//�����ַ���
			i+=2;
			tempbuf+=2;
		}
	}
}

/*
д��һ������
����asc���ַ��� , д��LCDbuf
x0-127 y 0-7
*/
void LCDPutChar(u8 x , u8 y , u8 *data)
{
  u8 i;
  const ASCWORD *pchar;
  pchar = asc_code;
  if(x>121 || y>7)
  {
  	return;
  }
  while(pchar->index[0] != '\0')
  {
  	 if(pchar->index[0] == *data)
	 {
	 	for(i=0;i<6;i++)
		{
			LCDbuf[y][x+i] = pchar->msk[2*i];
			LCDbuf[y+1][x+i] = pchar->msk[2*i+1];
		}
		return;
	 }
	 pchar++;
  }
}

/*
д��һ����������
���Һ������ַ��� , д��LCDbuf
x0-127 y 0-7
*/
void LCDPutCH(u8 x , u8 y , u8 *data)
{
  u8 i;
  const CHWORD *pch;
  pch = cha_code;
  if(x>115 || y>7)
  {
  	return;
  }
  while(pch->index[0] != '\0')
  {
  	 if(pch->index[0] == *data && pch->index[1] == *(data+1))
	 {
	 	for(i=0;i<12;i++)
		{
			LCDbuf[y][x+i] = pch->msk[2*i];
			LCDbuf[y+1][x+i] = pch->msk[2*i+1];
		}
		return;
	 }
	 pch++;
  }
}

void LCDinit(void) 
{ 
		GPIO_Configuration();

		ENL;	RSL;  RWL;
		CS1H;	CS2H;		
		CS1L;	CS2H;		
		RSL;	RWL;		
		OutPutData(0x3f); //����ʾ
		ENH;	Delay(5);	 ENL;		
		CS1L; CS2H;		
		RSL;	RWL;		
		OutPutData(0xc0);//��ʾ����
		ENH;	Delay(5);	 ENL;
		CS1L;	CS2L;		
		CS1H; CS2L;		
		RSL;	RWL;		
		OutPutData(0x3f);
		ENH;	Delay(5);	 ENL;
		CS1H;	 CS2L;		
		RSL;	RWL;		
		OutPutData(0xc0);
		ENH; 	Delay(5);  ENL;		
		CS1L;	CS2L;		
//		clr_screen();
		CS1H;CS2H;//����
}
