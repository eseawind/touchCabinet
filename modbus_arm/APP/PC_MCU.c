/*
���������ʽ
leading sign(2Byte) + Command length(2 Byte) + ID(6Byte)
 + command type(1Byte) + command data(n) + overflag(1Byte)

leading sign = 0xA5A5,�����ǰ����ʶ
overflag = 0x40
command length= 6(ID) +1(command type)+n (com mand data)+1(overflag)

*/
#include "PC_MCU.h"
#include "IC_PC_MCU.h"
#include "functionList.h"

#include "box_operate.h"
#include "BSP.h"
#include "UART485.h"
#include "sysinit.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*�жϽ��պ���*/
void PCInt(u8 data)
{
	static u8 Recvbegin = 0,count=0;
	static u16 length=0;
	pc_msgbuf[count++] = data;
	if(Recvbegin == 0)
	{
		if(count == 1 && pc_msgbuf[0] != HEAD1)//�ж�ͷ1
		{
			count = 0;
			return;
		}
	
		if(count == 2 && pc_msgbuf[1] != HEAD2)	//�ж�ͷ2 
		{
			count = 0;
			return;
		}
	
		if(count == 4) //���㳤��
		{
			length = ((u16)pc_msgbuf[2]<<8) + pc_msgbuf[3] + 4;
			if(length > PC_MSG_SIZE)
			{
				count = 0;
				return;				
			}
			Recvbegin = 1;
		}
	}

	if((count >= length) && (1 == Recvbegin))
	{
		OSMboxPost(pc_box , pc_msgbuf);// ��������
		PCIntDisable();
		Recvbegin = 0;
		count = 0;
	}
}

/*ȡ�ãɣĺ�*/
void GetCabID(u8 *buf)
{
	CAB_MSG cab_msg;
	ReadCabinetMsg(&cab_msg);
	memcpy(buf , cab_msg.cab_station_num , 6);	
}

/*���ݸ�ʽ��װ����������
input: send_data ��Ҫ���͵����� �� type ָ������ �����ݰ���С
*/
void ClosePack(u8 *send_data , u8 type , u16 size)
{
	u8 *sendBuf;
	HEAD_BLOCK *head_msg;
	sendBuf = malloc(size + sizeof(HEAD_BLOCK) + 10);//��ȡ�ڴ�
	head_msg = (HEAD_BLOCK *)sendBuf;//����ת��
	/*����ͷ*/
	head_msg->head1 = HEAD1;
	head_msg->head2 = HEAD2;
	/*���볤��*/
	head_msg->length[0] = (u8)((size + sizeof(HEAD_BLOCK) - 3)/256);
	head_msg->length[1] = (u8)((size + sizeof(HEAD_BLOCK) - 3)%256);
	/*����ID��*/
	GetCabID(head_msg->cabID);
	/*����ָ������*/
	head_msg->type = type;
	/*��������*/
	memcpy(sendBuf + sizeof(HEAD_BLOCK) , send_data , size);
	/*���������*/
	sendBuf[sizeof(HEAD_BLOCK) + size] = OVER_FLAG;

	/*��ʼ��������*/
	PutNChar(sendBuf , sizeof(HEAD_BLOCK) + size + 1);
	free(sendBuf); //�ͷ��ڴ�
}

/*���������жϽ��յ��İ��Ƿ���ȷ
��ȷ���� ָ������ ���� ����0
*/
u8 OpenPack(u8 *rec_buf)
{
	HEAD_BLOCK *head_msg;
	u16 length;
	u8 IDbuf[6];
	head_msg = (HEAD_BLOCK *)rec_buf;
	GetCabID(IDbuf);
	/*�ȽϹ���ID��*/
	if(0 != memcmp(IDbuf , head_msg->cabID , 6))
	{
		return 0;
	}

	/*��������*/
	length = (((u16)(head_msg->length[0]))<<8) + head_msg->length[1]+4;
	if(OVER_FLAG != rec_buf[length-1])
	{
		return 0;	
	}
	/*����ָ������*/
	return head_msg->type;
}

/*
�����û�����ָ��,����flash����Ӧ����Ϣ
input: ���ӱ��
*/
void PCSendUserData(u8 station_num)
{
	BOX_MSG box_msg;
	PACK_BLOCK pack_msg;

	memset((char *)&pack_msg , 0xff , sizeof(PACK_BLOCK));//��ȫ�����0xff����������������
	box_msg.station_num = station_num;
	ReadOneBoxMsg(&box_msg);
	/*д���������к�*/
	sprintf(pack_msg.station_num , "%02d" , station_num);
	/*д���������*/
	memcpy(pack_msg.virtualnumber , box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
	/*д��״̬*/
	pack_msg.status = box_msg.status;
	/*д�������*/
	memcpy(pack_msg.barcode , box_msg.send_id0 , SENDID_LENGTH);
	/*д��ͻ��ɣ�*/
	memcpy(pack_msg.userID , box_msg.user_id , USERID_LENGTH);
	/*д��ͻ�����*/
	memcpy(pack_msg.userPassWord , box_msg.pass_word , USER_PASSWORD_LENGTH);

	/*��װ����*/
	ClosePack((u8 *)(&pack_msg) , USER_DATA , sizeof(PACK_BLOCK));
}

/*
���յ��û����ݺ�Ĵ��� ������flash
����Э�飬��Ҫ�޸��û�����
*/
void PCRecvUserData(u8 *databuf)
{
	PACK_BLOCK *pack_msg;
	BOX_MSG box_msg;
	/*���������ݰ�ָ��ָ��buf������ȡ����Ϣ�����������ݰ����û���Ϣ�����뿪��*/
	pack_msg = (PACK_BLOCK *)databuf;
	box_msg.station_num = (pack_msg->station_num[0]-'0')*10 + pack_msg->station_num[1]-'0';
	ReadOneBoxMsg(&box_msg);
	/*ֻ�Է�����������޸�*/
	if(box_msg.status != BOX_USED)
	{
		return;
	}
	/*�޸Ŀͻ�ID*/	
	memcpy(box_msg.user_id , pack_msg->userID , USERID_LENGTH);
	/*�޸Ŀͻ�����*/
	memcpy(box_msg.pass_word , pack_msg->userPassWord , USER_PASSWORD_LENGTH);
	/*д��flash*/
	WriteOneBoxMsg(&box_msg);
}

/*
���յ�PC_COMM ����ָ���Ĵ���Ŀǰֻ����λ������ָ��
����֮��������û�����
*/
void PC_MCUComm(u8 *databuf)
{
	PACK_BLOCK *pack_msg;
	BOX_MSG box_msg;

	pack_msg = (PACK_BLOCK *)databuf;
	box_msg.station_num = (pack_msg->station_num[0]-'0')*10 + pack_msg->station_num[1]-'0';
	ReadOneBoxMsg(&box_msg);
	/*�ж��Ƿ���*/
	if(pack_msg->status == BOX_USED) 
	{
		/*�򿪶�Ӧ������*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			/*����ʧ��*/
			pack_msg->status = BOX_IDLE;
		}
		else								  //
		{  //����ɹ�						  //   3��31���޸ģ�����ɹ��󷵻� BOX_OK_PC
			pack_msg->status = BOX_OK_PC;	  //
		}									  //
		/*д�������*/
		memcpy(pack_msg->barcode , box_msg.send_id0 , SENDID_LENGTH);
		/*д��ͻ��ɣ�*/
		memcpy(pack_msg->userID , box_msg.user_id , USERID_LENGTH);
		/*д��ͻ�����*/
		memcpy(pack_msg->userPassWord , box_msg.pass_word , USER_PASSWORD_LENGTH);			
		/*��װ����*/
		ClosePack((u8 *)(pack_msg) , PC_COMM , sizeof(PACK_BLOCK));
		/*��ո���*/
		if(pack_msg->status == BOX_OK_PC)
		{
			box_msg.status = BOX_IDLE;
			pboxStatus[box_msg.station_num] = BOX_IDLE;
			WriteOneBoxMsg(&box_msg);

//			pfunBlock = mainFunBlock;
//			OSMboxPost(display_box , pfunBlock);// ��������,ˢ����ʾ
		}
	}
}


/*��λ����������ָ�һ�㲻��*/
void PCSysPowerOn(void)
{
  char *buf = "ON OK";
	/*��װ����*/
	ClosePack((u8 *)buf , POWER_ON , strlen(buf));
}

