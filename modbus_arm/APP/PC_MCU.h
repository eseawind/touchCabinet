#ifndef __PC_MCU_H_
#define __PC_MCU_H_

#include "user_cfg.h"

/*ָ���ʽ����*/
#define HEAD1 0xa5
#define HEAD2 0xa5

#define OVER_FLAG 0x40

/*����ָ�����Ͷ���*/
#define POWER_ON  'A'
#define USER_DATA 'B'
#define PC_COMM   'C'

/*ָ��ͷ����ʽ*/
typedef struct HEAD_Block{
	unsigned char head1;
	unsigned char head2;	//ָ��ͷ
	unsigned char length[2];//���ݳ��� = length[0]<<8 + length[1];
	unsigned char cabID[6]; //���ӱ�ţ����λ��Ч
	unsigned char type;//ָ������
}HEAD_BLOCK;

/*ָ�����ݰ���ʽ*/
#if !GUANG_DONG_MOD
typedef struct pack_block{
	char station_num[2];      //��2Byte���������к�
	char virtualnumber[VIRTUAL_NUM_LENGTH];     //��VIRTUAL_NUM_LENGTH Byte���������
	char status;             //����״̬��'1' ����  '0' ȡ�� ��
	char barcode[SENDID_LENGTH];        //����ţ��ͻ�Ա��
	char userID[USERID_LENGTH];         //ID�ţ��ͻ���
	char userPassWord[USER_PASSWORD_LENGTH];//�û�����
}PACK_BLOCK;
#else
typedef struct pack_block{
	char station_num[2];      //��2Byte���������к�
	char virtualnumber[VIRTUAL_NUM_LENGTH];     //��VIRTUAL_NUM_LENGTH Byte���������
	char status;             //����״̬��'1' ����  '0' ȡ�� ��
	char barcode[GUANG_DONG_SENDID_LENGTH];        //����ţ��ͻ�Ա��
	char userID[GUANG_DONG_USERID_LENGTH];         //ID�ţ��ͻ���
	char userPassWord[USER_PASSWORD_LENGTH];//�û�����
}PACK_BLOCK;

#endif

unsigned char OpenPack(unsigned char *rec_buf);
void PCSendUserData(unsigned char station_num);
void PCRecvUserData(unsigned char *databuf);
void PCSysPowerOn(void);
void PC_MCUComm(unsigned char *databuf);

#endif

