#include "includes.h"
#include "UART485.h"

//u8 pc_msgbuf[PC_MCU_PACK_LENGTH];
u8 recvflag = 1;//���ձ�־

/*��flash�ж�ȡ����IDֵ*/
static u8 ReadAdd()
{
	u8 station_num;
	CAB_MSG cab_msg;
	ReadCabinetMsg(&cab_msg);
	station_num = (cab_msg.cab_station_num[3]-'0')*100 + (cab_msg.cab_station_num[4]-'0')*10 + cab_msg.cab_station_num[5]-'0';
	return station_num;
}

void IC_GPRSINT(u8 data)
{
	static u8 count=0;
	if(recvflag == 1)
	{
		pc_msgbuf[count++] = data;

		if(count == 1)
		{
			if(pc_msgbuf[0] != RECV_HEAD1)
			{
				count = 0;
				return;			
			}
		}

		if(count == 2)//ÿ���������ַ����һ��
		{
			if((pc_msgbuf[0] != RECV_HEAD1) || (pc_msgbuf[1] != RECV_HEAD2))
			{
				count = 0;
				return;
			}
		}
	
		if(count == PC_MCU_PACK_LENGTH)
		{
			OSMboxPost(pc_box , pc_msgbuf);// ��������
			count = 0;
			recvflag = 0;//����һ֡���ݺ��ֹ����
		}
	}
}

/*
����֡���ݣ��ȼ���ţ��ټ��У����
*/
u8 CheckMsg(struct UART485_Com *UART485msg)
{
	u8 cabinet_add;
	u8 *check=0;
	u8 check_value=0;
	recvflag = 1;//���Խ���
	cabinet_add = ReadAdd();
	if(cabinet_add != UART485msg->addCode) //���Ӻ�ƥ��
	{
		return 0;
	}

	for(check = &(UART485msg->startCode[0]);
	       check < &(UART485msg->checkCode);check++)
	{
		check_value ^= *check;//���У��
	}
	if(check_value != UART485msg->checkCode) //У��ʧ��
	{
		return 0;
	}
	return 1;		
}

/*
�������ݵ���λ��
������comm������  box_num ���  comm_status ����״̬
*/
void SendPC(u8 comm , u8 box_num , u8 comm_status)
{
	u8 sendbuf[MCU_PC_PACK_LENGTH];
	u8 i;
	memset(sendbuf , 0 ,MCU_PC_PACK_LENGTH);
	sendbuf[0] = SEND_HEAD1;
	sendbuf[1] = SEND_HEAD2;
	sendbuf[2] = ReadAdd();
	sendbuf[3] = comm;
	sendbuf[4] = box_num;
	sendbuf[5] = comm_status;
	
	for(i=0;i<MCU_PC_PACK_LENGTH-1;i++)	//���У�λ
	{
		sendbuf[MCU_PC_PACK_LENGTH-1] ^= sendbuf[i];	
	}
	PutNChar(sendbuf , MCU_PC_PACK_LENGTH);//send to PC 	
}

/*���Գ���,����comm������  box_num ��� code ID����
����Ҫ���͵�����*/
void Test_PC_MCUdata(u8 comm , u8 box_num , u8 *code)
{
	u8 sendbuf[PC_MCU_PACK_LENGTH];
	u8 i;
	memset(sendbuf , 0 ,PC_MCU_PACK_LENGTH);
	sendbuf[0] = RECV_HEAD1;
	sendbuf[1] = RECV_HEAD2;
	sendbuf[2] = 1;
	sendbuf[3] = comm;
	sendbuf[4] = box_num;
	memcpy(&sendbuf[5] , code , 4);
	
	for(i=0;i<PC_MCU_PACK_LENGTH-1;i++)	//���У�λ
	{
		sendbuf[PC_MCU_PACK_LENGTH-1] ^= sendbuf[i];	
	}
	PutNChar(sendbuf , PC_MCU_PACK_LENGTH);//send to PC 
	PutNChar("\r\n" , 2);
}

/*
ע������
*/
void RegBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//��ȡ��ţ���1��������ƥ��

   ReadOneBoxMsg(&box_msg);//��ȡ�������������Ϣ

   box_msg.status = BOX_USED;
   memcpy(box_msg.user_id , UART485msg->IDcode , IC_CODE_LENTH);//����ID����

   WriteOneBoxMsg(&box_msg);//д����Ϣ
   SendPC(REGID , UART485msg->boxNum , IC_SUCCESS);
}

/*
ע������
*/
void LogoutBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//��ȡ��ţ���1��������ƥ��

   ReadOneBoxMsg(&box_msg);//��ȡ�������������Ϣ

   box_msg.status = BOX_IDLE;
   memset(box_msg.user_id , 0xff , IC_CODE_LENTH);//�ָ�Ĭ��

   WriteOneBoxMsg(&box_msg);//д����Ϣ
   SendPC(LOGOUTID , UART485msg->boxNum , IC_SUCCESS);
}

/*
��ѯĳ������״̬
*/
void CheckStatus(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//��ȡ��ţ���1��������ƥ��

   ReadOneBoxMsg(&box_msg);//��ȡ�������������Ϣ

   if(box_msg.status == BOX_USED)
   {
   	  SendPC(CHECK_STATUS , UART485msg->boxNum , IC_SUCCESS);
   }
   else 
   if(box_msg.status == BOX_IDLE)
   {
   	  SendPC(CHECK_STATUS , UART485msg->boxNum , IC_FAILE);
   }
}

/*
��ĳ������
*/
void PcOpenBox(struct UART485_Com *UART485msg)
{
   BOX_MSG box_msg;
   box_msg.station_num = UART485msg->boxNum - 1;//��ȡ��ţ���1��������ƥ��

   ReadOneBoxMsg(&box_msg);//��ȡ�������������Ϣ

	OpenOneBox(&box_msg);//����
	OSSemPend(door_semp , 0 , &err);//�ȴ������ź�
	if(ReadOneBox(&box_msg) == CLOSE_STAT)	//����δ��
	{
		SendPC(PCOPENBOX , UART485msg->boxNum , IC_FAILE);//����ʧ�����ظ���λ��
		return;
	}
	SendPC(PCOPENBOX , UART485msg->boxNum , IC_SUCCESS);//����ɹ����ظ���λ��
	return;	   	
}

/*�����û�ʹ�ü�¼*/
void IC_PCSendUserData(u8 box_num)
{
   BOX_MSG box_msg;
	struct UART485_Com UART485msg;
   box_msg.station_num = box_num;//��ȡ��ţ���1��������ƥ��
	UART485msg.boxNum = box_num+1;

   ReadOneBoxMsg(&box_msg);//��ȡ�������������Ϣ
	if(box_msg.status == BOX_USED)
   {
   	  SendPC(USER_DATA_BACK , UART485msg.boxNum , IC_SUCCESS);
   }
   else 
   if(box_msg.status == BOX_IDLE)
   {
   	  SendPC(USER_DATA_BACK , UART485msg.boxNum , IC_FAILE);
   }
}
