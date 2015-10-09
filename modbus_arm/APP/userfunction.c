/*�û�����ʵ���ļ�
�ж��������ݵ����ͣ������������ݲ������ӻ��������
*/
#include "includes.h"
#include "dis_fuction.h"
/*�û���Ϣ����*/
#define SENDID 1
#define GETID  2
#define NOID   0

/*�˻�����Ч��*/
#define RIGHT_MSG 1
#define WRONG_MSG 0

typedef struct sendID_msg{
#if COMPANY_FLAG
		u8 flag;
#endif
		u8 time_year[4];
		u8 time_month[2];
		u8 time_day[2];

#if CAB_NUM_FLAG
		u8 cab_num[3];	//�洢���Ӻţ����ڹ��ӵ�ʶ��3��31��
#endif

#if COMPANY_FLAG
#if CAB_NUM_FLAG
		u8 rand_data[SENDID_LENGTH-12];
#else
		u8 rand_data[SENDID_LENGTH-9];
#endif

#else

#if CAB_NUM_FLAG
		u8 rand_data[SENDID_LENGTH-11];
#else
		u8 rand_data[SENDID_LENGTH-8];
#endif
#endif
}SEND_IDMSG;

static u8 GetMsgType(u8 *user_msg);
static u8 JudgSendMsg(u8 *user_msg);
static void ChangeSendBoxMsg(BOX_MSG *box_msg , u8 *user_msg);
static void ChangeUserBoxMsg(BOX_MSG *box_msg , u8 *user_msg);
static void RecordBoxMsg(BOX_MSG *box_msg);
extern void GetCabID(u8 *buf);
/*�û�����ʵ�ֺ�����ˢ��ģʽ*/
void UserFunction(u8 *user_msg)
{
	u8 user_msg_type = GETID;
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//��ʾ����

#if !ICMOD
	/*�ж���Ϣ����*/
	user_msg_type = GetMsgType(user_msg);

	/*�û���Ϣ����*/
	if(NOID == user_msg_type)
	{
		strcpy(sing_temp->y2 , "��Ч��");
		goto user_end;
	}

	/*�ͻ�Ա����Ϣ*/
	if(SENDID == user_msg_type)
	{
#if !TESTMOD
		/*�жϸ��˻�������Ч��*/
		if(WRONG_MSG == JudgSendMsg(user_msg))
		{
			strcpy(sing_temp->y2 , "�����ѹ��ڻ���");
			goto user_end;
		}
#endif
		/*�������õ�����*/
		SearchIdleBoxMsg(&box_msg);
		if(NULL == box_msg.virtualnumber[0])
		{
			strcpy(sing_temp->y2 , "��������");	//�����ӿ�����
			goto user_end;
		}
		/*��������������*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "����ʧ�ܣ�����ˢ"); //����ʧ��
			goto user_end;
		}

		/*�޸�box_msg��Ϣ*/
		ChangeSendBoxMsg(&box_msg , user_msg);
	}
#endif

	/*һ���û�����Ϣ*/
	if(GETID == user_msg_type)
	{
		/*�����û�����������������*/
		SearchUserBoxMsg(user_msg , &box_msg);
		if(NULL == box_msg.virtualnumber[0])
		{
			strcpy(sing_temp->y2 , "��Ч��"); //������������
			goto user_end;
		}
		/*��������������*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "����ʧ��,����ˢ"); //����ʧ��
			goto user_end;
		}
		/*�޸�box_msg��Ϣ*/
#if !ICMOD
		ChangeUserBoxMsg(&box_msg , user_msg);
#endif
	}

	/*��¼��Ϣ��flash*/
	RecordBoxMsg(&box_msg );
	/*������Ϣ����λ��*/
#if ICMOD
#if ICMOD_GPRS
	IC_PCSendUserData(box_msg.station_num);
#endif
#else
	PCSendUserData(box_msg.station_num);
#endif

	/*��ʾ����*/
	memset(sing_temp->y2 , 0 , LINE_LENGTH);
	memcpy(sing_temp->y2 ,  box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
	strcat(sing_temp->y2 , "�����ѿ�");			 //****���ѿ�
	strcpy(sing_temp->y3 , "ʹ�ú���ر�����"); 
user_end:
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*�û���ȡ������*/
void UserGetPack(void)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	
UserGetStart:
#if USER_INPUT_BOXNUM
	pfunSubBlock->data_type = ZINUM;//��ʾ����
	strcpy(sing_temp->y2 ,  "���������");
	/*ȡ��VIRTUAL_NUM_LENGTHλ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , VIRTUAL_NUM_LENGTH))
	{
		FreeMem();
		return;
	}
	/*���������ѯ��Ӧ������*/
	SearchBoxMsg((u8 *)sing_temp->y3 , &box_msg);
	memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
	if(NULL == box_msg.virtualnumber[0])//û�в鵽
	{
		strcpy(sing_temp->y2 ,  "�����������������");		
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		goto UserGetStart;
	}
	/*�жϸ����Ƿ���ע��*/
	if(BOX_USED != box_msg.status)
	{
		strcpy(sing_temp->y1 ,  "����δע���������");
		strcpy(sing_temp->y2 ,  "����������");
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto UserGetStart;			
	}
	else
#endif
	{
		pfunSubBlock->data_type = XINGNUM;//��������
		strcpy(sing_temp->y2 ,  "��������������");
		/*ȡ������*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		 /*��֤����*/
#if USER_INPUT_BOXNUM
		if(0 != memcmp(sing_temp->y3 , box_msg.pass_word , USER_PASSWORD_LENGTH))
#else
		SearchUserBoxMsgPassWord((u8 *)sing_temp->y3 , &box_msg);
		if(NULL == box_msg.virtualnumber[0])//û�в鵽
#endif
		{
			strcpy(sing_temp->y2 ,  "�����������������");
			memset(sing_temp->y3 , 0 , LINE_LENGTH);		
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			goto UserGetStart;			
		}
		memset(sing_temp->y3 , 0 , LINE_LENGTH);
		/*������*/
		if(CLOSE_STAT == UserOpenBox(&box_msg))
		{
			strcpy(sing_temp->y2 , "����ʧ��,������"); //����ʧ��
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			goto UserGetStart;
		}
		/*�޸�box_msg��Ϣ*/
#if !ICMOD
		ChangeUserBoxMsg(&box_msg , 0);
#endif
		RecordBoxMsg(&box_msg );
		/*������Ϣ����λ��*/
#if ICMOD
#if ICMOD_GPRS
	IC_PCSendUserData(box_msg.station_num);
#endif
#else
	PCSendUserData(box_msg.station_num);
#endif

		pfunSubBlock->data_type = NONUM;//��������
		/*��ʾ����*/
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memcpy(sing_temp->y2 ,  box_msg.virtualnumber , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "�����ѿ�");			 //****���ѿ�
		strcpy(sing_temp->y3 , "ʹ�ú���ر�����"); 
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();	
}

/*�ж���������,ֻ��������Ч
������������
*/
u8 GetMsgType(u8 *user_msg)
{
	u8 length;
	length = strlen((char *)user_msg);
	if(SENDID_LENGTH == length)
	{
		return SENDID;
	}
	if(USERID_LENGTH == length)
	{
		return GETID;
	}
	return 0;
}

/*�ж��˻�������Ч��*/
static u8 JudgSendMsg(u8 *user_msg)
{
	SEND_IDMSG *msg_judge;
	uint32_t time_now,time_tm;
	struct rtc_time code_time;
	BOX_MSG box_msg;
#if CAB_NUM_FLAG
	u8 IDbuf[6];
#endif
	memset(&code_time , 0 ,sizeof(struct rtc_time));

	msg_judge = (SEND_IDMSG *)user_msg;

#if COMPANY_FLAG
	/*�жϹ�˾��־ֵ*/
	if(COMPANY_FLAG != msg_judge->flag)
	{
		return WRONG_MSG;
	}
#endif

/*�жϹ��Ӻţ�3��31���*/
#if CAB_NUM_FLAG
	GetCabID(IDbuf);
	/*�ȽϹ���ID��*/
	if(0 != memcmp(IDbuf+3 , msg_judge->cab_num , 3))
	{
		return WRONG_MSG;
	}

#endif
	
	/*��ʼʱ��У��*/
	code_time.tm_year = (msg_judge->time_year[0]-'0')*1000 + (msg_judge->time_year[1]-'0')*100 +
	                     (msg_judge->time_year[2]-'0')*10	+ (msg_judge->time_year[3]-'0');
	code_time.tm_mon = (msg_judge->time_month[0]-'0')*10 + (msg_judge->time_month[1]-'0');
	code_time.tm_mday = (msg_judge->time_day[0]-'0')*10 + (msg_judge->time_day[1]-'0');
	code_time.tm_hour = DAY_START_HOUR;

	/*����ʱ���ȥ�˻����ϵ�ʱ�䣬����ʱ��һ��Ҫ���˻���ʱ�����
	ʱ���߼���ϵŪ���ˣ�����ʱ��С������ʱ�䣬�򱾵�ʱ���������ʱ��ĳ������ʱ�����Ϊ������Ч	2013.4.20
	*/
	time_now = RTC_GetCounter();
	time_tm = mktimev(&code_time); //ʹ�ÿ⺯��mktimev ֻ��ʹ��һ�Σ������޸ĸ���ȥ��ֵ
	if((time_now < time_tm) || (time_now - time_tm) > LONGEST_TIME*60*60)
	{
		return WRONG_MSG;
	}

	/*��ʼ��¼У�飬�������ӱ���������¼*/
	for(box_msg.station_num = 0 ; box_msg.station_num < strlen((char *)pboxStatus) ; box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);//��������������Ϣ
		if(0 == memcmp(box_msg.send_id0 , user_msg , SENDID_LENGTH))//����ͬ��
		{
			return WRONG_MSG;
		}
		if(0 == memcmp(box_msg.send_id1 , user_msg , SENDID_LENGTH))//����ͬ��
		{
			return WRONG_MSG;
		}
	}

	/*���е�У��ͨ��*/
	return RIGHT_MSG;
}

/*�û���ָ��������
���� OPEN_STAT �򿪳ɹ�
     CLOSE_STAT ��ʧ��
	 ��ӷֶ�εȴ������ϵͳ�����ٶ�
*/
u8 UserOpenBox(BOX_MSG *box_msg)
{
	u8 count_open_time = 10;//��10�εȴ�	WAIT_DOOR_TIME/
	OpenOneBox(box_msg);

	OSSemPend(door_semp , 0 , &err);//�ȴ������ź�
	/*������Ϻ��ٵ�һ��ʱ��*/
	while(count_open_time--)
	{
		 if(OPEN_STAT == ReadOneBox(box_msg))
		 {
		 	break;
		 }
		 OSTimeDlyHMSM(0, 0, 0,WAIT_DOOR_TIME/10);
	}
	
	if(CLOSE_STAT == ReadOneBox(box_msg))
	{
		return CLOSE_STAT;
	}
	return OPEN_STAT;
}

/*�޸��ͻ�Ա�ͻ��ɹ����Ӧ����Ϣ*/
void ChangeSendBoxMsg(BOX_MSG *box_msg , u8 *user_msg)
{											
	box_msg->status = BOX_USED; //�޸�����״̬
	memcpy(box_msg->send_id1 , box_msg->send_id0 , SENDID_LENGTH);
	memcpy(box_msg->send_id0 , user_msg , SENDID_LENGTH);		  //��¼�ͻ�ԱID
	memset(box_msg->user_id , 0xff , USERID_LENGTH);//����û�ID
	memset(box_msg->pass_word , 0xff , USER_PASSWORD_LENGTH);//����û�����
	pboxStatus[box_msg->station_num] = BOX_USED;
/*
#if TESTMOD	
	memcpy(box_msg->user_id , "201212291234" , 12);
	memcpy(box_msg->pass_word , "123456" , 6);
#endif*/
}

/*�޸Ŀͻ�ȡ���ɹ����Ӧ����Ϣ*/
void ChangeUserBoxMsg(BOX_MSG *box_msg , u8 *user_msg)
{
	box_msg->status = BOX_IDLE;  //�޸�����״̬
	pboxStatus[box_msg->station_num] = BOX_IDLE;
}

/*�ҳ��������ʷ��¼�����ؼ�¼����Ե�ַ
��i����4��
*/
u8 FindHNearestRecord(u8 station_num ,H_BOX_MSG *box_hmsg)
{
	u8 i,temp=0;
	/*�ҳ����ֵ*/
	for(i=1;i<=4;i++)
	{
		ReadOneBoxHMsg(station_num , i ,box_hmsg);
		if(temp < box_hmsg->hCount)
		{
			temp = box_hmsg->hCount;
		}
		else
		if(temp > box_hmsg->hCount)
		{
			break;
		}
	}
//	if(i == 5) i = 4;
	return i-1;
}

/*��¼�û���Ϣ��flash
���м�¼��ʷ��¼*/
void RecordBoxMsg(BOX_MSG *box_msg)
{
	H_BOX_MSG box_hmsg;
	u8 i=0;
	/*��¼�û���Ϣ*/
	WriteOneBoxMsg(box_msg);
	/*�ҳ�����ļ�¼*/
	i = FindHNearestRecord(box_msg->station_num , &box_hmsg);
	if(i>=4)	 i = 1;			
	else	    i++;
	
	box_hmsg.hCount++;
	/*����һ������ֵʱ�ٷ�ת����*/
	if(box_hmsg.hCount == 252)
	{
		for(i=1;i<=3;i++)
		{
			ReadOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
			box_hmsg.hCount = i;
			WriteOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
		}
		box_hmsg.hCount = i;
	}
	GetTimeStr((char *)box_hmsg.hTime , &systmtime);//��ȡʱ��
	box_hmsg.hStatus = box_msg->status;		 //��ȡ״̬
	WriteOneBoxHMsg(box_msg->station_num , i ,&box_hmsg);
}
