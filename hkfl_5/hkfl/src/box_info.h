#ifndef __BOX_INFO_H_
#define __BOX_INFO_H_

//#define unsigned char uchar

/*����״̬*/
#define BOX_IDLE	'0' //����
#define BOX_USED  '1'//�ѷ�����û�������������Ʒ
#define BOX_LOCK  '3'//��������������䣬ֻ�й���Ա���Բ���
#define BOX_OK_PC  '2' //������λ�������ɹ�

/*�����ͺ�*/
#define BOX_TYPE_MIN '1'//С
#define BOX_TYPE_MID '2'//��
#define BOX_TYPE_MAX '3'//��

/*������Ϣ��������*/
#define VIRTUAL_NUM_LENGTH 4 //������ų���һ��Ϊ4��2
#define USER_PASSWORD_LENGTH 6 //�û����볤��
#define SENDID_LENGTH  20	  //�ͻ�Ա�Ŀ�����Ϣ����
#define USERID_LENGTH  10	  //ȡ���˵���Ϣ����
#define USER_PHNUM_LENGTH 11//�û����ֻ���
#define SEND_NUM_LENGTH 10//����ԱID��

/*һ���������ӵ�������Ϣ�����ж����ӵĲ��������ڴ˽ṹ�����*/
typedef struct box_msg
{
	unsigned char station_num;//�������к� ��ֵ ��1��ʼ
	unsigned char station_port;//���Ӷ˿ں� ��ֵ ��1��ʼ
	char virtualnumber[VIRTUAL_NUM_LENGTH];//�����˺ţ�һ��2-4λ ����ȫ���ַ���ʽ
	char type;//�����ͺ� '1'С  '2'��  '3'��
	char status;    //����״̬
	char user_id[USERID_LENGTH];//�û�ID �ô�Ϊ�û�������Ż�IC���ţ� ��Ĳ�0xff�������Ҳ��0xff
	char user_phnum[USER_PHNUM_LENGTH];
	char pass_word[USER_PASSWORD_LENGTH];//�û����� һ��Ϊ6λ
	char send_num[SEND_NUM_LENGTH];//����Ա���
	char send_id[SENDID_LENGTH];//����Աʹ�õ������
}BOX_MSG;

typedef struct history_msg
{
	unsigned char index;//0��200ѭ������
	BOX_MSG box_info;//��ǰ������Ϣ
	unsigned long data_time;//��ǰʱ��
}HISTORY_MSG;

/*������Ϣ�������Ļ�������*/
unsigned char box_info_init(unsigned char box_num , unsigned char flag);//��������Ϣ��ʼ��
unsigned char read_box_info_station_num(unsigned char station_num , BOX_MSG *box_info);//�������кŶ�ȡ������Ϣ
unsigned char read_box_info_virtualnumber(char *virtualnumber ,  BOX_MSG *box_info);//����������Ŷ�ȡ��Ϣ
unsigned char read_box_info_user_id(char *user_id ,  BOX_MSG *box_info);//�����û�ID��ȡ��Ϣ
unsigned char read_box_info_pass_word(char *pass_word ,  BOX_MSG *box_info);//�����û������ȡ��Ϣ
unsigned char read_box_info_status(char status ,  BOX_MSG *box_info);//��������״̬��ȡ��Ϣ,�����ڿ�������
unsigned char read_box_info_status_type(char status , char type , BOX_MSG *box_info);//��������״̬�����Ͷ�ȡ��Ϣ,�����ڿ������������

unsigned char write_box_info(BOX_MSG *box_info);//д��ĳ��������Ϣ���ɰ������к�����λ��

/*��ʷ��¼��������������*/
unsigned char history_info_init(void);//��ʷ��¼��ʼ���������ļ�������indexֵ
unsigned char read_history_info(unsigned char index , HISTORY_MSG *history_msg);//��ȡĳһ����ʷ��¼
unsigned char write_history_info(HISTORY_MSG *history_msg);//д��ĳһ����ʷ��¼
unsigned char read_history_count(void);
#endif

