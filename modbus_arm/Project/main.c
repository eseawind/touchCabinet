/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    �����ص�LED1��LED2��LED3���Թ̶���Ƶ��������˸��Ƶ�ʿɵ�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/	

#include "includes.h"

static OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //����ջ


  
int main(void)
{ 
  	BSP_Init();	//�ײ�Ӳ����ʼ��
	OSInit();  //ϵͳ��ʼ��
	OSTaskCreate(Task_Start,(void *)0,
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);  //������������

	OSStart();
    return 0;
 }

/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/




