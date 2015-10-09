/*
��Ҫʵ�ָ������ӵ���Ϣ��ȡ�ʹ洢�Լ�����������
*/

#include "includes.h"
#include "flash.h"
#include "CATi2c.h"

/*��ȡ����״̬
�������ӵ����к�
*/
u8 ReadOneBox(u8 station_port)
{
	u16 temp;
	u8 position , port;
	port = station_port;//�ҳ���Ӧ�Ķ˿�
	position = port/16;
	switch(position)
	{
	case 0:
	temp = ReadCATData(AddCATdoor);
	temp = ReadCATData(AddCATdoor);//�������
	temp = temp & (0x0001<<port);
	break;

	case 1:
	temp = EXT1_ReadCATData(EXT1_AddCATdoor1);
	temp = EXT1_ReadCATData(EXT1_AddCATdoor1);//�������
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 2:
	temp = EXT1_ReadCATData(EXT1_AddCATdoor2);
	temp = EXT1_ReadCATData(EXT1_AddCATdoor2);//�������
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 3:
	temp = EXT2_ReadCATData(EXT2_AddCATdoor1);
	temp = EXT2_ReadCATData(EXT2_AddCATdoor1);//�������
	temp = temp & (0x0001<<(port-position*16));
	break;

	case 4:
	temp = EXT2_ReadCATData(EXT2_AddCATdoor2);
	temp = EXT2_ReadCATData(EXT2_AddCATdoor2);//�������
	temp = temp & (0x0001<<(port-position*16));
	break;
	default : return 0;
	}
	if(temp != 0)
	{
		return CLOSE_STAT;//	 3��31���޸� ,��CLOSE_STAT��OPEN_STATλ�öԵ�
	}					  //
	else				  //
	{					  //
		return OPEN_STAT; //
	}
}

/*��ĳ�����ӣ����ڿ���������*/
void OpenOneDoor(u8 station_port)
{
	u8 boxPort;
	u16 temp;
	boxPort = station_port;
	if(boxPort<16)
	{
		temp = 0x0001<<boxPort;
		WriteCATData(AddCATlock,0x02,temp);//��ĳ������
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //��ʱ������
		WriteCATData(AddCATlock,0x02,0);//��ĳ������
	}
	if(boxPort>=16 && boxPort<32)
	{
		boxPort -= 16;
		temp = 0x0001<<boxPort;
		EXT1_WriteCATData(EXT1_AddCATlock1,0x02,temp);//��ĳ������
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //��ʱ������
		EXT1_WriteCATData(EXT1_AddCATlock1,0x02,0);//��ĳ������
	}
	if(boxPort>=32 && boxPort<48)
	{
		boxPort -= 32;
		temp = 0x0001<<boxPort;
		EXT1_WriteCATData(EXT1_AddCATlock2,0x02,temp);//��ĳ������
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //��ʱ������
		EXT1_WriteCATData(EXT1_AddCATlock2,0x02,0);//��ĳ������
	}
	if(boxPort>=48 && boxPort<64)
	{
		boxPort -= 48;
		temp = 0x0001<<boxPort;
		EXT2_WriteCATData(EXT2_AddCATlock1,0x02,temp);//��ĳ������
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //��ʱ������
		EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//��ĳ������
	}
	if(boxPort>=64 && boxPort<80)
	{
		boxPort -= 64;
		temp = 0x0001<<boxPort;
		EXT2_WriteCATData(EXT2_AddCATlock2,0x02,temp);//��ĳ������
		OSTimeDlyHMSM(0, 0, 0,OPEN_DOOR_TIME);	 //��ʱ������
		EXT2_WriteCATData(EXT2_AddCATlock2,0x02,0);//��ĳ������
	}
}

/*�û���ָ��������
���� OPEN_STAT �򿪳ɹ�
     CLOSE_STAT ��ʧ��
	 ��ӷֶ�εȴ������ϵͳ�����ٶ�
*/
u8 UserOpenBox(u8 station_port)
{
	u8 count_open_time = 10;//��10�εȴ�	WAIT_DOOR_TIME/
	OpenOneDoor(station_port);
	/*������Ϻ��ٵ�һ��ʱ��*/
	while(count_open_time--)
	{
		 if(OPEN_STAT == ReadOneBox(station_port))
		 {
		 	break;
		 }
		 OSTimeDlyHMSM(0, 0, 0,WAIT_DOOR_TIME/10);
	}
	
	if(CLOSE_STAT == ReadOneBox(station_port))
	{
		return CLOSE_STAT;
	}
	return OPEN_STAT;
}



