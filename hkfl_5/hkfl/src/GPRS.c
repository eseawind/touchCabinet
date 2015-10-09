/*����Э�鴦���ļ�*/

#include "box_info.h"
#include "GPRS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
function:���ݷ�װ
input: sendbuf,��Ҫ����װ�ķ��Ͱ� ��cab_num���ӱ�ţ�typeָ������ databuf ��Ҫ��װ������ data_len ���ݳ���
output:��װ������ݳ���
*/
int package_send_pack(unsigned char *sendbuf , unsigned char *cab_num ,char type , unsigned char *databuf , int data_len)
{
	//int pack_len;//������
	int i;
	/*��Ӱ�ͷ*/
	sendbuf[0] = 0xa5;
	sendbuf[1] = 0xa5;
	sendbuf[2] = (data_len+8)>>8;
	sendbuf[3] = (data_len+8)%256;//ָ���
	memcpy(&sendbuf[4] , cab_num , 6);//���ӱ��
	sendbuf[10] = type;//ָ������
	memcpy(&sendbuf[11] , databuf , data_len);
	sendbuf[11+data_len] = 0;
	for(i=4;i<11+data_len;i++)//У��ֵ
	{
		sendbuf[11+data_len] += sendbuf[i];
	}
	sendbuf[12+data_len] = 0x5a;
	sendbuf[13+data_len] = 0x5a;
	return 14+data_len;
}

/*function:�漰�û����������ݲ��ִ������
input: data_buf ��Ҫ�����buf flag��־�����ݾ���ָ��᲻ͬ  box_info ����������ݰ� 
output: ���ݰ�����
*/
int package_user_data_pack(unsigned char *data_buf , unsigned char flag , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	int buf_len = sizeof(USER_INFO);

	memset(data_buf , 0xff , buf_len);//��Ĳ���Ĭ��Ϊ0xff
	
	user_msg = (USER_INFO *)data_buf;

	user_msg->flag = flag;
	memcpy(user_msg->pass_word,box_info->pass_word,USER_PASSWORD_LENGTH);
	memcpy(user_msg->send_id , box_info->send_id,SENDID_LENGTH);
	memcpy(user_msg->send_num , box_info->send_num,SEND_NUM_LENGTH);
	user_msg->station_num[0] = box_info->station_num/10 + '0';
	user_msg->station_num[1] = box_info->station_num%10 + '0';
	memcpy(user_msg->user_id,box_info->user_id,USERID_LENGTH);
	user_msg->status = box_info->status;
	user_msg->type = box_info->type;
	memcpy(user_msg->virtualnumber,box_info->virtualnumber,VIRTUAL_NUM_LENGTH);
	memcpy(user_msg->user_phnum,box_info->user_phnum,USER_PHNUM_LENGTH);

	return buf_len;
}
/*function:����ȷ�Ϻ���
input: data_buf ��ָ�����ݲ��֣�send_num �˻�Ա���ţ���Ҫ���
output: 1 ȷ�ϳɹ� 0 ȷ��ʧ��
*/
int confirm_sender(unsigned char *data_buf , unsigned char *send_num)
{
	SENDER_INFO *sender_msg;
	sender_msg = (SENDER_INFO *)data_buf;
	if(sender_msg->flag == SENDER_OK)
	{
		memcpy(send_num , sender_msg->send_id , SEND_NUM_LENGTH);
		return 1;
	}
	return 0;
	
}

/*function:����ʱ��̨�����û����ݽ���
input:data_buf ��ָ�����ݲ��� box_info ����������ݰ�
*/
int save_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;
	if(user_msg->flag != OPEN_OK)//��������
	{
		return 0;
	}
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	read_box_info_station_num(box_info->station_num , box_info);//��ȡ������Ϣ
	memcpy(box_info->pass_word,user_msg->pass_word,USER_PASSWORD_LENGTH);
	memcpy(box_info->send_id , user_msg->send_id,SENDID_LENGTH);
	memcpy(box_info->send_num ,user_msg ->send_num,SEND_NUM_LENGTH);
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	memcpy(box_info->user_id,user_msg->user_id,USERID_LENGTH);
	box_info->status = user_msg->status;
	box_info->type = user_msg->type;
	memcpy(box_info->virtualnumber,user_msg->virtualnumber,VIRTUAL_NUM_LENGTH);
	memcpy(box_info->user_phnum,user_msg->user_phnum,USER_PHNUM_LENGTH);	
	return 1;
}

/*
function:�û�ȡ��ʱ������������Ϣ��ȷ���Ƿ������Ϣ������û���Ϣ��ʽΪbox_info�����ϢȫΪff
input: data_buf ���������ص����ݰ�  box_info ��Ҫ������������Ϣ
output: 1 ����û���Ϣ 0 �����û���Ϣ
*/
int getout_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;
	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	read_box_info_station_num(box_info->station_num , box_info);//��ȡ������Ϣ
	if(user_msg->flag == CLEAR_OK)//��������û���Ϣ
	{
		box_info->status = BOX_IDLE;
		memset(box_info->pass_word , 0xff , USER_PASSWORD_LENGTH);
		memset(box_info->send_id , 0xff , SENDID_LENGTH);
		memset(box_info->send_num , 0xff , SENDID_LENGTH);
		memset(box_info->user_id , 0xff , USERID_LENGTH);
		memset(box_info->user_phnum , 0xff , USER_PHNUM_LENGTH);
		return 1;
	}else
	{return 0;}
}

/*
function:Զ�̶�ȡ�������û�ָ��ִ�к���,��ȡָ����������кŶ�ȡ��Ӧ��������Ϣ��д�뵽���ӽṹ���У�
         д��ָ����������ݰ���Ϣ���޸�������Ϣ�����洢
input: data_buf ���������ص����ݰ�  box_info ��Ҫ������������Ϣ
output: ���صı�־λ RW_OK �����ɹ� RW_ERR ����ʧ��
*/
char rw_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info)
{
	USER_INFO *user_msg;
	user_msg = (USER_INFO *)data_buf;

	box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
	if(0 == read_box_info_station_num(box_info->station_num , box_info))//��ȡ������Ϣ
	{
		return RW_ERR;
	}
	
	if(user_msg->flag == R_INFO)//��ȡ�û���Ϣ
	{
		return RW_OK;
	}
	if(user_msg->flag == W_INFO)//д���û���Ϣ
	{
		memcpy(box_info->pass_word,user_msg->pass_word,USER_PASSWORD_LENGTH);
		memcpy(box_info->send_id , user_msg->send_id,SENDID_LENGTH);
		memcpy(box_info->send_num ,user_msg ->send_num,SEND_NUM_LENGTH);
		box_info->station_num = (user_msg->station_num[0]-'0')*10 + user_msg->station_num[1]-'0';
		memcpy(box_info->user_id,user_msg->user_id,USERID_LENGTH);
		box_info->status = user_msg->status;
		box_info->type = user_msg->type;
		memcpy(box_info->virtualnumber,user_msg->virtualnumber,VIRTUAL_NUM_LENGTH);
		memcpy(box_info->user_phnum,user_msg->user_phnum,USER_PHNUM_LENGTH);	
		
		write_box_info(box_info);//�洢���û���Ϣ
		return RW_OK;
	}
	return RW_ERR;
}

/*
function:Զ�̶�ȡ�������û���Ϣָ��ִ�к���,��ȡָ�����ȡ������Ϣ��cab_msg��д��ָ�������,��Ҫ�ڽű��и���ϵͳ��Ϣ
input: data_buf ���������ص����ݰ�  cab_msg ��Ҫ�����Ĺ�����Ϣ���ڴ������ǰ�Ѿ���ȡ��ϵͳ��Ϣ
output: ���صı�־λ RW_OK �����ɹ� RW_ERR ����ʧ��
*/
char rw_cab_server_back(unsigned char *data_buf , CAB_INFO *cab_msg)
{
	CAB_INFO *cab_msgtemp;
	cab_msgtemp = (CAB_INFO *)data_buf;
	if(cab_msgtemp->flag == R_INFO)//��ȡ�û���Ϣ
	{
		cab_msg->flag = RW_OK;
		cab_msg->restart_flag = cab_msgtemp->restart_flag;
		return RW_OK;
	}
	if(cab_msgtemp->flag == W_INFO)//д���û���Ϣ
	{
		memcpy((char *)cab_msg , data_buf , sizeof(CAB_INFO));//�������ݰ���Ϣ
		cab_msg->flag = RW_OK;	
		return RW_OK;
	}
	cab_msg->flag = RW_ERR;
	return RW_ERR;
		
}

/*
function:Զ�̿��䣬������ָ���������Ϣ����
input: data_buf ���������ص����ݰ�  server_open_msg���ָ����صĽṹ��,box_info ������Ϣ
output: ���صı�־λ SERVER_OPEN_OK �����ɹ� SERVER_OPEN_ERR ����ʧ��
*/
char server_open_box_back(unsigned char *data_buf , SERVER_OPEN_INFO *server_open_msg , BOX_MSG *box_info)
{
	memcpy((unsigned char *)server_open_msg , data_buf , sizeof(SERVER_OPEN_INFO));

	if(0 == read_box_info_virtualnumber(server_open_msg->virtualnumber ,  box_info))
	{
		server_open_msg->flag = SERVER_OPEN_ERR;
		return SERVER_OPEN_ERR;
	}
	if(server_open_msg->flag == CLEAR_USER_INFO)//����û���Ϣ
	{
		box_info->status = BOX_IDLE;
		memset(box_info->pass_word , 0xff , USER_PASSWORD_LENGTH);
		memset(box_info->send_id , 0xff , SENDID_LENGTH);
		memset(box_info->send_num , 0xff , SENDID_LENGTH);
		memset(box_info->user_id , 0xff , USERID_LENGTH);
		memset(box_info->user_phnum , 0xff , USER_PHNUM_LENGTH);
		write_box_info(box_info);//�洢���û���Ϣ
		server_open_msg->flag = SERVER_OPEN_OK;
		return SERVER_OPEN_OK;		
	}
	if(server_open_msg->flag == NON_CLEAR_USER_INFO)
	{
		server_open_msg->flag = SERVER_OPEN_OK;
		return SERVER_OPEN_OK;
	}
	server_open_msg->flag = SERVER_OPEN_ERR;
	return SERVER_OPEN_ERR;
}
