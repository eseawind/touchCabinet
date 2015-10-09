#ifndef __SYSINIT_H_
#define __SYSINIT_H_
#include  "ucos_ii.h"

#define USER_MSG_SIZE  25//�û���Ϣ����Ĵ�С�ݶ�Ϊ25
#define PC_MSG_SIZE  100
#define MODBUS_MSG_SIZE 100	

/*��λ��������������ͨ������pc_msgbuf������Ϣ*/
extern OS_EVENT *IC_box;
extern u8 IC_msgbuf[PC_MSG_SIZE];

/*���룬һ�����յ�����������,ͨ������barcode_msgbuf�����û���Ϣ*/
extern OS_EVENT *barcode_box;
extern char barcode_msgbuf[USER_MSG_SIZE];

/*modbus_rtu ���ݽ��պͷ��ͣ�һ�����յ����ݣ�ͨ������modbus_msgbox������Ϣ��������*/
extern OS_EVENT *modbus_box;
extern u8 modbus_msgbuf[MODBUS_MSG_SIZE];

/*����������Ϣ����������*/
extern OS_EVENT *open_box;//����������˿ں�����

/*��������ź�*/
extern OS_EVENT *door_semp;

/*��ջ������*/
extern OS_STK pc_task_stk[PC_TASK_STK_SIZE];
extern OS_STK openbox_task_stk[OPENBOX_TASK_STK_SIZE];

void CreatAllTask(void);
void CreatAllEvent(void);
#endif

