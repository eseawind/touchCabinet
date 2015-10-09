#include <stdio.h>

#include "lincon.h"
#include "string.h"

#define debug 1

#define PACKET_BUF_SIZE                 128

#define SERIAL_STATUS_OK                0
#define SERIAL_STATUS_SYS_ERR           -1
#define SERIAL_STATUS_PORT_ERR          -2
#define SERIAL_STATUS_TIMEOUT           -3
#define SERIAL_STATUS_PKT_ERR           -4
#define SERIAL_STATUS_PACK_ERR           -5
static int serial_id;

static int recv_pack(char *recv_packet, int recv_total_len, int *recv_len,int timeout);
static int send_pack(char *send_packet_buf);

/*ģ���ʼ��*/
static int echodemo_init()
{
    //char com_port[16];
	//long baud=9600;
    //rtdb_get_data_value_by_name("echodemo", "serialname", com_port);
    //rtdb_get_data_value_by_name("echodemo", "baud", &baud);
 
    //serial_id = serial_open(com_port, baud, SERIAL_PARITY_NO, 8, SERIAL_STOPBIT_ONE, 1000);
    //�򿪴��ڣ�COM1��9600,��У�飬8λ��һ��ֹͣλ��ͨѶ��ʱ 100
//    serial_id = serial_open("COM1", 9600, SERIAL_PARITY_NO, 8, SERIAL_STOPBIT_ONE, 100);
    if (serial_id < 0)
    {
        return 0;
    }


    return 1;
}
/*�������Ͱ�*/
static int echodemo_build_send_packet(char *send_buf, int buf_len)
{
    static unsigned int send_count=0;
    int send_len;

	send_count++;
   // rtdb_get_data_value_by_name("echodemo", "send_count", &send_count);
    send_len = sprintf(send_buf, "send packet: %u\n", send_count);
    return send_len;
}
/*ʵ�ַ��ͺͽ���*/
static int echodemo_transaction(char *send_packet, int send_len, char *recv_packet, int recv_total_len, int *recv_len, 
                             int serial_id,int timeout)
{
    if (serial_id == -1)
        return SERIAL_STATUS_PORT_ERR;
    
    if (!serial_flush(serial_id, SERIAL_FLUSH_RX|SERIAL_FLUSH_TX))
        return SERIAL_STATUS_PORT_ERR;

    if (serial_write(serial_id, send_packet, send_len) != send_len)
        return SERIAL_STATUS_PORT_ERR;

    //read packet
    *recv_len = 0;
    while(1)
    {
        int ret,i;
        int read_len;
        
        ret = serial_poll(serial_id,timeout);
        if (ret < 0)
           return SERIAL_STATUS_PORT_ERR;
        if (ret == 0)
            return SERIAL_STATUS_TIMEOUT;
        
        if (recv_total_len <= *recv_len)
            return SERIAL_STATUS_PKT_ERR;
        
        read_len = serial_read(serial_id, recv_packet+(*recv_len), recv_total_len-(*recv_len));
        if (read_len <= 0)
            return SERIAL_STATUS_PORT_ERR;

        *recv_len += read_len;
        for(i = 0; i < *recv_len; i++)
        {
            if (recv_packet[i] == '\n')
            {
                return SERIAL_STATUS_OK;
            }
        }
    }
    return SERIAL_STATUS_PORT_ERR;
}

static int echodemo_resp_packet_handle(char *recv_packet, int packet_len)
{
	recv_packet[packet_len-1] = 0;
    rtdb_set_data_value_by_name("test_parm", "recv_buf", recv_packet);
    return SERIAL_STATUS_OK;
}

/*���µĽ�����һֱѭ��ִ�еĺ�����ʵ�����ݵĽ��պͷ���*/
static int echodemo_run()
{/*
    int ret, send_len, recv_len = 0;
    char send_packet_buf[PACKET_BUF_SIZE];
    char recv_packet_buf[PACKET_BUF_SIZE];
    unsigned char send_flag , recv_flag;
*/
	int count=0;
    while(1)
    {
    	debug_printf("3G_GPRS %d\n",count);
    	count++;
    	sys_sleep(1000);
    /*
        if ((send_len =echodemo_build_send_packet(send_packet_buf, sizeof(send_packet_buf))) == 0)
            return SERIAL_STATUS_PKT_ERR;
        rtdb_set_data_value_by_name("test_parm", "send_buf", send_packet_buf);
       // debug_printf("!!!!!!!!!!!!!!!!!!!!\n");
        ret = echodemo_transaction(send_packet_buf, send_len, recv_packet_buf, sizeof(recv_packet_buf), &recv_len, serial_id, 1000);
        if (ret == SERIAL_STATUS_OK)
        {
            echodemo_resp_packet_handle(recv_packet_buf, recv_len);
        }
		//rtdb_set_data_value_by_name("echodemo","status",&ret);

        sys_sleep(1000);
        rtdb_get_data_value_by_name("sys_set","send_pack_flag",&send_flag);//��ѯ�Ƿ������ݷ���
        if(send_flag == 1)
        {
			rtdb_get_data_value_by_name("sys_set","send_pack",send_packet_buf);//��������
			send_flag = 0;
			rtdb_set_data_value_by_name("sys_set","send_pack_flag",&send_flag);
			ret = send_pack(send_packet_buf);//���ݷ���
        }
        ret = recv_pack(recv_packet_buf, sizeof(recv_packet_buf), &recv_len,100);
        if(SERIAL_STATUS_TIMEOUT != ret)
        rtdb_set_data_value_by_name("test_parm","ret",&ret);
        if(recv_len != 0)
        rtdb_set_data_value_by_name("test_parm","rec_len",&recv_len);
        serial_flush(serial_id, SERIAL_FLUSH_RX);//��ս��ջ���
        if(ret == SERIAL_STATUS_OK)//�ɹ�����һ֡��Ϣ
        {
   			 rtdb_set_data_value_by_name("sys_set", "recv_pack", recv_packet_buf);
   			 recv_flag = 1;
			 rtdb_set_data_value_by_name("sys_set", "recv_pack_flag", &recv_flag);//���յ�һ֡	
			 debug_printf("recv 1 pack\n");
        }
        memset(recv_packet_buf , 0 , PACKET_BUF_SIZE);*/
    }
    
    return SERIAL_STATUS_OK;
}

static void echodemo_release()
{
    return;
}

static ctrl_io_driver_t echodemo_drive={NULL, "echodemo", echodemo_init, echodemo_run, echodemo_release};

int module_init(char *params)
{
			
    control_io_register_driver(&echodemo_drive);
    return 1;
}


void module_exit()
{
}

/*��У��*/
static int check_sum(char *recv_packet , int pack_len)
{
	int i=0;
	unsigned char check_value=0;
	for(i=4;i<pack_len-3;i++)
	{
		check_value += recv_packet[i];
	}
	if(check_value == recv_packet[pack_len-3])
	{
		return 1;
	}
	else
	{
		#if debug
		return 1;
		#endif
		return 0;
	}
}

/*function:ʵ�����ݵĽ��պ����ݵĳ�������
input: recv_packet�������ݷ���������� recv_total_len���Խ��յ�����ֽ��� timeout ��ʱ
output: ��ǰ��������״̬��SERIAL_STATUS_OK �ɹ�����һ֡����
*/
static int recv_pack(char *recv_packet, int recv_total_len, int *recv_len,int timeout)
{
	// int recv_len=0;//recv_packet�н��յ����ֽ���
	 int pack_len=0;//���հ����ܳ���
	 *recv_len = 0;
    while(1)
    {
        int ret,i;
        int read_len;
        
        ret = serial_poll(serial_id,timeout);
        if (ret < 0)
           return SERIAL_STATUS_PORT_ERR;
        if (ret == 0)
            return SERIAL_STATUS_TIMEOUT;
        
        read_len = serial_read(serial_id, recv_packet + *recv_len, recv_total_len-(*recv_len));
        if (read_len <= 0)//δ�յ�����
            return SERIAL_STATUS_PORT_ERR;

        *recv_len += read_len;//���ݳ���

       // return SERIAL_STATUS_OK;

        /*���ݳ�������*/
        if(recv_packet[0] != 0xa5 || recv_packet[1] != 0xa5)//��ͷ���ԣ�����������
        {
			//serial_flush(serial_id, SERIAL_FLUSH_RX);//��ս��ջ���
			return SERIAL_STATUS_PACK_ERR;
        }
        pack_len = recv_packet[2]*256 + recv_packet[3];//��ȡָ���
        pack_len = pack_len+6;//����Э�飬�����ͷβ�ĳ���
        
        if(pack_len <= *recv_len)//һ֡���ݽ������
        {
			if((recv_packet[pack_len-1] != 0x5a) || (recv_packet[pack_len-2] != 0x5a) || !check_sum(recv_packet , pack_len))//��βУ��,У���
			{
				//serial_flush(serial_id, SERIAL_FLUSH_RX);//��ս��ջ���
				return SERIAL_STATUS_PACK_ERR;				
			}
			//serial_flush(serial_id, SERIAL_FLUSH_RX);//��ս��ջ���
			return SERIAL_STATUS_OK;
        }
        if(pack_len < *recv_len)
        {
			//	serial_flush(serial_id, SERIAL_FLUSH_RX);//��ս��ջ���
			//	return SERIAL_STATUS_PACK_ERR;				
        }
    }	
}

static int send_pack(char *send_packet_buf)
{
	int send_len;
     send_len = send_packet_buf[2]*256 + send_packet_buf[3];//��ȡָ���
     send_len = send_len+6;//����Э�飬�����ͷβ�ĳ���	
     if (!serial_flush(serial_id, SERIAL_FLUSH_TX))
        return SERIAL_STATUS_PORT_ERR;

    if (serial_write(serial_id, send_packet_buf, send_len) != send_len)
        return SERIAL_STATUS_PORT_ERR;    
}

