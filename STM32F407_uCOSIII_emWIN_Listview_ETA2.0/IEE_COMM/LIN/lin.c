#include "lin.h"
#include "delay.h"
#include "usart.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

u8 LIN_CHECKSUM_PID = 0;
u8 LIN_DLC = 0;
unsigned char Flag_DataReady1 = 0;
unsigned char Flag_DataReady2 = 0;
unsigned char ReciveBKTimes = 0;
char  LIN_RXD_buf1[33] = {NULL};	
char  LIN_RXD_buf2[33] = {NULL};
unsigned int k = 0;	

void LIN_Slave_int(int baud_rate)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);       // 使能PORTC时钟  用于控制PC12 LIN TXD 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);       // 使能PORTD时钟  用于控制PD2 LIN RXD 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);       // 使能LIN时钟

	USART_DeInit(UART5);	//  复位串口5
	
  // USART5_RX PD2
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;    							//  PD2 = LIN RXD
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //  复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //  推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;          //  100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //  上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);                      //  初始化PD2
  // USART5_TX PC12       
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;    							//  PC12 = LIN TXD
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //  复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //  推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;          //  100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //  上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);                      //  初始化PC12
        
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource12, GPIO_AF_UART5);   //  PC12 = LIN TXD
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2, GPIO_AF_UART5);   //  PD2 = LIN RXD
    //UART5 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3 ;	//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                      //根据指定的参数初始化NVIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx;					//从机只收模式

  USART_Init(UART5, &USART_InitStructure); 					//初始化串口
	
	USART_LINBreakDetectLengthConfig(UART5, USART_LINBreakDetectLength_10b);
  USART_ITConfig(UART5, USART_IT_LBD , ENABLE);	  //开启break中断  从机才需要此功能
	USART_LINCmd( UART5, ENABLE);  

	USART_ITConfig(UART5, USART_IT_RXNE , ENABLE);			//开启中断	
	USART_Cmd(UART5, ENABLE);                    				//使能串口	


}
//------------------------------------------------------------------串口3中断服务程序
void UART5_IRQHandler(void)                				
{
	int Res;
	char temp[3];
	int j;
#if SYSTEM_SUPPORT_OS   // 使用UCOS操作系统
		OSIntEnter();    
#endif

	if( USART_GetITStatus(UART5,USART_IT_RXNE) != RESET)   //字节开始接收
	{			
		if (ReciveBKTimes == 1)	//收到BK次数为奇数时
		{	
			Res =	USART_ReceiveData(UART5);						   // 接收单个字节 
			sprintf(temp,"%02X ",Res);
			for(j = 0; j < 3; j++)
			{
				LIN_RXD_buf1[k] = temp[j];
				k = k+1;
				if( k >= 33)
				{
					k = 0;
					Flag_DataReady1 = 1;
				}
			}				
		}
		else if (ReciveBKTimes == 0)		//收到break信号个数为偶数
		{
			Res =	USART_ReceiveData(UART5);						    // 接收单个字节      			
			sprintf(temp,"%02X ",Res);
			for(j = 0; j < 3; j++)
			{
				LIN_RXD_buf2[k] = temp[j];
				k = k+1;
				if( k >= 33)
				{
					k = 0;
					Flag_DataReady2 = 1;
				}
			}				
		}			
	}	
	
	if( USART_GetITStatus(UART5,USART_IT_LBD) != RESET)   // 如果检测到break信号
	{		
		k = 0;
		ReciveBKTimes = ReciveBKTimes + 1;
		switch(ReciveBKTimes)
		{
			case 1:
				Flag_DataReady1 = 0;
				Flag_DataReady2 = 1;
				break;
			case 2:
				ReciveBKTimes = 0;
				Flag_DataReady1 = 1;							
				Flag_DataReady2 = 0;
			break;
			default:
				break;
		}
		USART_ClearITPendingBit( UART5, USART_IT_LBD );//清除BK标志		
	}	
#if SYSTEM_SUPPORT_OS  
    OSIntExit();    	// 退出中断
#endif
}
