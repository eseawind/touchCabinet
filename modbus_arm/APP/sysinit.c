#include "includes.h"


#if OS_CRITICAL_METHOD == 3u                 /* Allocate storage for CPU status register               */
    OS_CPU_SR  cpu_sr = 0u;
#endif

/*IC��������������ͨ������IC_msgbuf������Ϣ*/
OS_EVENT *IC_box;
u8 IC_msgbuf[PC_MSG_SIZE];

/*���룬һ�����յ�����������,ͨ������barcode_msgbuf�����û���Ϣ*/
OS_EVENT *barcode_box;
char barcode_msgbuf[USER_MSG_SIZE];

/*modbus_rtu ���ݽ��պͷ��ͣ�һ�����յ����ݣ�ͨ������modbus_msgbox������Ϣ��������*/
OS_EVENT *modbus_box;
u8 modbus_msgbuf[MODBUS_MSG_SIZE];

/*����������Ϣ����������*/
OS_EVENT *open_box;//����������˿ں�����

/*��������ź�*/
OS_EVENT *door_semp;

/*��ջ������*/
OS_STK pc_task_stk[PC_TASK_STK_SIZE];
OS_STK openbox_task_stk[OPENBOX_TASK_STK_SIZE];

/*
���������¼�
*/
void CreatAllEvent(void)
{
	open_box = OSMboxCreate(0);
	door_semp = OSSemCreate(0);
	barcode_box = OSMboxCreate(0);
	IC_box = OSMboxCreate(0);
	modbus_box = OSMboxCreate(0);
}

/*
fuction:������������
*/
void CreatAllTask(void)
{
//	OSTaskCreate(pc_task,(void *)0,		  	
//	   &pc_task_stk[PC_TASK_STK_SIZE-1], PC_TASK_PRIO);
	OSTaskCreate(openbox_task,(void *)0,		  	
	   &openbox_task_stk[OPENBOX_TASK_STK_SIZE-1], OPENBOX_TASK_PRIO);
}

