#include "functionList.h"
#include "mainfunction.h"
#include "sysfunction.h"
#include "commfunction.h"

#include "stm32f10x.h"
#include "menu_cfg.h"
#include "user_cfg.h"

#include <stdlib.h>
#include <string.h>

void ProcNull(FUN_BLOCK **funBlock);

FUN_BLOCK *pfunBlock = mainFunBlock;//����һ��ȫ��ָ��,ָ������ṹ��
FUN_BLOCK *pfunSubBlock = NULL;//����һ��ר��ָ����ʱ�����ڴ��ȫ��ָ�룬�������ָ��
//DIS_SING displayFull;//����һ��ȫ�ֵ���ʾȫ������
DIS_SING mainDisolayFull = 
{MAIN_LINE1,
"",
MAIN_LINE3,
MAIN_LINE4};

/*����ṹ�����飬���������ǰ����������򣬲�����һ������*/

/*������*/
FUN_BLOCK mainFunBlock[1] =
{{&mainDisolayFull , 0 , 0 , 0 , parentFunBlock , ProcNull , NONUM}};

/*������ѡ���ܲ˵�*/
FUN_BLOCK parentFunBlock[MAX_PARENT_FUN_BLOCK] =      
{
{PARENT_FUN1"��ϵͳ����Ա" , 0 , 0 , mainFunBlock , sysFunBlock , SysEnter , NONUM},
{PARENT_FUN2"������Ա" , 0 , 0 , mainFunBlock , commFunBlock , CommEnter , NONUM},
{PARENT_FUN3"���޸��û�����" , 0 , 0 , mainFunBlock , userChangeCodeFunBlock , UserEnter , NONUM},
{PARENT_FUN4"��" , 0 , 0 , mainFunBlock , 0 , ProcNull , NONUM},
};


/*ϵͳ����Ա�µĹ��ܲ˵�
��һ������ָ���Լ�����*/
FUN_BLOCK sysFunBlock[MAX_SYS_FUN_BLOCK] = 
{
/*��ʾ����*/				  /*ǰ���*/  /*��һ������*/	 /*��һ������*/	 /*�ü��Ĺ��ܺ���*/  /*��ʾ����*/
{SYS_FUN1"���޸�ϵͳ����"  , 0 , 0 , parentFunBlock , &sysFunBlock[0]  , SysChangePassWord    , NONUM},
{SYS_FUN2"������ģʽ����"  , 0 , 0 , parentFunBlock , &sysFunBlock[1]  , SysSetWorkMod        , NONUM},
{SYS_FUN3"��������������"  , 0 , 0 , parentFunBlock , &sysFunBlock[2]  , SysSetBoxNum         , NONUM},
{SYS_FUN4"��վ������"      , 0 , 0 , parentFunBlock , &sysFunBlock[3]  , SysSetCabStation     , NONUM},
{SYS_FUN5"����ָ������"  , 0 , 0 , parentFunBlock , &sysFunBlock[4]  , SysOpenOneBox        , NONUM},
{SYS_FUN6"������������"  , 0 , 0 , parentFunBlock , &sysFunBlock[5]  , SysOpenAllBox        , NONUM},
{SYS_FUN7"���˿�����"      , 0 , 0 , parentFunBlock , &sysFunBlock[6]  , SysSetPort           , NONUM},
{SYS_FUN8"������ϵͳʱ��"  , 0 , 0 , parentFunBlock , &sysFunBlock[7]  , SysSetTime           , NONUM},
{SYS_FUN9"����ѯʹ�ü�¼"  , 0 , 0 , parentFunBlock , &sysFunBlock[8]  , SysCheckRecord       , NONUM},
{SYS_FUN10"���ָ���������" , 0 , 0 , parentFunBlock , &sysFunBlock[9]  , SysRecoveryInit      , NONUM},
{SYS_FUN11"���˳�"         , 0 , 0 , parentFunBlock , &sysFunBlock[10] , SysExit              , NONUM},
{SYS_FUN12"��"             , 0 , 0 , parentFunBlock , &sysFunBlock[11] , 0                    , NONUM},
{SYS_FUN13"��"             , 0 , 0 , parentFunBlock , &sysFunBlock[12] , 0                    , NONUM},
{SYS_FUN14"��"             , 0 , 0 , parentFunBlock , &sysFunBlock[13] , 0                    , NONUM},
{SYS_FUN15"��"             , 0 , 0 , parentFunBlock , &sysFunBlock[14] , 0                    , NONUM},
};

/*����Ա�µĹ��ܲ˵�*/
FUN_BLOCK commFunBlock[MAX_COMM_FUN_BLOCK] = 
{															  
/*��ʾ����*/				  /*ǰ���*/ /*��һ������*/		 /*��һ������*/   	 /*�ü��Ĺ��ܺ���*/  /*��ʾ����*/
{COMM_FUN1"���޸Ĺ���Ա����"  , 0 , 0 , &parentFunBlock[1] , &commFunBlock[0] , CommChangePassWord , NONUM},
{COMM_FUN2"��ע���û�"        , 0 , 0 , &parentFunBlock[1] , &commFunBlock[1] , CommRegistUser     , NONUM},
{COMM_FUN3"��ע���û�"        , 0 , 0 , &parentFunBlock[1] , &commFunBlock[2] , CommCancleUser     , NONUM},
{COMM_FUN4"����ָ������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[3] , SysOpenOneBox      , NONUM},
{COMM_FUN5"������������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[4] , SysOpenAllBox      , NONUM},
{COMM_FUN6"�������������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[5] , CommClearAllBox    , NONUM},
{COMM_FUN7"������ָ������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[6] , CommLockOneBox     , NONUM},
{COMM_FUN8"������ָ������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[7] , CommUnLockOneBox   , NONUM},
{COMM_FUN9"��������������"    , 0 , 0 , &parentFunBlock[1] , &commFunBlock[8] , CommLockAllBox     , NONUM},
{COMM_FUN10"��������������"   , 0 , 0 , &parentFunBlock[1] , &commFunBlock[9] , CommUnLockAllBox   , NONUM},
{COMM_FUN11"����ѯʹ�ü�¼"   , 0 , 0 , &parentFunBlock[1] , &commFunBlock[10] , SysCheckRecord    , NONUM},
{COMM_FUN12"���˳�"           , 0 , 0 , &parentFunBlock[1] , &commFunBlock[11] , SysExit           , NONUM},
{COMM_FUN13"��"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[12] , 0 , NONUM},
{COMM_FUN14"��"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[13] , 0 , NONUM},
{COMM_FUN15"��"               , 0 , 0 , &parentFunBlock[1] , &commFunBlock[14] , 0 , NONUM},
};

/*�û��������빦�ܲ˵�*/
FUN_BLOCK userChangeCodeFunBlock[1] = 
{0 , 0 , 0 , mainFunBlock , mainFunBlock , 0 , ZINUM};


/*
�Զ�����ṹ�壬������˫����������ͷ��βΪ�ձȽϴ���99��Ϊ�յĵĲ���������
input��FUN_BLOCK **funBlock�ṹ������ ��length ����Ԫ�ظ���
*/
void AdjustBlock(FUN_BLOCK *funBlock , u8 length)
{
 	u8 *numbuf , *tempbuf;
	FUN_BLOCK *funBlocktemp;
	u8 i,j,temp,min_value=0,min_value1=0;

	numbuf = malloc(length);
	tempbuf = numbuf;
	for(funBlocktemp = funBlock ; funBlocktemp < funBlock + length ; funBlocktemp++)//��ȡ�������ӵı��
	{
		*tempbuf++ = (u8)atoi((char const *)funBlocktemp->current_display);
	}
	/*�ҳ���Сֵ*/
	for(i=0;i<length;i++)
	{
		if(numbuf[i] == 1)
		{
			min_value = i;
			break;
		}
	}
	pfunBlock = &funBlock[i];//ȫ��ָ��ָ������ͷ

	temp = 100;
	/*����length*length�Σ��ٲ��޸������ǰ���°���С�����˳���ҳ�����ֵ*/
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;)
		{
			/*�ҳ����ϴ�ֵ�����һ��*/
			if(numbuf[j] > numbuf[min_value])
			{
				if(temp > numbuf[j] - numbuf[min_value])
				{
					temp = numbuf[j] - numbuf[min_value];
					min_value1 = j;
				}
			}
			j++;
		}//end for(j=0;j<length;)
		if(numbuf[min_value1] > 20)  break;//��������Ҫָ���ֱֵ���˳�ѭ��
		if(min_value != min_value1)
		{
			funBlock[min_value].pnext_block = &funBlock[min_value1];//ǰ���ָ��ָ�����
			funBlock[min_value1].plast_block = &funBlock[min_value];//�����ָ��ָ��ǰ��
		}
		min_value = min_value1;
		temp = 100;
	}//end for(i=0;i<length;i++)
	free(numbuf);
}

/*
��ִ�к�������Ӧenter��,����ָ��ָ���ָ�룬�����������Ӻ������޸�ָ��
��Ҫע����ʽ���ȼ�������
*/
void ProcNull(FUN_BLOCK **funBlock)
{
	*funBlock = (*funBlock)->sub_block;
}


