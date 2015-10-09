#include "USART.h"

void USART1_Conf(u32 baudRate)
{
	USART_InitTypeDef USART_InitSturct;//���崮��1�ĳ�ʼ���ṹ��

	GPIO_InitTypeDef GPIO_InitStruct;//���崮�ڶ�Ӧ�ܽŵĽṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE);//�򿪴��ڹܽ�ʱ��
	//USART1_Tx_Pin Configure
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//��������ٶ�50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//���츴�����
	GPIO_Init(GPIOA , &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���
//USART1_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIOģʽ��������
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;//��������
  GPIO_Init(GPIOA, &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���

//USART1 Configure	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);//ʱ��ʹ��
	USART_InitSturct.USART_BaudRate = baudRate;//������38400
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//���ݿ��8λ
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitSturct.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܷ��������
	USART_Init(USART1 , &USART_InitSturct);//����ʼ���õĽṹ��װ��Ĵ���
	USART_ClearFlag(USART1 , USART_FLAG_TC);
	//USART1_INT Configure
//	USART_ITConfig(USART1 , USART_IT_RXNE , ENABLE);//ʹ�ܽ����ж�
//	USART_ITConfig(USART1 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART1 , ENABLE);//�򿪴���
}

void PutChar(u8 Data)
{
	USART_SendData(USART1 , Data);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ��������
}
void PutStr(uint8_t *str)//����һ���ַ���
{
	while(*str != '\0')
	{
		USART_SendData(USART1 , *str++);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ��������
	}
}

void PutNChar(u8 *buf , u16 size)
{
  u8 i;
	for(i=0;i<size;i++)
	{
		 USART_SendData(USART1 , buf[i]);
		 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ��������
	}
}

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
} 

