#ifndef __FLASH_H
#define __FLASH_H			    
#include <stm32f10x.h>

/*һ������ռ��5����������һ����¼�û���Ϣ������4����¼4����ʷ��Ϣ*/
#define Sector           4096  //һ��������4K�������ݶ�д������Ϊ��λ
#define CAB_MSG_ADD   0	  //������Ϣ��ַ
#define BOX_MSG_ADD	 Sector*5 //������Ϣ��ַ��һ������ռ��һ��sector������
#define H_RECORD_ADD(x)   BOX_MSG_ADD+(x)*Sector

void SPI_Flash_Init(void);	 //FLASH��ʼ��
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash

void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_FLASH_Write_SR(u8 sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Disable(void);	//д����


//void SPI_Flash_PowerDown(void);           //�������ģʽ
//void SPI_Flash_WAKEUP(void);			  //����
#endif
