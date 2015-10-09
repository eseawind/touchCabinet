#ifndef __USER_CFG_H_
#define __USER_CFG_H_

#define INIT_FLAG  0x07//flash��ʼ����־λ

#define ICMOD 0 //ѡ��IC��ģʽ��Ϊ1 ΪIC��ģʽ��Ϊ0 ��Ϊ����ģʽ
#define ICMOD_485 0
#define ICMOD_GPRS 1//GPRSģʽ��ע�⣺GPRSģʽָ�����485ģʽָ��

#define OLD_NEW_BOARD 1//���ϰ���ʶ���־ 0 �ϰ���  1 �°���

#define PC_MOD 1//ѡ���Ƿ�����λ������ѡ��Ϊ1
#define PC_BKP_NUM 19200//485��GPRS������ 	 485Ϊ9600  GPRSΪ19200
#define GUANG_DONG_MOD 1 //�ر�Ĺ㶫ģʽ,���������0xff
#define GUANG_DONG_SENDID_LENGTH 20
#define GUANG_DONG_USERID_LENGTH 20

#define BOX_FEED_BACK	1//ѡ����û������״̬����  0�� ��1��
#define USER_INPUT_BOXNUM 0	 //ѡ���û���ֱ�������뿪��0 �������������������1
#define TESTMOD 0 //ѡ���ж������Ƿ���ʧЧ��1 ���ж� 0 �ж�
/*����״̬*/
#define CLOSE_STAT       1//���ӹ�
#define OPEN_STAT        0//���ӿ�

/*�������볤�ȶ���*/
#if !ICMOD
#define SENDID_LENGTH  20	  //�ͻ�Ա�Ŀ�����Ϣ����,����ģʽ��
#define USERID_LENGTH  6	  //ȡ���˵���Ϣ���� ,����ģʽ��
#else
#define SENDID_LENGTH  17	  //�ͻ�Ա�Ŀ�����Ϣ���ȣ�ICģʽ��
#define USERID_LENGTH  4	  //ȡ���˵���Ϣ���ȣ�ICģʽ��
#endif

#define USER_PASSWORD_LENGTH 6 //�û����볤��
#define VIRTUAL_NUM_LENGTH 4//������ų���һ��Ϊ4��2
#define CAB_STATION_LENGTH 3 //���ӵ�վ�ų�������,IC����ģʽ�£���Ų��ܳ���255

#define BOXNUM 16//Ĭ��������16

#define COMPANY_FLAG 0//���幫˾�ض���־λ����Ϊ0��û�б�־λ������Ϊ�����ַ� 'H'
#define CAB_NUM_FLAG 1//�����Ƿ���Ҫƥ���ţ���λ��
#define DAY_START_HOUR 6//����һ�쿪ʼ��ʱ�䣬��ʱ��У���й�
#define LONGEST_TIME  48//��Ч�ڱ��ֵ��ʱ�䣬Сʱ


#define TIME_MAIN	 8*50	  //�ȴ�8s�ص�������

#define TIP_S		1
#define TIP_MS		500	  //��ʾʱ��1.5s

#define OPEN_DOOR_TIME 700//����ʱ��700ms
#define WAIT_DOOR_TIME  700//�ȴ�������ȫ��ʱ�䣬����ʱ��͵ȴ�ʱ����������ǿ��䷴Ӧʱ��, ��󣹣���

/*����Ļ���ĳ���*/
#define MAIN_LINE1 "˳ �� ¡"
#define MAIN_LINE3 "ˢ����'ȡ'����"
#define MAIN_LINE4 "tel:4001-029-529"

#endif
