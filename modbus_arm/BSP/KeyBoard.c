
#include "KeyBoard.h"


#define RCC_KEY44PORT		RCC_APB2Periph_GPIOG
#define KEY44PORT GPIOG    //	     4*4�������ӵ�IO�ڣ�GPIOA~GPIOE
#define KEY44LSB  GPIO_Pin_0// 4*4���̰�˳��ӵ�IO���ϣ����λ��Ӧ��һ��
#define KEY44LSBn 0			 //���λ��ӦIO���ź�
#define KEY44ROW  0x0f//(KEY44LSB+(KEY44LSB<<1)+(KEY44LSB<<2)+(KEY44LSB<<3))//4*4���̵�����
#define KEY44COL  (0x00f0<<(uint16_t)KEY44LSBn) 
//������������ʱ���� ms
void Key_delayms(u32 n)
{
	u32 i;
	while(n--)
	for(i=0;i<0x0f5f;i++);
}

//�������4*4 IO�˿ڳ�ʼ����������������
void Key44Port_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;//����GPIO��ģʽ���ýṹ�����
	RCC_APB2PeriphClockCmd(RCC_KEY44PORT , ENABLE);
  GPIO_InitStructure.GPIO_Pin = KEY44ROW;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��������ʽ��� 
  GPIO_Init(KEY44PORT, &GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = KEY44COL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //������������
  GPIO_Init(KEY44PORT, &GPIO_InitStructure); 

//	GPIO_ResetBits(KEY44PORT , KEY44ROW);
}
//�������4*4ɨ������а���ʱ����1�����򷵻�0
uint16_t Key44_Scan(void)
{
	KEY44PORT->ODR &= ~KEY44ROW;  //����ȫ����0
	if(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL)
	 	{
		  KEY44PORT->ODR |= KEY44ROW;//�а���ʱ������ȫ���øߵ�ƽ��׼��ɨ��
		  return (uint16_t)1;
		}
	 else
		return (uint16_t)0;
}
/*****************************************************************************
*��    �ƣ�GetKey44val()
*��    �ܣ���ȡ�������4*4�ļ�ֵ����
*��ڲ�������
*���ڲ�������ȡ���ļ�ֵ���Ѿ���ǰ�����ֵ����
*��ֵ�ֲ���0  1  2  3
*          4  5  6  7
*          8  9  10 11
*          9  10 11 12
*****************************************************************************/
uint16_t GetKey44val(void)
{
	uint16_t i,row,key,keyval;
	key=0;
	row=~KEY44LSB;
	for(i=0;i<4;i++)
	{
		KEY44PORT->ODR &= row;
		if(((KEY44PORT->IDR)& KEY44COL)!=KEY44COL)
		{
			Key_delayms(1);
			if(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL)
			{
			  key=((~((KEY44PORT->IDR)& KEY44COL))& KEY44COL)+((~row)& KEY44ROW);
			  break;
			}
		}
		KEY44PORT->ODR |= ~row;
		row=(row<<1)|(KEY44LSB);
	}
	KEY44PORT->ODR &= ~KEY44ROW;
	while(((KEY44PORT->IDR)&KEY44COL)!=KEY44COL);
	Key_delayms(5);
	switch((key>>KEY44LSBn))	   
	{	  //bit7~bit4:���ߣ�4�У�bit3~bit0:���ߣ�4��
		case 0x11: keyval=1; break;//��һ��
		case 0x21: keyval=4; break;
		case 0x41: keyval=7; break;
		case 0x81: keyval=GETIN; break;
		case 0x12: keyval=2; break;//�ڶ���
		case 0x22: keyval=5; break;
		case 0x42: keyval=8; break;
		case 0x82: keyval=0; break;
		case 0x14: keyval=3; break;//������
		case 0x24: keyval=6; break;
		case 0x44: keyval=9;break;
		case 0x84: keyval=GETOUT;break;
		case 0x18: keyval=KEYUP;break;//������
		case 0x28: keyval=CANCEL;break;
		case 0x48: keyval=ENTER;break;
		case 0x88: keyval=KEYDOWN;break;
		default:   keyval=16;break;
	}
	return keyval;
}

u16 GetKeyValue(void)
{
	u16 keyval = 16;
	KEY44PORT->ODR &= ~KEY44ROW;  //����ȫ����0
	if(((KEY44PORT->IDR)&KEY44COL) != KEY44COL)//��������Ƿ���0λ����
	{
		/*��⵽�а�����ʼ����ɨ��*/
		u16 i,key,row;
		row = ~KEY44LSB;
		for(i=0;i<4;i++)
		{
			 KEY44PORT->ODR |= KEY44ROW;//�а���ʱ������ȫ���øߵ�ƽ��׼��ɨ��		
			 KEY44PORT->ODR &= row;
			 
			 if(((KEY44PORT->IDR)&KEY44COL) != KEY44COL)
			 {
			 	key = ((~((KEY44PORT->IDR)& KEY44COL))& KEY44COL)+(~(KEY44PORT->ODR) & KEY44ROW);
				switch((key>>KEY44LSBn))	   
				{	  //bit7~bit4:���ߣ�4�У�bit3~bit0:���ߣ�4��
					case 0x11: keyval=1; break;//��һ��
					case 0x21: keyval=4; break;
					case 0x41: keyval=7; break;
					case 0x81: keyval=GETIN; break;
					case 0x12: keyval=2; break;//�ڶ���
					case 0x22: keyval=5; break;
					case 0x42: keyval=8; break;
					case 0x82: keyval=0; break;
					case 0x14: keyval=3; break;//������
					case 0x24: keyval=6; break;
					case 0x44: keyval=9;break;
					case 0x84: keyval=GETOUT;break;
					case 0x18: keyval=KEYUP;break;//������
					case 0x28: keyval=CANCEL;break;
					case 0x48: keyval=ENTER;break;
					case 0x88: keyval=KEYDOWN;break;
					default:   keyval=16;break;
				}
				break;
			 }
			KEY44PORT->ODR |= ~row;
		    row=(row<<1)|(KEY44LSB);
		}
	}
	return keyval;
}

