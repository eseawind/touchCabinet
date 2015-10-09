/*-----------------------------------------------
  ���ƣ�IICЭ�� 
  ��̳��www.doflye.net
  ��д��shifang
  �޸ģ���
  ���ݣ������ǲ��������ʱ�ķ�������SCL����,�̶Ը߾���Ƶ��Ҫ�� һ�����޸�....(������1us����
		����,������Ƶ��ҪС��12MHZ)
------------------------------------------------*/  
  
              
#include "CATi2c.h"


#define  _Nop()   delay()  //�����ָ��

#define SDA_H  GPIO_SetBits(GPIO_SDA,SDA_PIN) 
#define SDA_L  GPIO_ResetBits(GPIO_SDA,SDA_PIN)
#define SCL_H  GPIO_SetBits(GPIO_SCL,SCL_PIN) 
#define SCL_L  GPIO_ResetBits(GPIO_SCL,SCL_PIN)
#define SDA_IN GPIO_ReadInputDataBit(GPIO_SDA, SDA_PIN)

#define EXT1_SDA_H  GPIO_SetBits(EXT1_GPIO_SDA,EXT1_SDA_PIN) 
#define EXT1_SDA_L  GPIO_ResetBits(EXT1_GPIO_SDA,EXT1_SDA_PIN)
#define EXT1_SCL_H  GPIO_SetBits(EXT1_GPIO_SCL,EXT1_SCL_PIN) 
#define EXT1_SCL_L  GPIO_ResetBits(EXT1_GPIO_SCL,EXT1_SCL_PIN)
#define EXT1_SDA_IN GPIO_ReadInputDataBit(EXT1_GPIO_SDA, EXT1_SDA_PIN)

#define EXT2_SDA_H  GPIO_SetBits(EXT2_GPIO_SDA,EXT2_SDA_PIN) 
#define EXT2_SDA_L  GPIO_ResetBits(EXT2_GPIO_SDA,EXT2_SDA_PIN)
#define EXT2_SCL_H  GPIO_SetBits(EXT2_GPIO_SCL,EXT2_SCL_PIN) 
#define EXT2_SCL_L  GPIO_ResetBits(EXT2_GPIO_SCL,EXT2_SCL_PIN)
#define EXT2_SDA_IN GPIO_ReadInputDataBit(EXT2_GPIO_SDA, EXT2_SDA_PIN)
                         
u8 ack;	              //Ӧ���־λ

/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void EXT1_Start_I2c(void);
/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void EXT1_Stop_I2c(void);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  EXT1_SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
static void  EXT1_SendByte(u16 c);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  EXT1_RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
static unsigned char  EXT1_RcvByte(void);
/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void EXT1_Ack_I2c(void);
----------------------------------------------------------------*/
static void EXT1_Ack_I2c(void);
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void EXT1_NoAck_I2c(void);
----------------------------------------------------------------*/
static void EXT1_NoAck_I2c(void);


/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void EXT2_Start_I2c(void);
/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void EXT2_Stop_I2c(void);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  EXT2_SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
static void  EXT2_SendByte(u16 c);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  EXT2_RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
static unsigned char  EXT2_RcvByte(void);
/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void EXT2_Ack_I2c(void);
----------------------------------------------------------------*/
static void EXT2_Ack_I2c(void);
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void EXT2_NoAck_I2c(void);
----------------------------------------------------------------*/
static void EXT2_NoAck_I2c(void);


/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void Start_I2c(void);
/*------------------------------------------------
                    ��������
------------------------------------------------*/
static void Stop_I2c(void);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
static void  SendByte(u16 c);
/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
static unsigned char  RcvByte(void);
/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void Ack_I2c(void);
----------------------------------------------------------------*/
static void Ack_I2c(void);
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void NoAck_I2c(void);
----------------------------------------------------------------*/
static void NoAck_I2c(void);

static void delay(void)
{
	u16 i = 0x0f;
	while(i--);
}

void WriteCATData(u8 add, u8 subadd ,u16 dat)//16λ����������Ч
{
	dat = ~dat;//��λȡ��
   Start_I2c();               //��������
   SendByte(add);             //����������ַ
     if(ack==0)return;
   SendByte(subadd);            //���������ӵ�ַ
     if(ack==0)return;
   SendByte((u8)(dat&0x00ff));             //��������1
     if(ack==0)return;
   SendByte((u8)((dat&0xff00)>>8));             //��������2
     if(ack==0)return;
   Stop_I2c();  
}			 

u16 ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   Start_I2c();               //��������
   SendByte(add);             //����������ַ
     if(ack==0)return(0);
   SendByte(0);             //����������ַ
     if(ack==0)return(0);

	Start_I2c();               //��������
	SendByte(add+1);             //����������ַ
	  if(ack==0)return(0);
   Val1=RcvByte();
   Ack_I2c();                 //����Ӧ��λ

   Val2=RcvByte();
   NoAck_I2c();                 //���ͷ�Ӧ��λ
   Stop_I2c();                  //��������

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 

void I2CIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);

	/* PA1,0 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //���ùܽ�Ϊ���ù��ܿ�©���
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //I2C�ӿ�ʹ�õ�GPIO�ܽų�ʼ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG ,ENABLE);

	/* ��չ����PG13,14,8,9 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //���ùܽ�Ϊ���ù��ܿ�©���
	GPIO_Init(GPIOG, &GPIO_InitStructure);          //I2C�ӿ�ʹ�õ�GPIO�ܽų�ʼ��
}

void CAT955Init(void)
{
  I2CIOInit();
  WriteCATData(AddCATlock,0x06,0xffff);//����CATlock����Ϊ���
  WriteCATData(AddCATlock,0x02,0);//����������

  WriteCATData(AddCATdoor,0x06,0);//����CATdoor����Ϊ����
  WriteCATData(AddCATstatus,0x06,0);//����CATstatus����Ϊ����
  WriteCATData(AddCATdoor,0x04,0);//����CATdoor���Է�ת
  WriteCATData(AddCATstatus,0x04,0);//����CATstatus���Է�ת
/*��չ����*/
  EXT1_WriteCATData(EXT1_AddCATlock1,0x06,0xffff);//����CATlock����Ϊ���
  EXT1_WriteCATData(EXT1_AddCATlock1,0x02,0);//����������

  EXT1_WriteCATData(EXT1_AddCATdoor1,0x06,0);//����CATdoor����Ϊ����
  EXT1_WriteCATData(EXT1_AddCATstatus1,0x06,0);//����CATstatus����Ϊ����
  EXT1_WriteCATData(EXT1_AddCATdoor1,0x04,0);//����CATdoor���Է�ת
  EXT1_WriteCATData(EXT1_AddCATstatus1,0x04,0);//����CATstatus���Է�ת

  EXT1_WriteCATData(EXT1_AddCATlock2,0x06,0xffff);//����CATlock����Ϊ���
  EXT1_WriteCATData(EXT1_AddCATlock2,0x02,0);//����������

  EXT1_WriteCATData(EXT1_AddCATdoor2,0x06,0);//����CATdoor����Ϊ����
  EXT1_WriteCATData(EXT1_AddCATstatus2,0x06,0);//����CATstatus����Ϊ����
  EXT1_WriteCATData(EXT1_AddCATdoor2,0x04,0);//����CATdoor���Է�ת
  EXT1_WriteCATData(EXT1_AddCATstatus2,0x04,0);//����CATstatus���Է�ת

  EXT2_WriteCATData(EXT2_AddCATlock1,0x06,0xffff);//����CATlock����Ϊ���
  EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//����������

  EXT2_WriteCATData(EXT2_AddCATdoor1,0x06,0);//����CATdoor����Ϊ����
  EXT2_WriteCATData(EXT2_AddCATstatus1,0x06,0);//����CATstatus����Ϊ����
  EXT2_WriteCATData(EXT2_AddCATdoor1,0x04,0);//����CATdoor���Է�ת
  EXT2_WriteCATData(EXT2_AddCATstatus1,0x04,0);//����CATstatus���Է�ת

  EXT2_WriteCATData(EXT2_AddCATlock2,0x06,0xffff);//����CATlock����Ϊ���
  EXT2_WriteCATData(EXT2_AddCATlock1,0x02,0);//����������

  EXT2_WriteCATData(EXT2_AddCATdoor2,0x06,0);//����CATdoor����Ϊ����
  EXT2_WriteCATData(EXT2_AddCATstatus2,0x06,0);//����CATstatus����Ϊ����
  EXT2_WriteCATData(EXT2_AddCATdoor2,0x04,0);//����CATdoor���Է�ת
  EXT2_WriteCATData(EXT2_AddCATstatus2,0x04,0);//����CATstatus���Է�ת
}

/*------------------------------------------------
                    ��������
------------------------------------------------*/
void Start_I2c(void)
{
  SDA_H;   //������ʼ�����������ź�
  _Nop();
  SCL_H;
  _Nop();    //��ʼ��������ʱ�����4.7us,��ʱ
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  SDA_L;     //������ʼ�ź�
  _Nop();    //��ʼ��������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  SCL_L;    //ǯסI2C���ߣ�׼�����ͻ��������
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    ��������
------------------------------------------------*/
void Stop_I2c(void)
{
  SDA_L;    //���ͽ��������������ź�
  _Nop();   //���ͽ���������ʱ���ź�
  SCL_H;    //������������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  SDA_H;    //����I2C���߽����ź�
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
void  SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //Ҫ���͵����ݳ���Ϊ8λ
    {
     if((c<<BitCnt)&0x80)SDA_H;   //�жϷ���λ
       else  SDA_L;                
     _Nop();
     SCL_H;               //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
      _Nop(); 
      _Nop();             //��֤ʱ�Ӹߵ�ƽ���ڴ���4��
      _Nop();
      _Nop();
      _Nop();         
     SCL_L; 
    }
    
    _Nop();
    _Nop();
    SDA_H;               //8λ��������ͷ������ߣ�׼������Ӧ��λ
    _Nop();
    _Nop();   
    SCL_H;
//    _Nop();
//    _Nop();
	 SDA_H;//��ֵ֮ǰ������
    _Nop();
    if(SDA_IN == 1)ack=0;     
       else ack=1;        //�ж��Ƿ���յ�Ӧ���ź�
    SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
unsigned char  RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  SDA_H;             //��������Ϊ���뷽ʽ
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        SCL_L;       //��ʱ����Ϊ�ͣ�׼����������λ
        _Nop();
        _Nop();      //ʱ�ӵ͵�ƽ���ڴ���4.7us
        _Nop();
        _Nop();
        _Nop();
        SCL_H;       //��ʱ����Ϊ��ʹ��������������Ч
        _Nop();
		  SDA_H;//��֮ǰ����
        _Nop();
        retc=retc<<1;
        if(SDA_IN == 1)retc=retc+1; //������λ,���յ�����λ����retc��
        _Nop();
        _Nop(); 
      }
  SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void Ack_I2c(void);
 
----------------------------------------------------------------*/
void Ack_I2c(void)
{
  
  SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  SCL_L;               //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void NoAck_I2c(void);
 
----------------------------------------------------------------*/
void NoAck_I2c(void)
{
  
  SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  SCL_L;                //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}



void EXT1_WriteCATData(u8 add, u8 subadd ,u16 dat)//16λ����������Ч
{
	dat = ~dat;//��λȡ��
   EXT1_Start_I2c();               //��������
   EXT1_SendByte(add);             //����������ַ
     if(ack==0)return;
   EXT1_SendByte(subadd);            //���������ӵ�ַ
     if(ack==0)return;
   EXT1_SendByte((u8)(dat&0x00ff));             //��������1
     if(ack==0)return;
   EXT1_SendByte((u8)((dat&0xff00)>>8));             //��������2
     if(ack==0)return;
   EXT1_Stop_I2c();  
}			 

u16 EXT1_ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   EXT1_Start_I2c();               //��������
   EXT1_SendByte(add);             //����������ַ
     if(ack==0)return(0);
   EXT1_SendByte(0);             //����������ַ
     if(ack==0)return(0);

	EXT1_Start_I2c();               //��������
	EXT1_SendByte(add+1);             //����������ַ
	  if(ack==0)return(0);
   Val1=EXT1_RcvByte();
   EXT1_Ack_I2c();                 //����Ӧ��λ

   Val2=EXT1_RcvByte();
   EXT1_NoAck_I2c();                 //���ͷ�Ӧ��λ
   EXT1_Stop_I2c();                  //��������

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 

/*------------------------------------------------
                    ��������
------------------------------------------------*/
void EXT1_Start_I2c(void)
{
  EXT1_SDA_H;   //������ʼ�����������ź�
  _Nop();
  EXT1_SCL_H;
  _Nop();    //��ʼ��������ʱ�����4.7us,��ʱ
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  EXT1_SDA_L;     //������ʼ�ź�
  _Nop();    //��ʼ��������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  EXT1_SCL_L;    //ǯסI2C���ߣ�׼�����ͻ��������
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    ��������
------------------------------------------------*/
void EXT1_Stop_I2c(void)
{
  EXT1_SDA_L;    //���ͽ��������������ź�
  _Nop();   //���ͽ���������ʱ���ź�
  EXT1_SCL_H;    //������������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  EXT1_SDA_H;    //����I2C���߽����ź�
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  EXT1_SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
void  EXT1_SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //Ҫ���͵����ݳ���Ϊ8λ
    {
     if((c<<BitCnt)&0x80)EXT1_SDA_H;   //�жϷ���λ
       else  EXT1_SDA_L;                
     _Nop();
     EXT1_SCL_H;               //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
      _Nop(); 
      _Nop();             //��֤ʱ�Ӹߵ�ƽ���ڴ���4��
      _Nop();
      _Nop();
      _Nop();         
     EXT1_SCL_L; 
    }
    
    _Nop();
    _Nop();
    EXT1_SDA_H;               //8λ��������ͷ������ߣ�׼������Ӧ��λ
    _Nop();
    _Nop();   
    EXT1_SCL_H;
//    _Nop();
//    _Nop();
	 EXT1_SDA_H;//��ֵ֮ǰ������
    _Nop();
    if(EXT1_SDA_IN == 1)ack=0;     
       else ack=1;        //�ж��Ƿ���յ�Ӧ���ź�
    EXT1_SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  EXT1_RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
unsigned char  EXT1_RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  EXT1_SDA_H;             //��������Ϊ���뷽ʽ
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        EXT1_SCL_L;       //��ʱ����Ϊ�ͣ�׼����������λ
        _Nop();
        _Nop();      //ʱ�ӵ͵�ƽ���ڴ���4.7us
        _Nop();
        _Nop();
        _Nop();
        EXT1_SCL_H;       //��ʱ����Ϊ��ʹ��������������Ч
        _Nop();
		  EXT1_SDA_H;//��֮ǰ����
        _Nop();
        retc=retc<<1;
        if(EXT1_SDA_IN == 1)retc=retc+1; //������λ,���յ�����λ����retc��
        _Nop();
        _Nop(); 
      }
  EXT1_SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void EXT1_Ack_I2c(void);
 
----------------------------------------------------------------*/
void EXT1_Ack_I2c(void)
{
  
  EXT1_SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  EXT1_SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  EXT1_SCL_L;               //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void EXT1_NoAck_I2c(void);
 
----------------------------------------------------------------*/
void EXT1_NoAck_I2c(void)
{
  
  EXT1_SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  EXT1_SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  EXT1_SCL_L;                //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}

void EXT2_WriteCATData(u8 add, u8 subadd ,u16 dat)//16λ����������Ч
{
	dat = ~dat;//��λȡ��
   EXT2_Start_I2c();               //��������
   EXT2_SendByte(add);             //����������ַ
     if(ack==0)return;
   EXT2_SendByte(subadd);            //���������ӵ�ַ
     if(ack==0)return;
   EXT2_SendByte((u8)(dat&0x00ff));             //��������1
     if(ack==0)return;
   EXT2_SendByte((u8)((dat&0xff00)>>8));             //��������2
     if(ack==0)return;
   EXT2_Stop_I2c();  
}			 

u16 EXT2_ReadCATData(u8 add)
 {
   unsigned char Val1=0,Val2=0;
	u16 Val;
   EXT2_Start_I2c();               //��������
   EXT2_SendByte(add);             //����������ַ
     if(ack==0)return(0);
   EXT2_SendByte(0);             //����������ַ
     if(ack==0)return(0);

	EXT2_Start_I2c();               //��������
	EXT2_SendByte(add+1);             //����������ַ
	  if(ack==0)return(0);
   Val1=EXT2_RcvByte();
   EXT2_Ack_I2c();                 //����Ӧ��λ

   Val2=EXT2_RcvByte();
   EXT2_NoAck_I2c();                 //���ͷ�Ӧ��λ
   EXT2_Stop_I2c();                  //��������

	Val = (u16)Val2*256 + (u16)Val1;
  return(Val);
 }	 
/*------------------------------------------------
                    ��������
------------------------------------------------*/
void EXT2_Start_I2c(void)
{
  EXT2_SDA_H;   //������ʼ�����������ź�
  _Nop();
  EXT2_SCL_H;
  _Nop();    //��ʼ��������ʱ�����4.7us,��ʱ
  _Nop();
  _Nop();
  _Nop();
  _Nop();    
  EXT2_SDA_L;     //������ʼ�ź�
  _Nop();    //��ʼ��������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();       
  EXT2_SCL_L;    //ǯסI2C���ߣ�׼�����ͻ��������
  _Nop();
  _Nop();
}
/*------------------------------------------------
                    ��������
------------------------------------------------*/
void EXT2_Stop_I2c(void)
{
  EXT2_SDA_L;    //���ͽ��������������ź�
  _Nop();   //���ͽ���������ʱ���ź�
  EXT2_SCL_H;    //������������ʱ�����4��
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  _Nop();
  EXT2_SDA_H;    //����I2C���߽����ź�
  _Nop();
  _Nop();
  _Nop();
  _Nop();
}




/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  EXT2_SendByte(unsigned char c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
------------------------------------------------------------------*/
void  EXT2_SendByte(u16 c)
{
 unsigned char BitCnt;
 
 for(BitCnt=0;BitCnt<8;BitCnt++)  //Ҫ���͵����ݳ���Ϊ8λ
    {
     if((c<<BitCnt)&0x80)EXT2_SDA_H;   //�жϷ���λ
       else  EXT2_SDA_L;                
     _Nop();
     EXT2_SCL_H;               //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
      _Nop(); 
      _Nop();             //��֤ʱ�Ӹߵ�ƽ���ڴ���4��
      _Nop();
      _Nop();
      _Nop();         
     EXT2_SCL_L; 
    }
    
    _Nop();
    _Nop();
    EXT2_SDA_H;               //8λ��������ͷ������ߣ�׼������Ӧ��λ
    _Nop();
    _Nop();   
    EXT2_SCL_H;
//    _Nop();
//    _Nop();
	 EXT2_SDA_H;//��ֵ֮ǰ������
    _Nop();
    if(EXT2_SDA_IN == 1)ack=0;     
       else ack=1;        //�ж��Ƿ���յ�Ӧ���ź�
    EXT2_SCL_L;
    _Nop();
    _Nop();
}







/*----------------------------------------------------------------
                 �ֽ����ݴ��ͺ���               
����ԭ��: unsigned char  EXT2_RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
------------------------------------------------------------------*/	
unsigned char  EXT2_RcvByte(void)
{
  unsigned char retc;
  unsigned char BitCnt;
  
  retc=0; 
  EXT2_SDA_H;             //��������Ϊ���뷽ʽ
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        EXT2_SCL_L;       //��ʱ����Ϊ�ͣ�׼����������λ
        _Nop();
        _Nop();      //ʱ�ӵ͵�ƽ���ڴ���4.7us
        _Nop();
        _Nop();
        _Nop();
        EXT2_SCL_H;       //��ʱ����Ϊ��ʹ��������������Ч
        _Nop();
		  EXT2_SDA_H;//��֮ǰ����
        _Nop();
        retc=retc<<1;
        if(EXT2_SDA_IN == 1)retc=retc+1; //������λ,���յ�����λ����retc��
        _Nop();
        _Nop(); 
      }
  EXT2_SCL_L;    
  _Nop();
  _Nop();
  return(retc);
}



/*----------------------------------------------------------------
                     Ӧ���Ӻ���
ԭ��:  void EXT2_Ack_I2c(void);
 
----------------------------------------------------------------*/
void EXT2_Ack_I2c(void)
{
  
  EXT2_SDA_L;     
  _Nop();
  _Nop();
  _Nop();      
  EXT2_SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  EXT2_SCL_L;               //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}
/*----------------------------------------------------------------
                     ��Ӧ���Ӻ���
ԭ��:  void EXT2_NoAck_I2c(void);
 
----------------------------------------------------------------*/
void EXT2_NoAck_I2c(void)
{
  
  EXT2_SDA_H;
  _Nop();
  _Nop();
  _Nop();      
  EXT2_SCL_H;
  _Nop();
  _Nop();              //ʱ�ӵ͵�ƽ���ڴ���4��
  _Nop();
  _Nop();
  _Nop();  
  EXT2_SCL_L;                //��ʱ���ߣ�ǯסI2C�����Ա��������
  _Nop();
  _Nop();    
}





