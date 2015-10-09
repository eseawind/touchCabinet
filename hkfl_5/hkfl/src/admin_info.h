#ifdef _ADMIN_INFO_H
#define _ADMIN_INFO_H

#define ADMIN_ID_LENTH 10
#define ADMIN_PSD_LENTH 6

#define ADMIN_FLAG 'N' //ΪN��ʾδע��
//ϵͳ��Ϣ�͹���Ա��Ϣ
typedef struct admin_info
{
	char cab_add[6];//����վ��
	unsigned char box_num;//һ��������������
	char init_flag;//��ʼ����־,Ϊ'1'���Ѿ���ʼ�� ��Ϊ����ֵ��δ��ʼ��
	char admin1;//����Ա��ţ�ΪN��ʾδע��
	char admin1_id[ADMIN_ID_LENTH];//����Ա�ɣĿ���
	char admin1_psd[ADMIN_PSD_LENTH];//����Ա����
	char admin2;
	char admin2_id[ADMIN_ID_LENTH];//����Ա�ɣĿ���
	char admin2_psd[ADMIN_PSD_LENTH];//����Ա����
	char admin3;
	char admin3_id[ADMIN_ID_LENTH];//����Ա�ɣĿ���
	char admin3_psd[ADMIN_PSD_LENTH];//����Ա����	
}ADMIN_MSG;

unsigned char admin_init(void);//���Ӻ͹���Ա��Ϣ��ʼ��
unsigned char read_admin_info(ADMIN_MSG *admin_info);//��ȡϵͳ��Ϣ
unsigned char write_admin_info(ADMIN_MSG *admin_info);//д��ϵͳ��Ϣ
unsigned char judge_admin_psd(char *password);//ͨ�������жϹ���Ա�Ƿ���ȷ
unsigned char judge_admin_id(char *admin_id);//ͨ��ID�����жϹ���Ա�Ƿ���ȷ

#endif
