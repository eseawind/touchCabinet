/*�û��������������ļ������������û��ͷ���Ա��صĲ�������Ҫ���������뿪��ȡ�ˢID��ֱ�ӿ���ȡ�ˢ�˻�����ֱ�ӿ���*/
#include "lincon.h"
#include "box_info.h"

void test_display(char *outbuf , unsigned char *inbuf , int len)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		if(inbuf[i]<'0' || inbuf[i]>'9')
		{
			outbuf[i] = '*';
		}else
		{
			outbuf[i] = inbuf[i];
		}
	}
}



