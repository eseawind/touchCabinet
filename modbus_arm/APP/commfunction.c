#include "includes.h"

extern u8 err;
/*
�޸Ĺ���Ա����
*/
void CommChangePassWord(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	u8 *pass_wordbuf[7];

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//��ʾ����

startCommChange:
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
		memcpy(cab_msg.comm_password,pass_wordbuf,6);
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
		goto startCommChange;
	}
	FreeMem();
}

/*ע���û�*/
void CommRegistUser(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

RegistStart:
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
		goto RegistStart;
	}
	else
	{
		u8 *icbuf = NULL;
		/*�жϸ����Ƿ����*/
		if(BOX_IDLE != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "������ע�������");
			strcpy(sing_temp->y2 ,  "����������");
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto RegistStart;			
		}

		/*�õ���ȷ��ź�����ȴ��ɣÿ�����*/
		strcpy(sing_temp->y2 ,  "��ˢ��������");
		OSMboxPost(display_box , pfunSubBlock);// ��������,ˢ����ʾ
		icbuf = OSMboxPend(user_box , 5000 , &err);//�ȴ�5s
		ICcardDisable();
		if(icbuf == NULL)//��ʱ����
		{
			FreeMem();
			ICcardEnable();
			return;
		}
		/*д���Ӧ����Ϣ*/
		memcpy(box_msg.user_id , icbuf , USERID_LENGTH);
		memset(box_msg.pass_word , '8' , USER_PASSWORD_LENGTH);//д��Ĭ������888888
		box_msg.status = BOX_USED;
		pboxStatus[box_msg.station_num] = BOX_USED;
		WriteOneBoxMsg(&box_msg);

		strcpy(sing_temp->y2 ,  "ע��ɹ�!");
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
		ICcardEnable();
	}
	FreeMem();
}


/*ע���û�*/
void CommCancleUser(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

CancleStart:
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
		goto CancleStart;
	}
	else
	{
		/*�жϸ����Ƿ���ע��*/
		if(BOX_USED != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "����δע���������");
			strcpy(sing_temp->y2 ,  "����������");
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto CancleStart;			
		}

		/*д���Ӧ����Ϣ���ص���ʼ״̬*/
		memset(box_msg.user_id , 0xff , USERID_LENGTH);
		memset(box_msg.pass_word , 0xff , USER_PASSWORD_LENGTH);
		box_msg.status = BOX_IDLE;
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		WriteOneBoxMsg(&box_msg);

		strcpy(sing_temp->y2 ,  "ע���ɹ�!");
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*�����������
�����������趨Ϊ��ʹ��״̬
*/
void CommClearAllBox(FUN_BLOCK **funBlock)
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
		box_msg.status = BOX_IDLE;//�޸�����״̬
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "�������");			 //****�������
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2	
}

/*����ָ������*/
void CommLockOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

LockOneStart:
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
		goto LockOneStart;
	}
	else
	{
		box_msg.status = BOX_LOCK; //״̬��Ϊ����
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_LOCK;

		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "��������");			 //****��������
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*����ָ������*/
void CommUnLockOneBox(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

UnLockOneStart:
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
		goto UnLockOneStart;
	}
	else
	{
		box_msg.status = BOX_IDLE; //״̬��Ϊ����
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;

		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		strcpy(sing_temp->y2 ,  sing_temp->y3);
		strcat(sing_temp->y2 , "���ѽ���");			 //****���ѽ���
		memset(sing_temp->y3 , 0 , VIRTUAL_NUM_LENGTH);
		DisplaySubBlock(pfunSubBlock);
	}
	FreeMem();
}

/*������������*/
void CommLockAllBox(FUN_BLOCK **funBlock)
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
		box_msg.status = BOX_LOCK;//�޸�����״̬
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_LOCK;

		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "��������");			 //****��������
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2	
}

/*������������*/
void CommUnLockAllBox(FUN_BLOCK **funBlock)
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
		box_msg.status = BOX_IDLE;//�޸�����״̬
		WriteOneBoxMsg(&box_msg);
		pboxStatus[box_msg.station_num] = BOX_IDLE;
		memcpy(sing_temp->y2 ,  (char *)(box_msg.virtualnumber) , VIRTUAL_NUM_LENGTH);
		strcat(sing_temp->y2 , "���ѽ���");			 //****���ѽ���
		/*��ʾ*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
	}
	FreeMem();
	TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2	
}




