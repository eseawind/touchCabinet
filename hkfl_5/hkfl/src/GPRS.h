#ifndef __GPRS_H_
#define __GPRS_H_

#define CAB_NUM_LEN 6
#define HEAD_DATA 0xa5
#define TAIL_DATA 0x5a

/*ָ�����Ͷ���*/
#define HEART_BEAT    'A'//������
#define SENDER_CONFIRM     'B'//���ʱ�˻�Ա��Ϣȷ��
#define SAVE_USER_INFO  'C'//���ʱ�����û���Ϣ
#define GETOUT_USER_INFO 'D'//�ͻ�ȡ��ʱ���û���Ϣ
#define RW_USER_INFO 'E'//��ȡ��д���û���Ϣ
#define RW_CAB_INFO 'F' //��ȡ��д�������Ϣ
#define SERVER_OPEN_BOX  'G'//Զ�̿���

/*SENDER_CONFIRM ���ݲ��� B*/
#define SENDER_ASK  '0'//�������Ȩ��
#define SENDER_OK  '1'//�������
#define SENDER_ERR '2'//������

#define SEND_ID_LEN 20
#define SEND_PSD_LEN 6

typedef struct 
{
	char flag;//��־
	char send_id[SEND_ID_LEN];//����ԱID��
	char send_psd[SEND_PSD_LEN];//����Ա����
}SENDER_INFO;

/*�û���Ϣ*/
/*������Ϣ��������*/
#define GPRS_VIRTUAL_NUM_LENGTH 4 //������ų���һ��Ϊ4��2
#define GPRS_USER_PASSWORD_LENGTH 6 //�û����볤��
#define GPRS_SENDID_LENGTH  20	  //�ͻ�Ա�Ŀ�����Ϣ����
#define GPRS_USERID_LENGTH  10	  //ȡ���˵���Ϣ����
#define GPRS_USER_PHNUM_LENGTH 15//�û����ֻ���
#define GPRS_SEND_NUM_LENGTH 20//����ԱID��

#define GPRS_ADMIN_PSD_LENGTH 6

/*SAVE_USER_INFO ��־���ֶ��� C */
#define OPEN_ASK '0'
#define OPEN_OK '1'
#define OPEN_ERR '2'
#define GET_PACK_BACK '3'

/*GETOUT_USER_INFO ��־���ֶ��� D */
#define CLEAR_ASK '0'
#define CLEAR_OK '1'
#define CLEAR_ERR '2'

/*RW_USER_INFO RW_CAB_INFO ��־���ֶ��� E F*/
#define R_INFO '0'
#define W_INFO '1'
#define RW_OK '2'
#define RW_ERR '3'

/*������־���ֶ��� */
#define NON_RESTART '0'
#define RESTART '1'
#define SYS_START '2'//ϵͳ������־


/*SERVER_OPEN_BOX ��־���ֶ��� G*/
#define CLEAR_USER_INFO '0'
#define NON_CLEAR_USER_INFO '1'
#define SERVER_OPEN_OK '2'
#define SERVER_OPEN_ERR '3'


typedef struct
{
	char flag;
	char station_num[2];
	char virtualnumber[GPRS_VIRTUAL_NUM_LENGTH];//�����˺ţ�һ��2-4λ ����ȫ���ַ���ʽ
	char type;//�����ͺ� '1'С  '2'��  '3'��
	char status;    //����״̬
	char send_id[GPRS_SENDID_LENGTH];//����Աʹ�õ������
	char send_num[GPRS_SEND_NUM_LENGTH];//����Ա���
	char user_id[GPRS_USERID_LENGTH];//�û�ID �ô�Ϊ�û�������Ż�IC���ţ� ��Ĳ�0xff�������Ҳ��0xff
	char pass_word[GPRS_USER_PASSWORD_LENGTH];//�û����� һ��Ϊ6λ
	char user_phnum[GPRS_USER_PHNUM_LENGTH];

}USER_INFO;

#define GPRS_CAB_NUM_LEN 6
typedef struct 
{
	unsigned char head[2];
	unsigned char comm_len[2];//ָ��ȣ�comm_len[0]*256+comm_len[1]
	char cabinet_num[GPRS_CAB_NUM_LEN];//���ӱ��
	char comm_type;//ָ������	
}PACK_HEAD_INFO;

/*Զ�̶�ȡ�����ù�����Ϣ���ݽṹ��*/
typedef struct
{
	char flag;//��־λ
	char cabinet_num[GPRS_CAB_NUM_LEN];//���ӱ��
	unsigned char box_num;//���ӵ���������
	char admin_psd[GPRS_ADMIN_PSD_LENGTH];//����Ա����
	char restart_flag;//������־
}CAB_INFO;

/*Զ�̿���ָ��ṹ�����ݲ���*/
typedef struct
{
	char flag;//��־
	char virtualnumber[GPRS_VIRTUAL_NUM_LENGTH];
}SERVER_OPEN_INFO;

PACK_HEAD_INFO ex_pack_head_msg;
int package_send_pack(unsigned char *sendbuf , unsigned char *cab_num ,char type , unsigned char *databuf , int data_len);
int confirm_sender(unsigned char *data_buf , unsigned char *send_num);
int package_user_data_pack(unsigned char *data_buf , unsigned char flag , BOX_MSG *box_info);
int save_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
//int confirm_save_pack(unsigned char *data_buf , BOX_MSG *box_info);
int getout_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
char rw_pack_server_back(unsigned char *data_buf , BOX_MSG *box_info);
char rw_cab_server_back(unsigned char *data_buf , CAB_INFO *cab_msg);
char server_open_box_back(unsigned char *data_buf , SERVER_OPEN_INFO *server_open_msg , BOX_MSG *box_info);

#endif

