#include "file_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEEK_SET 0//�ļ���ͷ
#define SEEK_CUR 1//�ļ���ǰλ��
#define SEEK_END 2//�ļ�ĩβ

unsigned char read_file(int *size , const char *file_name)
{
	FILE *box_file;
//	int write_count;

	box_file = fopen(file_name,"r+b");//�Զ�������̬���ļ�,�ɶ���д
	if(NULL == box_file)
	return 0;
	fseek(box_file , 0, SEEK_END);//�ƶ��ļ�ָ�뵽��Ҫ��λ��
	*size=ftell(box_file);
	fclose(box_file);//�ر��ļ�
	return 1;		
}
/*���ֽ��� datafile/  ��datafile/desk1.jpg��datafile/12.jpg��������*/
unsigned char ex_name(void)
{
	//if(0 != rename("datafile/desk1.jpg" , "datafile/13.jpg")) 
//	return 0;
	if(0 != rename("datafile/12.jpg" , "datafile/desk1.jpg"))
	return 0;
//	if(0 != rename("datafile/desk1temp.jpg" , "datafile/12.jpg"))
//	return 0;
	return 1;
	
}

unsigned char copy(void)
{
	FILE *file1;
	FILE *file2;
	unsigned char buf[1024];
	unsigned int read_count,write_count;

	file1 = fopen("datafile/desk1.jpg","w+b");//�Զ�������̬���ļ�,�ɶ���д,��ո��ļ�
	file2 = fopen("datafile/12.jpg","r+b");
	if(file1 == NULL  || file2 == NULL) return 0;
	fseek(file1,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ
	fseek(file2,0,SEEK_SET);//�ƶ��ļ�ָ�뵽��λ

	while(1)//ƥ�����������Ϣ��ֱ�����
	{
		read_count = fread(buf ,  1 , 1024 , file2);//˳���ȡ
		write_count = fwrite(buf ,  1 , read_count , file1);

		if(write_count < 1024)
		{
			fclose(file1);
			fclose(file2);
			return 1;//ƥ��ʧ�ܣ���ĩβ��
		}
	}	
	
}

