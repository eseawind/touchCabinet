/*
 * This file is automatically generated by func_gen.c,don't edit
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lincon.h"
#include "linconhmi.h"
#include "userfunc.h"

#ifndef HMI_GEN_FUNC_FILE
static void widget_button_5_click(void);
static void widget_button_4_click(void);
static void widget_button_3_click(void);
static void widget_button_2_click(void);
static void widget_button_click(void);
static void widget_window_open(void);
static void widget_window_close(void);

hmi_widget_func_t hmi_window_77696E5F696E7075745F706E756D5F74797065_event_funcs[]={
{"button_5_click",(void *)widget_button_5_click},
{"button_4_click",(void *)widget_button_4_click},
{"button_3_click",(void *)widget_button_3_click},
{"button_2_click",(void *)widget_button_2_click},
{"button_click",(void *)widget_button_click},
{"window_open",(void *)widget_window_open},
{"window_close",(void *)widget_window_close},
{NULL,NULL}
};

static void widget_button_5_click(void)
{
	u8 __hmi_var_26 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_min"));
	u8 __old___hmi_var_26 = __hmi_var_26;
	u8 __hmi_var_27 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_mid"));
	u8 __old___hmi_var_27 = __hmi_var_27;
	u8 __hmi_var_28 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_max"));
	u8 __old___hmi_var_28 = __hmi_var_28;
	u8 __hmi_var_29 = (*(u8 *)hmidb_get_data_value("box_msg.station_num"));
	u8 __old___hmi_var_29 = __hmi_var_29;
	char __hmi_var_30 = (*(char *)hmidb_get_data_value("box_msg.type"));
	char __old___hmi_var_30 = __hmi_var_30;
	char * __hmi_var_31 = ((char *)hmidb_get_data_value("picture_ctrl.win_tip"));
		{
#line 1 "�ؼ�:button_5,�¼�:click"
//�ı���ʵ״̬��ͬʱ���Һͷ����������
BOX_MSG box_info;
__hmi_var_26 = 0;
__hmi_var_27 = 0;
__hmi_var_28 = 1;

//box_type = ''
if(1 == read_box_info_status_type(BOX_IDLE , BOX_TYPE_MAX , &box_info))
{
    //��ʣ�������
    __hmi_var_29 = box_info.station_num;//��¼���к�
    __hmi_var_30 = BOX_TYPE_MAX;
}
else
{
    strcpy(__hmi_var_31 , "�޸��ͺŵ����ӿ���");
    __hmi_var_28 = 0;
    {
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_31);
	if(__old___hmi_var_30 != __hmi_var_30)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_30);
		__old___hmi_var_30 = __hmi_var_30;
	}
	if(__old___hmi_var_29 != __hmi_var_29)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_29);
		__old___hmi_var_29 = __hmi_var_29;
	}
	if(__old___hmi_var_28 != __hmi_var_28)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_28);
		__old___hmi_var_28 = __hmi_var_28;
	}
	if(__old___hmi_var_27 != __hmi_var_27)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_27);
		__old___hmi_var_27 = __hmi_var_27;
	}
	if(__old___hmi_var_26 != __hmi_var_26)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_26);
		__old___hmi_var_26 = __hmi_var_26;
	}
}

    hmi_window_show("win_tip");
}

	}
{
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_31);
	if(__old___hmi_var_30 != __hmi_var_30)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_30);
	}
	if(__old___hmi_var_29 != __hmi_var_29)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_29);
	}
	if(__old___hmi_var_28 != __hmi_var_28)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_28);
	}
	if(__old___hmi_var_27 != __hmi_var_27)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_27);
	}
	if(__old___hmi_var_26 != __hmi_var_26)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_26);
	}
}
}

static void widget_button_4_click(void)
{
	u8 __hmi_var_33 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_min"));
	u8 __old___hmi_var_33 = __hmi_var_33;
	u8 __hmi_var_34 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_mid"));
	u8 __old___hmi_var_34 = __hmi_var_34;
	u8 __hmi_var_35 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_max"));
	u8 __old___hmi_var_35 = __hmi_var_35;
	u8 __hmi_var_36 = (*(u8 *)hmidb_get_data_value("box_msg.station_num"));
	u8 __old___hmi_var_36 = __hmi_var_36;
	char __hmi_var_37 = (*(char *)hmidb_get_data_value("box_msg.type"));
	char __old___hmi_var_37 = __hmi_var_37;
	char * __hmi_var_38 = ((char *)hmidb_get_data_value("picture_ctrl.win_tip"));
		{
#line 1 "�ؼ�:button_4,�¼�:click"
//�ı���ʵ״̬��ͬʱ���Һͷ����������
BOX_MSG box_info;
__hmi_var_33 = 0;
__hmi_var_34 = 1;
__hmi_var_35 = 0;

//box_type = ''
if(1 == read_box_info_status_type(BOX_IDLE , BOX_TYPE_MID , &box_info))
{
    //��ʣ�������
    __hmi_var_36 = box_info.station_num;//��¼���к�
    __hmi_var_37 = BOX_TYPE_MID;
}
else
{
    strcpy(__hmi_var_38 , "�޸��ͺŵ����ӿ���");
    __hmi_var_34 = 0;
    {
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_38);
	if(__old___hmi_var_37 != __hmi_var_37)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_37);
		__old___hmi_var_37 = __hmi_var_37;
	}
	if(__old___hmi_var_36 != __hmi_var_36)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_36);
		__old___hmi_var_36 = __hmi_var_36;
	}
	if(__old___hmi_var_35 != __hmi_var_35)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_35);
		__old___hmi_var_35 = __hmi_var_35;
	}
	if(__old___hmi_var_34 != __hmi_var_34)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_34);
		__old___hmi_var_34 = __hmi_var_34;
	}
	if(__old___hmi_var_33 != __hmi_var_33)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_33);
		__old___hmi_var_33 = __hmi_var_33;
	}
}

    hmi_window_show("win_tip");
}

	}
{
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_38);
	if(__old___hmi_var_37 != __hmi_var_37)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_37);
	}
	if(__old___hmi_var_36 != __hmi_var_36)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_36);
	}
	if(__old___hmi_var_35 != __hmi_var_35)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_35);
	}
	if(__old___hmi_var_34 != __hmi_var_34)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_34);
	}
	if(__old___hmi_var_33 != __hmi_var_33)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_33);
	}
}
}

static void widget_button_3_click(void)
{
	u8 __hmi_var_40 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_min"));
	u8 __old___hmi_var_40 = __hmi_var_40;
	u8 __hmi_var_41 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_mid"));
	u8 __old___hmi_var_41 = __hmi_var_41;
	u8 __hmi_var_42 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_max"));
	u8 __old___hmi_var_42 = __hmi_var_42;
	u8 __hmi_var_43 = (*(u8 *)hmidb_get_data_value("box_msg.station_num"));
	u8 __old___hmi_var_43 = __hmi_var_43;
	char __hmi_var_44 = (*(char *)hmidb_get_data_value("box_msg.type"));
	char __old___hmi_var_44 = __hmi_var_44;
	char * __hmi_var_45 = ((char *)hmidb_get_data_value("picture_ctrl.win_tip"));
		{
#line 1 "�ؼ�:button_3,�¼�:click"
//�ı���ʵ״̬��ͬʱ���Һͷ����������
BOX_MSG box_info;
__hmi_var_40 = 1;
__hmi_var_41 = 0;
__hmi_var_42 = 0;

//box_type = ''
if(1 == read_box_info_status_type(BOX_IDLE , BOX_TYPE_MIN , &box_info))
{
    //��ʣ�������
    __hmi_var_43 = box_info.station_num;//��¼���к�
    __hmi_var_44 = BOX_TYPE_MIN;
}
else
{
    strcpy(__hmi_var_45 , "�޸��ͺŵ����ӿ���");
    __hmi_var_40 = 0;
    {
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_45);
	if(__old___hmi_var_44 != __hmi_var_44)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_44);
		__old___hmi_var_44 = __hmi_var_44;
	}
	if(__old___hmi_var_43 != __hmi_var_43)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_43);
		__old___hmi_var_43 = __hmi_var_43;
	}
	if(__old___hmi_var_42 != __hmi_var_42)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_42);
		__old___hmi_var_42 = __hmi_var_42;
	}
	if(__old___hmi_var_41 != __hmi_var_41)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_41);
		__old___hmi_var_41 = __hmi_var_41;
	}
	if(__old___hmi_var_40 != __hmi_var_40)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_40);
		__old___hmi_var_40 = __hmi_var_40;
	}
}

    hmi_window_show("win_tip");
}

	}
{
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_45);
	if(__old___hmi_var_44 != __hmi_var_44)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_44);
	}
	if(__old___hmi_var_43 != __hmi_var_43)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_43);
	}
	if(__old___hmi_var_42 != __hmi_var_42)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_42);
	}
	if(__old___hmi_var_41 != __hmi_var_41)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_41);
	}
	if(__old___hmi_var_40 != __hmi_var_40)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_40);
	}
}
}

static void widget_button_2_click(void)
{
	{
#line 1 "�ؼ�:button_2,�¼�:click"
hmi_window_hide("win_input_pnum_type");
	}
{
}
}

static void widget_button_click(void)
{
	u8 __hmi_var_46 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_min"));
	u8 __old___hmi_var_46 = __hmi_var_46;
	u8 __hmi_var_47 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_mid"));
	u8 __old___hmi_var_47 = __hmi_var_47;
	u8 __hmi_var_48 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_max"));
	u8 __old___hmi_var_48 = __hmi_var_48;
	char * __hmi_var_49 = ((char *)hmidb_get_data_value("picture_ctrl.win_tip"));
		u8 __hmi_var_50 = (*(u8 *)hmidb_get_data_value("box_msg.station_num"));
	u8 __old___hmi_var_50 = __hmi_var_50;
	char * __hmi_var_51 = ((char *)hmidb_get_data_value("box_msg.send_num"));
		char * __hmi_var_52 = ((char *)hmidb_get_data_value("box_msg.send_id"));
		char * __hmi_var_53 = ((char *)hmidb_get_data_value("box_msg.user_phnum"));
		char __hmi_var_54 = (*(char *)hmidb_get_data_value("box_msg.type"));
	char __old___hmi_var_54 = __hmi_var_54;
	u8 * __hmi_var_55 = ((u8 *)hmidb_get_data_value("sys_set.send_pack"));
		char * __hmi_var_56 = ((char *)hmidb_get_data_value("sys_set.station_add"));
		u8 __hmi_var_57 = (*(u8 *)hmidb_get_data_value("sys_set.send_pack_flag"));
	u8 __old___hmi_var_57 = __hmi_var_57;
	u8 __hmi_var_58 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_save_next_flag"));
	u8 __old___hmi_var_58 = __hmi_var_58;
	char * __hmi_var_59 = ((char *)hmidb_get_data_value("picture_ctrl.win_wait_tip"));
		u8 __hmi_var_60 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_wait_sw"));
	u8 __old___hmi_var_60 = __hmi_var_60;
	u8 __hmi_var_61 = (*(u8 *)hmidb_get_data_value("sys_set.user_ic_enable_flag"));
	u8 __old___hmi_var_61 = __hmi_var_61;
	{
#line 1 "�ؼ�:button,�¼�:click"
//��������Ϣ�Ƿ��������������ݵ������������ȴ�����������
BOX_MSG box_info;
int data_len;
unsigned char data_buf[128];
if((__hmi_var_46 == 0) && (__hmi_var_47 == 0) && (__hmi_var_48 == 0))
{
    strcpy(__hmi_var_49 , "��ѡ����������");
    {
	if(__old___hmi_var_61 != __hmi_var_61)
	{
		hmidb_set_data_value("sys_set.user_ic_enable_flag",&__hmi_var_61);
		__old___hmi_var_61 = __hmi_var_61;
	}
	if(__old___hmi_var_60 != __hmi_var_60)
	{
		hmidb_set_data_value("picture_ctrl.win_wait_sw",&__hmi_var_60);
		__old___hmi_var_60 = __hmi_var_60;
	}
		hmidb_set_data_value("picture_ctrl.win_wait_tip",__hmi_var_59);
	if(__old___hmi_var_58 != __hmi_var_58)
	{
		hmidb_set_data_value("picture_ctrl.win_save_next_flag",&__hmi_var_58);
		__old___hmi_var_58 = __hmi_var_58;
	}
	if(__old___hmi_var_57 != __hmi_var_57)
	{
		hmidb_set_data_value("sys_set.send_pack_flag",&__hmi_var_57);
		__old___hmi_var_57 = __hmi_var_57;
	}
		hmidb_set_data_value("sys_set.station_add",__hmi_var_56);
		hmidb_set_data_value("sys_set.send_pack",__hmi_var_55);
	if(__old___hmi_var_54 != __hmi_var_54)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_54);
		__old___hmi_var_54 = __hmi_var_54;
	}
		hmidb_set_data_value("box_msg.user_phnum",__hmi_var_53);
		hmidb_set_data_value("box_msg.send_id",__hmi_var_52);
		hmidb_set_data_value("box_msg.send_num",__hmi_var_51);
	if(__old___hmi_var_50 != __hmi_var_50)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_50);
		__old___hmi_var_50 = __hmi_var_50;
	}
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_49);
	if(__old___hmi_var_48 != __hmi_var_48)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_48);
		__old___hmi_var_48 = __hmi_var_48;
	}
	if(__old___hmi_var_47 != __hmi_var_47)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_47);
		__old___hmi_var_47 = __hmi_var_47;
	}
	if(__old___hmi_var_46 != __hmi_var_46)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_46);
		__old___hmi_var_46 = __hmi_var_46;
	}
}

    hmi_window_show("win_tip");
    return;
}

read_box_info_station_num(__hmi_var_50 , &box_info);
//д����Ҫ���ݵ��û���Ϣ,�˻�Ա���ţ������ţ��û��ֻ��ţ������ͺ�
memset(box_info.send_num , 0xff , SEND_NUM_LENGTH);
memcpy(box_info.send_num , __hmi_var_51 , strlen(__hmi_var_51));
memset(box_info.send_id , 0xff , SENDID_LENGTH);
memcpy(box_info.send_id , __hmi_var_52 , strlen(__hmi_var_52));
memset(box_info.user_phnum , 0xff , USER_PHNUM_LENGTH);
memcpy(box_info.user_phnum , __hmi_var_53 , strlen(__hmi_var_53));//�����û��ֻ���
box_info.type = __hmi_var_54;//�����ͺ�
data_len = package_user_data_pack(data_buf , OPEN_ASK , &box_info);//��װ���ݲ���
package_send_pack(__hmi_var_55 , __hmi_var_56 ,SAVE_USER_INFO , data_buf , data_len);//��װ����
__hmi_var_57 = 1;//���Ͱ�
__hmi_var_58 = 1;

hmi_window_hide("win_input_pnum_type");
hmi_window_hide("win_input_send_tm");
strcpy(__hmi_var_59,"��̨�����У������ĵȴ�");
__hmi_var_60 = 0;
//__hmi_var_61 = 1;
{
	if(__old___hmi_var_61 != __hmi_var_61)
	{
		hmidb_set_data_value("sys_set.user_ic_enable_flag",&__hmi_var_61);
		__old___hmi_var_61 = __hmi_var_61;
	}
	if(__old___hmi_var_60 != __hmi_var_60)
	{
		hmidb_set_data_value("picture_ctrl.win_wait_sw",&__hmi_var_60);
		__old___hmi_var_60 = __hmi_var_60;
	}
		hmidb_set_data_value("picture_ctrl.win_wait_tip",__hmi_var_59);
	if(__old___hmi_var_58 != __hmi_var_58)
	{
		hmidb_set_data_value("picture_ctrl.win_save_next_flag",&__hmi_var_58);
		__old___hmi_var_58 = __hmi_var_58;
	}
	if(__old___hmi_var_57 != __hmi_var_57)
	{
		hmidb_set_data_value("sys_set.send_pack_flag",&__hmi_var_57);
		__old___hmi_var_57 = __hmi_var_57;
	}
		hmidb_set_data_value("sys_set.station_add",__hmi_var_56);
		hmidb_set_data_value("sys_set.send_pack",__hmi_var_55);
	if(__old___hmi_var_54 != __hmi_var_54)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_54);
		__old___hmi_var_54 = __hmi_var_54;
	}
		hmidb_set_data_value("box_msg.user_phnum",__hmi_var_53);
		hmidb_set_data_value("box_msg.send_id",__hmi_var_52);
		hmidb_set_data_value("box_msg.send_num",__hmi_var_51);
	if(__old___hmi_var_50 != __hmi_var_50)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_50);
		__old___hmi_var_50 = __hmi_var_50;
	}
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_49);
	if(__old___hmi_var_48 != __hmi_var_48)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_48);
		__old___hmi_var_48 = __hmi_var_48;
	}
	if(__old___hmi_var_47 != __hmi_var_47)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_47);
		__old___hmi_var_47 = __hmi_var_47;
	}
	if(__old___hmi_var_46 != __hmi_var_46)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_46);
		__old___hmi_var_46 = __hmi_var_46;
	}
}

hmi_window_show("win_wait_tip");

debug_printf("box_msg.send_id = %s\n",__hmi_var_52);
debug_printf("box_msg.user_phnum = %s\n",__hmi_var_53);
debug_printf("box_msg = %c\n",__hmi_var_54);



	}
{
	if(__old___hmi_var_61 != __hmi_var_61)
	{
		hmidb_set_data_value("sys_set.user_ic_enable_flag",&__hmi_var_61);
	}
	if(__old___hmi_var_60 != __hmi_var_60)
	{
		hmidb_set_data_value("picture_ctrl.win_wait_sw",&__hmi_var_60);
	}
		hmidb_set_data_value("picture_ctrl.win_wait_tip",__hmi_var_59);
	if(__old___hmi_var_58 != __hmi_var_58)
	{
		hmidb_set_data_value("picture_ctrl.win_save_next_flag",&__hmi_var_58);
	}
	if(__old___hmi_var_57 != __hmi_var_57)
	{
		hmidb_set_data_value("sys_set.send_pack_flag",&__hmi_var_57);
	}
		hmidb_set_data_value("sys_set.station_add",__hmi_var_56);
		hmidb_set_data_value("sys_set.send_pack",__hmi_var_55);
	if(__old___hmi_var_54 != __hmi_var_54)
	{
		hmidb_set_data_value("box_msg.type",&__hmi_var_54);
	}
		hmidb_set_data_value("box_msg.user_phnum",__hmi_var_53);
		hmidb_set_data_value("box_msg.send_id",__hmi_var_52);
		hmidb_set_data_value("box_msg.send_num",__hmi_var_51);
	if(__old___hmi_var_50 != __hmi_var_50)
	{
		hmidb_set_data_value("box_msg.station_num",&__hmi_var_50);
	}
		hmidb_set_data_value("picture_ctrl.win_tip",__hmi_var_49);
	if(__old___hmi_var_48 != __hmi_var_48)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_48);
	}
	if(__old___hmi_var_47 != __hmi_var_47)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_47);
	}
	if(__old___hmi_var_46 != __hmi_var_46)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_46);
	}
}
}

static void widget_window_open(void)
{
	u8 __hmi_var_62 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_min"));
	u8 __old___hmi_var_62 = __hmi_var_62;
	u8 __hmi_var_63 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_mid"));
	u8 __old___hmi_var_63 = __hmi_var_63;
	u8 __hmi_var_64 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_type_max"));
	u8 __old___hmi_var_64 = __hmi_var_64;
	char * __hmi_var_65 = ((char *)hmidb_get_data_value("box_msg.user_phnum"));
		{
#line 1 "�ؼ�:window,�¼�:open"
__hmi_var_62 = 0;
__hmi_var_63 = 0;
__hmi_var_64 = 0;
memset(__hmi_var_65 , 0 , 25);

	}
{
		hmidb_set_data_value("box_msg.user_phnum",__hmi_var_65);
	if(__old___hmi_var_64 != __hmi_var_64)
	{
		hmidb_set_data_value("picture_ctrl.win_type_max",&__hmi_var_64);
	}
	if(__old___hmi_var_63 != __hmi_var_63)
	{
		hmidb_set_data_value("picture_ctrl.win_type_mid",&__hmi_var_63);
	}
	if(__old___hmi_var_62 != __hmi_var_62)
	{
		hmidb_set_data_value("picture_ctrl.win_type_min",&__hmi_var_62);
	}
}
}

static void widget_window_close(void)
{
	u8 __hmi_var_66 = (*(u8 *)hmidb_get_data_value("sys_set.send_tm_enable_flag"));
	u8 __old___hmi_var_66 = __hmi_var_66;
	u8 __hmi_var_67 = (*(u8 *)hmidb_get_data_value("picture_ctrl.win_save_next_flag"));
	u8 __old___hmi_var_67 = __hmi_var_67;
	{
#line 1 "�ؼ�:window,�¼�:close"
__hmi_var_66 = 0;//��ֹ�����ȡ
__hmi_var_67 = 0;//��ֹ���ּ�������
hmi_window_hide("TextKeyboard6");

	}
{
	if(__old___hmi_var_67 != __hmi_var_67)
	{
		hmidb_set_data_value("picture_ctrl.win_save_next_flag",&__hmi_var_67);
	}
	if(__old___hmi_var_66 != __hmi_var_66)
	{
		hmidb_set_data_value("sys_set.send_tm_enable_flag",&__hmi_var_66);
	}
}
}

#endif