#include "includes.h"
#include "UART485.h"

void CAT955Init(void);

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ������Χģ���ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
    SystemInit();		/* ����ϵͳʱ��Ϊ72M */	
	 SysTick_init();		/* ��ʼ����ʹ��SysTick��ʱ�� */
	 NVIC_Configuration();
//	 TIME_Configuration();//��ʱ����ʼ��

	 GPRS_UART485_init(57600);
	 ICcardInit();
	 BarCodeInit(9600);

	 LEDIOinit();

	 CAT955Init();
//	 TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2 
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
    SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);//��ʼ����ʹ��SysTick��ʱ��
}

void InterruptConfig(void)
{   
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);

}

void NVIC_Configuration(void)
{
	/* Enable the TIME1 Interrupt */
	NVIC_InitTypeDef 	NVIC_InitStruct;//����һ�������жϵĽṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����ʽ���ȼ�1������3

	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;	 //��TIM2�ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//�����ȼ�0�����
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;	 //�����ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //�ж�ʹ��
	NVIC_Init(&NVIC_InitStruct);

/*	Enable the USART3 Interrupt ����ɨ��   */
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�򿪸��ж�
	NVIC_Init(&NVIC_InitStruct);

/*	Enable the USART1 Interrupt  modbus�жϳ�ʼ��	*/
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�򿪸��ж�
	NVIC_Init(&NVIC_InitStruct);

/*IC ���жϳ�ʼ��*/
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);	 
}

void TIME_Configuration(void)//��ʱ����ʼ��
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;//����һ������TIME�Ľṹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);//ʹ��TIME2ʱ��
	TIM_DeInit(TIM2);//��λ��ʱ��
	TIM_TimeBaseStruct.TIM_Prescaler = (7200-1);//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ
	TIM_TimeBaseStruct.TIM_Period = 200;	//����200
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct); 

	TIM_ClearFlag(TIM2 , TIM_FLAG_Update);	//����жϱ�־
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //ʹ���ж�
	TIM_Cmd(TIM2,DISABLE);//ʹ��TIM2 
}

/*������IO��ʼ��*/
void BuzzerIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);

	/* PA1,0 SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	#if OLD_NEW_BOARD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ùܽ�Ϊ���ù����������
	#else
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //���ùܽ�Ϊ���ù��ܿ�©���
	#endif
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //I2C�ӿ�ʹ�õ�GPIO�ܽų�ʼ��	

	BeepOFF;
}

void LEDIOinit(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);//ʹ��LEDʹ�õ�GPIOʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 + GPIO_Pin_12;//����ʹ��GPIO�ܽ�
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//����GPIOģʽ,��©���ù���
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�

 GPIO_Init(GPIOG , &GPIO_InitStructure);//��ʹ��LED����ص�GPIO��ʼ��
 GPIO_SetBits(GPIOG , GPIO_Pin_11 + GPIO_Pin_12);//�ر����еģ̣ţ�ָʾ��

/*������ʼ��*/
// RCC_APB2PeriphClockCmd(RCC_GPIO_KEY , ENABLE);//ʹ��LEDʹ�õ�GPIOʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����ʹ��GPIO�ܽ�
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����GPIOģʽ,��������
 //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�

 GPIO_Init(GPIOG , &GPIO_InitStructure);//��λ������ʼ��
}

/*����ɨ��ͷ��ʼ��*/
void BarCodeInit(unsigned long ulBaud)
{
	USART_InitTypeDef USART_InitSturct;//���崮�ڵĳ�ʼ���ṹ��

	GPIO_InitTypeDef GPIO_InitStruct;//���崮�ڶ�Ӧ�ܽŵĽṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);//ʱ��ʹ��	RCC_APB1Periph_UART5 | 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC, ENABLE);//�򿪴��ڹܽ�ʱ��

	//USART3_Tx_Pin Configure
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//��������ٶ�50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//���츴�����
	GPIO_Init(GPIOB , &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���
//USART3_Rx_Pin Configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIOģʽ��������
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;//��������
  GPIO_Init(GPIOB, &GPIO_InitStruct);//����ʼ���õĽṹ��װ��Ĵ���
  	
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART3 , ENABLE);//ʱ��ʹ��
	USART_InitSturct.USART_BaudRate = ulBaud;//������9600
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//���ݿ��8λ
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitSturct.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ʹ�ܷ��������

//USART3 Configure
	USART_Init(USART3 , &USART_InitSturct);//����ʼ���õĽṹ��װ��Ĵ���
	USART_ClearFlag(USART3 , USART_FLAG_TC);
	USART_ITConfig(USART3 , USART_IT_RXNE , ENABLE);//ʹ�ܽ����ж�
	//	USART_ITConfig(USART3 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART3 , ENABLE);//�򿪴���
}

void ICcardInit( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
/*GPIO init*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			   //Weigand26  D1�ж�
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			       //Weigand26  D0�ж�
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

/*EXIT init*/
	
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource0);	
	EXTI_ClearITPendingBit( EXTI_Line0 );
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );

	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource1);	
	EXTI_ClearITPendingBit( EXTI_Line1 );
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
}

/*ʹ��IC�������ж�*/
void ICcardEnable(void)
{
	NVIC_InitTypeDef 	NVIC_InitStruct;//����һ�������жϵĽṹ��

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/*����IC�������ж�*/
void ICcardDisable(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;//����һ�������жϵĽṹ��

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	  	//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	  		//ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;		//
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	  			//
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);
}
