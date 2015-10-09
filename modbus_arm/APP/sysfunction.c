/*
���ļ���Ҫʵ��ϵͳ����Ա����
��functionList.c��Ĺ����������
*/
#include "includes.h"

/*
�޸�ϵͳ����
*/
void SysChangePassWord(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 *pass_wordbuf[7];

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//��ʾ����

startSysChange:
	strcpy(sing_temp->y2 , "������������");
	/*ȡ��6λ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}
	/*����������*/
	memcpy(pass_wordbuf , sing_temp->y3 , 6);
	memset(sing_temp->y3 , 0 ,6);
	strcpy(sing_temp->y2 , "���ٴ�����������");
	/*ȡ��6λ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}
	/*�Ƚ�ǰ����������*/
	if(0 == memcmp(pass_wordbuf , sing_temp->y3 , 6))
	{
		ReadCabinetMsg(&cab_msg);
		memcpy(cab_msg.sys_password,pass_wordbuf,6);
		/*д��flash*/
		WriteCabinetMsg(&cab_msg);
		strcpy(sing_temp->y2 , "�����޸ĳɹ�");
		memset(sing_temp->y3 , 0 , 6);
		/*����*/
		DisplaySubBlock(pfunSubBlock);
	}
	else
	{
		strcpy(sing_temp->y2 , "�����������������");
		memset(sing_temp->y3 , 0 , 6);
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		goto startSysChange;
	}
	FreeMem();
}

/*����ģʽ����*/
void SysSetWorkMod(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}

/*������������
�������������ж���������ȷ��
������Ҫ�޸�����״̬���ڴ���
*/
void SysSetBoxNum(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 box_num;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����
	ReadCabinetMsg(&cab_msg);

startSetBox:
	strcpy(sing_temp->y2 ,  "������������");
	/*ȡ��2λ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 2))
	{
		FreeMem();
		return;
	}
	/*ȡ�����������=��*/
	box_num = atoi(sing_temp->y3);
	if(box_num>80)
	{
		strcpy(sing_temp->y2 , "�������,����������");
		memset(sing_temp->y3 , 0 ,3);
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		goto startSetBox;
	}
	cab_msg.cab_box_num = box_num;
	WriteCabinetMsg(&cab_msg);

	/*�޸�ȫ��ָ��*/
	free(pboxStatus);
	pboxStatus = malloc(cab_msg.cab_box_num + 1);
	memset(pboxStatus , '0' , cab_msg.cab_box_num);
	*(pboxStatus + cab_msg.cab_box_num) = 0;//���һλ����Ϊ0������ʹ��strlen

	strcpy(sing_temp->y2 , "�����޸ĳɹ�");
	memset(sing_temp->y3 , 0 ,3);
	/*����*/
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*վ������*/
void SysSetCabStation(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����
	ReadCabinetMsg(&cab_msg);

	strcpy(sing_temp->y2 ,  "������վ��");
	/*ȡ��2λ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , CAB_STATION_LENGTH))
	{
		FreeMem();
		return;
	}
	/*ȡ��վ��*/
	memcpy(&(cab_msg.cab_station_num[6-CAB_STATION_LENGTH]) , sing_temp->y3 ,CAB_STATION_LENGTH); 
	WriteCabinetMsg(&cab_msg);

	strcpy(sing_temp->y2 ,  "վ���޸ĳɹ�");
	memset(sing_temp->y3 , 0 ,3);
	/*����*/
	DisplaySubBlock(pfunSubBlock);
	FreeMem();
}

/*��ָ������	ϵͳ����Ա�͹���Ա������
�������->�ж����->��ָ������
*/
void SysOpenOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

OpenBoxStart:
	strcpy(sing_temp->y2 ,  "���������");
	/*ȡ��VIRTUAL_NUM_LENGTHλ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , VIRTUAL_NUM_LENGTH))
	{
		FreeMem();
		return;
	}
	/*���������ѯ��Ӧ������*/
	SearchBoxMsg((u8 *)sing_temp->y3 , &box_msg);
	if(NULL == box_msg.virtualnumber[0])//û�в鵽
	{
		strcpy(sing_temp->y2 ,  "�����������������");
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		goto OpenBoxStart;
	}
	else
	{
		OpenOneBox(&box_msg);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "���ѿ�");			 //****���ѿ�
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();	
}

/*����������
������Ҫ�ص���ʱ����δ��*/
void SysOpenAllBox(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	BOX_MSG box_msg;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//��ʾ����

	TIM_Cmd(TIM2,DISABLE);//����TIM2
	for(box_msg.station_num=0; box_msg.station_num<strlen((char *)pboxStatus);box_msg.station_num++)
	{
		ReadOneBoxMsg(&box_msg);
		OpenOneBox(&box_msg);//���Ϳ����ź�
		OSSemPend(door_semp , 1000 , &err);//�ȴ���������ź�

		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "���ѿ�");			 //****���ѿ�
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2	
}

/*�˿�����
������ţ��ж���ţ�����˿�2λ��ע��˿ں�-1*/
void SysSetPort(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

SetPortStart:
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
		goto SetPortStart;
	}

	/*����˿ں�*/
	strcpy(sing_temp->y2 ,  "������˿ں�");
	if(CANCEL == KeyDisplay(pfunSubBlock , 2))
	{
		FreeMem();
		return;
	}
	box_msg.station_port = atoi(sing_temp->y3); //�޸Ķ˿ں�
	memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
	WriteOneBoxMsg(&box_msg);
	strcpy(sing_temp->y2 ,  "�˿��޸ĳɹ�");
	DisplaySubBlock(pfunSubBlock);
		
	FreeMem();	
}

/*����ϵͳʱ��*/
void SysSetTime(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

	RTC_ITConfig(RTC_IT_SEC, DISABLE);	//��RTC�жϣ���ֹsystmtime���޸�
	strcpy(sing_temp->y2 ,  "������ʱ��");
	/*ȡ��VIRTUAL_NUM_LENGTHλ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 10))
	{
		FreeMem();
		return;
	}
	/*��ȡʱ��ֵ*/
	systmtime.tm_year = 2000 + (sing_temp->y3[0]-'0')*10 + sing_temp->y3[1]-'0';
	systmtime.tm_mon = (sing_temp->y3[2]-'0')*10 + sing_temp->y3[3]-'0';
	systmtime.tm_mday = (sing_temp->y3[4]-'0')*10 + sing_temp->y3[5]-'0';
	systmtime.tm_hour = (sing_temp->y3[6]-'0')*10 + sing_temp->y3[7]-'0';
	systmtime.tm_min = (sing_temp->y3[8]-'0')*10 + sing_temp->y3[9]-'0';
	memset(sing_temp->y3 , 0 , 10);
	/*д��ʱ��*/
	RTC_Configuration();
	Time_Adjust(&systmtime);//д��ϵͳʱ��
	BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);

	strcpy(sing_temp->y2 ,  "ϵͳʱ���޸ĳɹ�");
	DisplaySubBlock(pfunSubBlock);
		
	FreeMem();
}

void SysDisplayHrecord(char *buf , u8 station_num , u8 ph_record ,H_BOX_MSG *box_hmsg)
{
		ReadOneBoxHMsg(station_num , ph_record , box_hmsg);
		if(box_hmsg->hCount == 0) return;

		memcpy(buf , box_hmsg->hTime , 15);
		if(box_hmsg->hStatus == BOX_IDLE)
		{
			strcat(buf , " ȡ");
		}
		else
		if(box_hmsg->hStatus == BOX_USED)
		{
			strcat(buf , " ��");
		}
}

/*��ѯʹ�ü�¼*/
void SysCheckRecord(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	H_BOX_MSG box_hmsg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

OpenCheckStart:
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
	memset(sing_temp->y2 , 0 , VIRTUAL_NUM_LENGTH);
	if(NULL == box_msg.virtualnumber[0])//û�в鵽
	{
		strcpy(sing_temp->y2 ,  "�����������������");		
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		goto OpenCheckStart;
	}
	else
	{
		u8 ph_record;
		ph_record = FindHNearestRecord(box_msg.station_num , &box_hmsg);
		ReadOneBoxHMsg(box_msg.station_num , ph_record , &box_hmsg);
		if(box_hmsg.hCount == 0)
		{
			strcpy(sing_temp->y2 ,  "����û�м�¼");		
			/*����*/
			DisplaySubBlock(pfunSubBlock);		
		}
		else
		{	/*����ʱ���Ⱥ�˳����ʾ*/
			SysDisplayHrecord(sing_temp->y1 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y2 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y3 , box_msg.station_num , ph_record , &box_hmsg);
			ph_record--;
			if(ph_record == 0) ph_record = 4;
			SysDisplayHrecord(sing_temp->y4 , box_msg.station_num , ph_record , &box_hmsg);
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			/*�ȴ����صļ�ֵ*/
			if(CANCEL == KeyDisplay(pfunSubBlock , 0))
			{
				FreeMem();
				return;
			}
		}
	}
	FreeMem();
}


/*�ָ���������*/
void SysRecoveryInit(FUN_BLOCK **funBlock)
{
	DIS_SING *sing_temp;
	CAB_MSG cab_msg;

	ReadCabinetMsg(&cab_msg);
	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = NONUM;//��ʾ����

	strcpy(sing_temp->y2 ,  "ȷ�ϻָ��������ã�");
	/*ȡ��VIRTUAL_NUM_LENGTHλ����������*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 10))
	{
		FreeMem();
		return;
	}

	Dis1LineMid("��ʼ���С�����" , 1);
	RefreshLCD();
	/*�ָ���������*/
	InitAllBox(INIT_FLAG);
	memset(pboxStatus , BOX_IDLE , cab_msg.cab_box_num);  //���˽������������Ϣ��� 2013.4.25
	*(pboxStatus + cab_msg.cab_box_num) = 0;//���һλ����Ϊ0������ʹ��strlen
	strcpy(sing_temp->y2 ,  "��ʼ�����");
	DisplaySubBlock(pfunSubBlock);	
}


/*�˳�
ֱ�ӻص�������*/
void SysExit(FUN_BLOCK **funBlock)
{
	*funBlock = mainFunBlock;
}

/*
��λ������⣬ʵ�ֶԹ���Ա�����ϵͳ����Ա���븴λ
������λ��5s��ʵ�ָ�λ����
time: LC 2013.8.13
*/
void RestKeyCheck()
{
/*��⸴λ���Ƿ���,����Ч*/		 
	if(!RESETKEY)
	{
		u8 i;
		LED2ON;
		for(i=0;i<100;i++)
		{
			OSTimeDlyHMSM(0, 0, 0,50);//ѭ����⣬����ʱ������3s
			if(RESETKEY)
			{
				LED2OFF;
				break;
			}
			if(i == 99)
			{
				CAB_MSG cab_msg;

				TIM_Cmd(TIM2,DISABLE);//����TIM2,��ֹ��������
				RefreshLCD();
				Dis1LineMid("��ʼ���С�����" , 1);
				RefreshLCD();//ˢ����Ļ	
				
				ReadCabinetMsg(&cab_msg);//��ȡϵͳ��Ϣ
				memset(cab_msg.sys_password , '8' , 6);//�ı�����ϵͳ����Ա���� 888888
				memset(cab_msg.comm_password , '6' , 6);//�ı�����ϵͳ����Ա����	666666
				WriteCabinetMsg(&cab_msg);//д��ϵͳ��Ϣ						

				OSTimeDlyHMSM(0, 0, 2,0);//��ʾʱ��2s				
				LED2OFF;

				TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2
				pfunBlock = mainFunBlock;	
				OSMboxPost(display_box , pfunBlock);// ��������,ˢ����ʾ���ص�����			
			}
		}
	}
}

u8 AuthorProcess(u8 key_data)
{
	static u8 key_count = 0;
	u8 author_flag = 0;
	if(key_data > 9)
	{
	 	key_count = 0;
		memset(authorbuf , 0 , 10);	
	}
	else
	{
		authorbuf[key_count++] = key_data + '0';
		if(key_count >= 9)
		{
			if(0 == memcmp(authorbuf , "503740053" , 9)) //ƥ��ɹ�
			{
				CAB_MSG cab_msg;
				ReadCabinetMsg(&cab_msg);//��ȡϵͳ��Ϣ
				memset(cab_msg.sys_password , '8' , 6);//�ı�����ϵͳ����Ա���� 888888
				memset(cab_msg.comm_password , '6' , 6);//�ı�����ϵͳ����Ա����	666666
				WriteCabinetMsg(&cab_msg);//д��ϵͳ��Ϣ

				RefreshLCD();
				Dis1LineMid("�人���˸���" , 0);
				Dis1LineMid("���ߣ�lc" , 1);
				Dis1LineMid("�汾��v7.7.3" , 2);
				RefreshLCD();//ˢ����Ļ	
				author_flag = 1;											
			}
			key_count = 0;
			memset(authorbuf , 0 , 10);	
		}
	}
	return author_flag;
}



