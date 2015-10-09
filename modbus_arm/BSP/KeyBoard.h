#ifndef __KEYBOARF_H
#define __KEYBOARF_H	

#include "stm32f10x.h"

#define GETIN   10
#define GETOUT  11 
#define KEYUP   12
#define KEYDOWN 13
#define CANCEL  14
#define ENTER   15

//�������4*4 IO�˿ڳ�ʼ����������������
void Key44Port_Init(void);
//�������4*4ɨ������а���ʱ����1�����򷵻�0
uint16_t Key44_Scan(void);
//��ȡ�������4*4�ļ�ֵ����
uint16_t GetKey44val(void);
u16 GetKeyValue(void);

#endif
