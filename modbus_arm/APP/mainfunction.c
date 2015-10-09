/*
���ܣ�ʵ���������ĸ����Ĺ��ܺ���ʾ����
��functionList.c�ļ������
*/
#include "includes.h"
extern u8 err;

/*�Ӻ�����������*/
void DisplaySubBlock(FUN_BLOCK *funBlock)
{
	OSMboxPost(display_box , funBlock);// ��������,ˢ����ʾ
	OSTimeDlyHMSM(0, 0, TIP_S,TIP_MS);
}


/*
���ܣ�ʵ���û����̵�����͸�����ʾ
���룺��д�����ݵĽṹ��
���� CANCEL ȡ����	 ENTERȷ�ϼ�����
*/
u8 KeyDisplay(FUN_BLOCK *funBlock , u8 key_length)
{
	u8 *pkey_value = NULL; 
	u8 i=0;
	DIS_SING *sing_temp = (DIS_SING *)(funBlock->current_display);
	OSMboxPost(display_box , funBlock);// ��������,ˢ����ʾ
	while(1)
	{
		pkey_value = OSMboxPend(key_box , 0 , &err);	//���޵ȴ�
	
		switch(*pkey_value)
		{
			case CANCEL:  return CANCEL;
								
			case ENTER:   return ENTER; 
		}
		if(*pkey_value < 10)
		{
			if(i<key_length)
			{
				sing_temp->y3[i++] = *pkey_value + '0';	//ת����ASC��
				OSMboxPost(display_box , funBlock);// ��������,ˢ����ʾ	
			}
		}
	}
}

/*������ڻ������ܿ�Ŀռ�
����key_length ��������ݳ���
���ػ�õ�ָ��
*/
void GetSubFunBlock(FUN_BLOCK **pfunSubBlock)
{
//	DIS_SING *sing_temp;
	u8 temp;
	temp = sizeof(FUN_BLOCK);
	*pfunSubBlock = malloc(temp);//����һ����ʱ�ڴ�
	memset(*pfunSubBlock , 0 , temp);

	temp = sizeof(DIS_SING);
	(*pfunSubBlock)->current_display = malloc(temp);//ȫ����ʾ��ָ��
	memset((*pfunSubBlock)->current_display , 0 , temp);

//	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
//	sing_temp->y3 = malloc(key_length);//���ڴ洢����
//	memset(sing_temp->y3 , 0 , key_length);
}

/*
�������µĹ��ܺ���
ֱ��ָ���ӽ���
*/
void MainEnter(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}

/*ĸ�����µĹ��ܺ���*/

/*ϵͳ����Ա
�������룬�ж����룬������һ��
*/
void SysEnter(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//��ʾ����

start:
	strcpy(sing_temp->y2 ,  "������ϵͳ����Ա����");
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}

	ReadCabinetMsg(&cab_msg);
	/*ƥ������*/
	if(0 == memcmp(cab_msg.sys_password , sing_temp->y3 , 6))
	{
		*funBlock = (*funBlock)->sub_block;
	}
	else
	{
		strcpy(sing_temp->y1 ,  "�������");
		strcpy(sing_temp->y2 ,  "����������");
		memset(sing_temp->y3 , 0 , 7);		
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto start;
	}
	FreeMem();
}



/*����Ա
�������룬�ж����룬������һ��
*/
void CommEnter(FUN_BLOCK **funBlock)
{
	CAB_MSG cab_msg;
	DIS_SING *sing_temp;
	/*�����ڴ�������ʼ��*/
	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = XINGNUM;//��ʾ����

start:
	strcpy(sing_temp->y2 ,  "���������Ա����");

	/*��ȡ��ֵ���жϷ���ֵ����ֵװ����y3��*/
	if(CANCEL == KeyDisplay(pfunSubBlock , 6))
	{
		FreeMem();
		return;
	}

	ReadCabinetMsg(&cab_msg);
	/*ƥ������*/
	if(0 == memcmp(cab_msg.comm_password , sing_temp->y3 , 6))
	{
		*funBlock = (*funBlock)->sub_block;
	}
	else
	{
		strcpy(sing_temp->y1 ,  "�������");
		strcpy(sing_temp->y2 , "����������");
		memset(sing_temp->y3 , 0 , 7);
		/*����*/
		DisplaySubBlock(pfunSubBlock);
		memset(sing_temp->y2 , 0 , LINE_LENGTH);
		memset(sing_temp->y1 , 0 , LINE_LENGTH);
		goto start;
	}
	FreeMem();
}

/*�û��޸�����
������ţ��ж���ţ��������룬�ж����룬���������룬�ٴ����������룬�ж����룬���
*/
void UserEnter(FUN_BLOCK **funBlock)
{
	BOX_MSG box_msg;
	DIS_SING *sing_temp;

	GetSubFunBlock(&pfunSubBlock);
	sing_temp = (DIS_SING *)(pfunSubBlock->current_display);
	pfunSubBlock->data_type = ZINUM;//��ʾ����

UserStart:
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
		goto UserStart;
	}
	else
	{
		u8 pass_wordbuf[USER_PASSWORD_LENGTH];
		/*�жϸ����Ƿ���ע��*/
		if(BOX_USED != box_msg.status)
		{
			strcpy(sing_temp->y1 ,  "����δע���������");
			strcpy(sing_temp->y2 ,  "����������");
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			memset(sing_temp->y1 , 0 , LINE_LENGTH);
			goto UserStart;			
		}

		pfunSubBlock->data_type = XINGNUM;//��������
		strcpy(sing_temp->y2 ,  "��������������");
		/*ȡ������*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		if(0 != memcmp(sing_temp->y3 , box_msg.pass_word , USER_PASSWORD_LENGTH))
		{
			strcpy(sing_temp->y2 ,  "�����������������");
			memset(sing_temp->y3 , 0 , LINE_LENGTH);		
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			goto UserStart;			
		}
		memset(sing_temp->y3 , 0 , LINE_LENGTH);

UserNewStart:
		strcpy(sing_temp->y2 , "������������");
		/*ȡ��6λ����������*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		/*����������*/
		memcpy(pass_wordbuf , sing_temp->y3 , USER_PASSWORD_LENGTH);
		memset(sing_temp->y3 , 0 ,USER_PASSWORD_LENGTH);
		strcpy(sing_temp->y2 , "���ٴ�����������");
		/*ȡ��6λ����������*/
		if(CANCEL == KeyDisplay(pfunSubBlock , USER_PASSWORD_LENGTH))
		{
			FreeMem();
			return;
		}
		/*�Ƚ�ǰ����������*/
		if(0 == memcmp(pass_wordbuf , sing_temp->y3 , USER_PASSWORD_LENGTH))
		{
			memcpy(box_msg.pass_word,pass_wordbuf,USER_PASSWORD_LENGTH);
			/*д��flash*/
			WriteOneBoxMsg(&box_msg);
			strcpy(sing_temp->y2 , "�����޸ĳɹ�");
			memset(sing_temp->y3 , 0 , 6);
			/*����*/
			DisplaySubBlock(pfunSubBlock);
		}
		else
		{
			strcpy(sing_temp->y2 , "�����������������");
			memset(sing_temp->y3 , 0 , USER_PASSWORD_LENGTH);
			/*����*/
			DisplaySubBlock(pfunSubBlock);
			goto UserNewStart;
		}
		FreeMem();
	 }
}

