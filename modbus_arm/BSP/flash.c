#include "flash.h" 
#include "spi.h"
#include <string.h>
//W25X64��д
#define FLASH_ID 0XEF16
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg	0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

#define  SPI_FLASH_CS_H   GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define  SPI_FLASH_CS_L   GPIO_ResetBits(GPIOA,GPIO_Pin_4)

static void Delay(vu32 nCount);
static u16  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
static u8	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
static void SPI_FLASH_Write_Enable(void);  //дʹ�� 
static void SPI_Flash_Erase_Sector(u32 Dst_Addr);//��������
static void SPI_Flash_Wait_Busy(void);           //�ȴ�����

//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25X16
//����Ϊ2M�ֽ�,����32��Block,512��Sector 

static void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}

void SPI_Flash_Init(void)	//��ʼ��SPI
{
	SPIx_Init();//��ʼ��SPI FLASH��IO��
		while(SPI_Flash_ReadID()!=FLASH_ID)//��ⲻ��W25X16
  {	
		Delay(0xaFFF);
		Delay(0xaFFF);
	}		   
}  

//��ȡSPI_FLASH��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS_L;                            //ʹ������   
	SPIx_ReadWriteByte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPIx_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     
	return byte;   
}

//дSPI_FLASH״̬�Ĵ���
void SPI_FLASH_Write_SR(u8 sr)   
{   
	SPI_FLASH_CS_L;                            //ʹ������   
	SPIx_ReadWriteByte(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	SPIx_ReadWriteByte(sr);               //д��һ���ֽ�  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
}

//SPI_FLASHдʹ��
void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_WriteEnable);      //����дʹ��  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
}

//SPI_FLASHд��ֹ	
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_WriteDisable);     //����д��ָֹ��    
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
}

//��ȡоƬID W25X16��ID:0XEF14
static u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS_L;				    
	SPIx_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	SPI_FLASH_CS_H;				    
	return Temp;
}

//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	register u16 i;    												    
	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_ReadData);         //���Ͷ�ȡ����   
    SPIx_ReadWriteByte((u8)((ReadAddr)>>16));  //����24bit��ַ    
    SPIx_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPIx_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPIx_ReadWriteByte(0XFF);   //ѭ������  
    }
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
}

//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
static void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_PageProgram);      //����дҳ����   
    SPIx_ReadWriteByte((u8)((WriteAddr)>>16)); //����24bit��ַ    
    SPIx_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPIx_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPIx_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ 
	SPI_Flash_Wait_Busy();					   //�ȴ�д�����
}
 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 
 
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)  		   
u8 SPI_FLASH_BUF[4096];
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
  
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;  
	secpos=WriteAddr/4096;//������ַ 0~511 for w25x16
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			SPI_Flash_Erase_Sector(secpos);//�����������
			/*for(i=0;i<secremain;i++)	   //����
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			} */
			memcpy(SPI_FLASH_BUF+secoff , pBuffer , secremain);
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//д����������  

		}else SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	 	 
}

//��������оƬ
//��Ƭ����ʱ��:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//�ȴ�ʱ�䳬��...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_ChipErase);        //����Ƭ��������  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
	SPI_Flash_Wait_Busy();   				   //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ��ɽ��������ʱ��:150ms
static void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
	Dst_Addr*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_SectorErase);      //������������ָ�� 
    SPIx_ReadWriteByte((u8)((Dst_Addr)>>16));  //����24bit��ַ    
    SPIx_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPIx_ReadWriteByte((u8)Dst_Addr);  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
    SPI_Flash_Wait_Busy();   				   //�ȴ��������
}  
//�ȴ�����
static void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
/*//�������ģʽ
void SPI_Flash_PowerDown(void)   
{ 
  	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_PowerDown);        //���͵�������  
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TPD  
}   
//����
void SPI_Flash_WAKEUP(void)   
{  
  	SPI_FLASH_CS_L;                            //ʹ������   
    SPIx_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS_H;                            //ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TRES1
}  */ 











