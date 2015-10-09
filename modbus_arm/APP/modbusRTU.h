#ifndef __MODBUSRTU_H
#define __MODBUSRTU_H

/*modbusRTUͷ�ļ���ʵ��ARM�ϵ�ͨѶ����*/

//=================================================================================================
#define MODBUS_ADDR			0X01//modbusЭ��վ��
//-----------------------------------
#define PACK_START		1	// ���ݿ�ʼ����
#define PACK_REC_ING		2//���ڽ�������
#define PACK_ADDR_ERR		4	// ��ַ������
#define PACK_REC_OK		8	// ������ֽ��� ��ͬ�ж� ����һ��֡�ɹ�
/*�ṹ�嶨��*/

/*modbusλ�ö��壬�ϸ��մ����������������������16λ�ģ�������ʱ����Ҫ
�ѵ�ַ*2Ȼ���Ӧ����ĵ�ַ*/
struct MODBUS_ADD{
unsigned char station_num_H;
unsigned char station_num_L;//�������кţ���λһ��Ϊ0
unsigned char station_port_H;
unsigned char station_port_L;//���Ӷ˿ںţ���λһ��Ϊ0
unsigned char send_comm_H;
unsigned char send_comm_L;//����ָ���λһ��Ϊ0
unsigned char back_comm_H;
unsigned char back_comm_L;//����ָ���λһ��Ϊ0
unsigned char send_id[24];//�˻�����
unsigned char user_id[4];//�û�ID��
unsigned char send_id_flag_H;
unsigned char send_id_flag_L;//�˻�����ɨ���־
unsigned char user_id_flag_H;
unsigned char user_id_flag_L;//�û�IDʹ�ñ�־
};

extern struct MODBUS_ADD modbus_Addt;//����һ��modbus�ṹ�����
extern struct MODBUS_ADD *modbusAdd;//�ṹ��ָ�룬ָ���������
extern int rec_time_out;//��ʱ
extern int rec_stat;//����״̬
extern int rec_num;//���յ��ֽ���
extern int send_count;//Ҫ���͵��ֽ���
extern unsigned char send_buf[200];

unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);

unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void init_MODBUS(void);
unsigned char checkPACK_MODBUS(unsigned char *rec_buff , int rec_num);
unsigned int comp_crc16(unsigned char *pack, unsigned char num);
void function_MODBUS(unsigned char *rec_buff , unsigned char *send_data);
void read_reg(unsigned char * rec_buff , unsigned char * send_data);
void force_reg(unsigned char * rec_buf , unsigned char * send_data);
int time_out_check_MODBUS(void);
#endif
