#include "box_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEEK_SET 0//�ļ���ͷ
#define SEEK_CUR 1//�ļ���ǰλ��
#define SEEK_END 2//�ļ�ĩβ

#define HISTOIRY_HEAD_LEN 1//��ʷ�ļ���ͷ���ݳ���
#define MAX_RECORD 200//����¼����
/*
function:������Ϣ��ʼ��
input: box_num ��Ҫ��ʼ�������Ӹ��� flag ����ʱ�Ƿ���Ҫ��ʼ�� 0 �� 1 ��
output: 0 ��ʼ��ʧ�� 1��ʼ���ɹ�
*/
unsigned char box_info_init(unsigned char box_num , unsigned char flag)
{
	BOX_MSG box_info;
	unsigned char count = 0;
	FILE *box_file;
	int write_count;
	
	if(flag == 1)
	return 1;//�����ʼ����ֱ�ӷ���

	box_file = fopen("box_msg.dat","w+b");//�Զ�������̬�½��ļ�
	fseek(box_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	if(box_file == NULL)
	return 0;

	memset(&box_info , 0xff , sizeof(BOX_MSG));
	box_info.type = BOX_TYPE_MIN;
	box_info.status = BOX_IDLE;
	memset(box_info.virtualnumber , '0' , VIRTUAL_NUM_LENGTH);//��������ȳ�ʼ��Ϊ0
	for(count=0;count<box_num;count++)
	{
		box_info.station_num = count+1;
		box_info.station_port = count+1;
		box_info.virtualnumber[VIRTUAL_NUM_LENGTH-1] = (count+1)%10+'0';//д���λ
		box_info.virtualnumber[VIRTUAL_NUM_LENGTH-2] = (count+1)/10+'0';//д���λ
		write_count = fwrite((char *)&box_info ,  1 , sizeof(BOX_MSG) , box_file);//д���ļ���
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//д��ʧ��
		}
	}
	fclose(box_file);//�ر��ļ�
	return 1;
	
}

/*
function: �������кŶ�ȡ������Ϣ
input: station_num �������к�  box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_station_num(unsigned char station_num , BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;
	if(0 != fseek(box_file , (station_num-1)*sizeof(BOX_MSG) , SEEK_SET))//�ƶ��ļ�ָ�뵽��Ҫ��λ��
	{
		return 0;//��ȡʧ��
	}
	write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//����ǰ����Ϣֱ�Ӷ�����box_info��
	if(write_count != sizeof(BOX_MSG))
	{
		fclose(box_file);
		return 0;//��ȡʧ��
	}
	fclose(box_file);//�ر��ļ�
	return 1;	
}

/*
function: ͨ��������Ŷ�ȡ������Ϣ
input: virtualnumber  box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_virtualnumber(char *virtualnumber ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;

	while(1)//ƥ�����������Ϣ��ֱ�����
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//˳���ȡ
		if(0 == memcmp(virtualnumber , box_info->virtualnumber , VIRTUAL_NUM_LENGTH))
		{
			fclose(box_file);
			return 1;//ƥ��ɹ�
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//ƥ��ʧ�ܣ���ĩβ��
		}
	}
}

/*
function: ͨ���û���ID�Ŷ�ȡ������Ϣ
input: user_ID �û�ID�� box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_user_id(char *user_ID ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;

	while(1)//ƥ�����������Ϣ��ֱ�����
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//˳���ȡ
		if((box_info->status == BOX_USED) && (0 == memcmp(user_ID , box_info->user_id, USERID_LENGTH)))
		{
			fclose(box_file);
			return 1;//ƥ��ɹ�
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//ƥ��ʧ�ܣ���ĩβ��
		}
	}
}

/*
function: ͨ���û�ID�Ŷ�ȡ������Ϣ
input: user_ID �û�ID�� box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_pass_word(char *pass_word ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;

	while(1)//ƥ�����������Ϣ��ֱ�����,ֻƥ���Ѿ������������
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//˳���ȡ
		if((box_info->status == BOX_USED) && (0 == memcmp(pass_word , box_info->pass_word, USER_PASSWORD_LENGTH)))
		{
			fclose(box_file);
			return 1;//ƥ��ɹ�
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//ƥ��ʧ�ܣ���ĩβ��
		}
	}
}

/*
function: ͨ������״̬��ȡ������Ϣ ,�����ڿ�������
input: status ����״̬ box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_status(char status ,  BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;

	while(1)//ƥ�����������Ϣ��ֱ�����
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//˳���ȡ
		if(box_info->status == status)
		{
			fclose(box_file);
			return 1;//ƥ��ɹ�
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//ƥ��ʧ�ܣ���ĩβ��
		}
	}
}

/*
function: ͨ������״̬��ȡ������Ϣ ,�����ڿ�������
input: status ����״̬ type �������� box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char read_box_info_status_type(char status , char type , BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;

	while(1)//ƥ�����������Ϣ��ֱ�����
	{
		write_count = fread((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//˳���ȡ
		if((box_info->status == status) && (box_info->type == type))//ͬʱ������������
		{
			fclose(box_file);
			return 1;//ƥ��ɹ�
		}
		if(write_count != sizeof(BOX_MSG))
		{
			fclose(box_file);
			return 0;//ƥ��ʧ�ܣ���ĩβ��
		}
	}
}

/*
function: д��������Ϣ
input: box_info ��д���������Ϣ
output: 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
unsigned char write_box_info(BOX_MSG *box_info)
{
	FILE *box_file;
	int write_count;

	box_file = fopen("box_msg.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;
	fseek(box_file , (box_info->station_num-1)*sizeof(BOX_MSG) , SEEK_SET);//�ƶ��ļ�ָ�뵽��Ҫ��λ��
	write_count = fwrite((char *)box_info ,  1 , sizeof(BOX_MSG) , box_file);//����ǰ����Ϣֱ�Ӷ�����box_info��
	if(write_count != sizeof(BOX_MSG))
	{
		fclose(box_file);
		return 0;//д��ʧ��
	}
	fclose(box_file);//�ر��ļ�
	return 1;		
}

//��ʷ��¼��ʼ���������ļ�������indexֵ
unsigned char history_info_init(void)
{
	unsigned char index = 0;
	FILE *history_file;
	int write_count;


	history_file = fopen("history.dat","w+b");//�Զ�������̬�½��ļ�
	fseek(history_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	if(history_file == NULL)
	return 0;
	write_count = fwrite(&index ,  1 , HISTOIRY_HEAD_LEN , history_file);//д��indexֵΪ0
	if(write_count != 1)
	{
		return 0;
	}
	fclose(history_file);
}

//д��ĳһ����ʷ��¼,index��1��ʼ
unsigned char write_history_info(HISTORY_MSG *history_msg)
{
	FILE *history_file;
	int write_count;
	unsigned char index;

	history_file = fopen("history.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//��ȡindexֵ
	index++;
	if(index > MAX_RECORD)
	{
		index = 0;//�����ݴ洢����200�������ͷ��ʼ�棬�γ�һ��ѭ��
	}
	history_msg->index = index;
	fseek(history_file,(HISTOIRY_HEAD_LEN + index*sizeof(HISTORY_MSG)),SEEK_SET);//�ƶ��ļ�ָ�뵽��Ӧд���λ��
	write_count = fwrite((char *)history_msg ,  1 , sizeof(HISTORY_MSG) , history_file);//д����ʷ��¼
	fseek(history_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ	
	write_count = fwrite(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//����index
	fclose(history_file);
	return 1;
	
}

//��ȡĳһ����ʷ��¼
unsigned char read_history_info(unsigned char time_index , HISTORY_MSG *history_msg)
{
	FILE *history_file;
	int write_count;
	unsigned char index;

	history_file = fopen("history.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//��ȡindexֵ	
	/*��ȡ�ļ�λ��*/
	if(time_index <= index)
	{
		index = index-(time_index-1);//ָ����ǰ�ļ�¼
	}else
	{
		index = MAX_RECORD - (time_index -1 - index);
	}
	if(0 !=fseek(history_file,(HISTOIRY_HEAD_LEN + index*sizeof(HISTORY_MSG)),SEEK_SET))//�ƶ��ļ�ָ�뵽��Ӧ��ȡ��λ��
	{
		fclose(history_file);
		return 0;
	}
	write_count = fread((char *)history_msg ,  1 , sizeof(HISTORY_MSG) , history_file);//��ȡ��ʷ��¼	
	if(history_msg->index != index)
	{
		fclose(history_file);
		return 0;		
	}
	fclose(history_file);
	return 1;
	
}

//��ȡ��ʷ��¼����
unsigned char read_history_count(void)
{
	FILE *history_file;
	int write_count;
	unsigned char index=0;
	HISTORY_MSG history_msg;
	
	if(1 == read_history_info(MAX_RECORD , &history_msg))
	{
		//�鿴����¼����û�м�¼
		return MAX_RECORD;//ֱ�ӷ�������¼��
	}



	history_file = fopen("history.dat","r+b");//�Զ�������̬���ļ�,�ɶ���д	
	if(history_file == NULL)
	{
		return 0;
	}
	fseek(history_file,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	write_count = fread(&index ,  1 , HISTOIRY_HEAD_LEN, history_file);//��ȡindexֵ	
	return index;//���ؼ�¼λ��
	fclose(history_file);	
	
}


