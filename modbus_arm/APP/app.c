#include "includes.h"

u8 err;

void Task_Start(void *p_arg)
{
	u8 *modbus_buf;	
	CreatAllEvent();
	CreatAllTask();
	init_MODBUS();
    while (1)
    {
	   modbus_buf = OSMboxPend(modbus_box , 0 , &err);	//���޵ȴ�
	   function_MODBUS(modbus_buf , send_buf); //���ݴ���ͷ���
	   memset(modbus_msgbuf , 0 , MODBUS_MSG_SIZE);//�建��
	   rec_num = 0;
	   rec_stat = PACK_START; //׼����һ�ν���
    }
}

/*�봥����ͨ�ŵ�����
void pc_task(void *p_arg)
{

}
*/
/*��������ѭ�����ָ��λ���Ƿ���Ҫ����*/
void openbox_task(void *p_arg)
{
 // BOX_MSG *box_msg = NULL;
  static int LED_count = 0;
  while(1)
  {
	if((1 == modbusAdd->send_comm_L) && (modbusAdd->station_num_L != 0))//�п���ָ�����
	{
//		unsigned char box_station_num;
		unsigned char box_port;
//		box_station_num = modbusAdd->station_num_L;
		box_port = modbusAdd->station_port_L-1;  //��ȡ���������Ϣ
		modbusAdd->send_comm_L = 0;//���㣬��ֹ�ظ�ָ��
		if(OPEN_STAT == UserOpenBox(box_port))
		{
			modbusAdd->back_comm_L = 1;//����ɹ�����
			modbusAdd->station_num_L = 0;			
		}
	}
	OSTimeDlyHMSM(0, 0, 0,10);	 //��ʱ10ms���һ��
	/*���е���˸*/
	LED_count++;
	if(LED_count  == 100)
	{
		LED1ON;
	}
	if(LED_count  == 200)
	{
		LED1OFF;
		LED_count = 0;
	}
  }
}

