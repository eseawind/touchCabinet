#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************�����������ȼ�*******************/
#define STARTUP_TASK_PRIO   0
#define USER_TASK_PRIO      3	//�û���Χģ��
#define KEYVALUE_TASK_PRIO  2	//��ֵ
#define OPENBOX_TASK_PRIO   4 //	����
#define TIME_TASK_PRIO      6	//ʱ��
#define PC_TASK_PRIO   	    1	  //��λ������
#define DISPLAY_TASK_PRIO	 5	//��ʾ����

/************����ջ��С����λΪ OS_STK ��************/
#define STARTUP_TASK_STK_SIZE   128 
#define USER_TASK_STK_SIZE      128	//�û�
#define KEYVALUE_TASK_STK_SIZE  128	//��ֵ
#define TIME_TASK_STK_SIZE      128	//ʱ��
#define PC_TASK_STK_SIZE        128	//��ӡ��
#define OPENBOX_TASK_STK_SIZE   128 //	ʱ�� 
#define DISPLAY_TASK_STK_SIZE   128//��ʾ

#endif

