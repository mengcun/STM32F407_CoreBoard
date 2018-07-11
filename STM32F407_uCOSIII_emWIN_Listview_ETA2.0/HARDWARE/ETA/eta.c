#include "eta.h" 
#include "delay.h"		 

/*********************************************************************
*
*       ETA Channel To PIN Index
*/
const static uint16_t ETA_Channel_To_PIN[] = 
{
	GPIO_Pin_0,	
	GPIO_Pin_1,
	GPIO_Pin_2,
	GPIO_Pin_3,
	GPIO_Pin_4,
	GPIO_Pin_5,
	GPIO_Pin_6,
	GPIO_Pin_7,
	GPIO_Pin_8,
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11,
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15
};

/*********************************************************************
*
*       ETA_Init
*	
*/
/*为了实现将某一通道设置成输入或输出，将GPIO映射到通道上*/
void ETA_Init(int Chn_num)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
	if ( Chn_num > 29 && Chn_num < 32 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 17];	// CH31 - CH30    PIN14 - PIN13
		GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	}
	if ( Chn_num > 24 && Chn_num < 30 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 18];	// CH29 - CH25    PIN11 - PIN07
		GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	}
	if ( Chn_num > 15 && Chn_num < 25 )
	{	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOG时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 16];	// CH24 - CH16  PIN08 -PIN00
		GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
	}
	if( Chn_num > 9 && Chn_num < 16 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 10];	// CH15 - CH10   PIN05 - PIN00
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	}
	if ( Chn_num == 8 || Chn_num == 9 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 8];	// CH09 - CH08   PIN01 - PIN00  
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化	
	}
	if ( Chn_num < 8 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num];	// CH07 - CH00       PIN07 - PIN00
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	}
}
/*********************************************************************
*
*       Adc_Init
*	
*/
void Adc_Init(int Chn_num)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
  //初始化ADC1通道为模拟输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	
	if (Chn_num < 8)
	{
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num];	// ADCCH07 - ADCCH00 			PIN07 - PIN00
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
	}
	if ( Chn_num == 8 || Chn_num == 9)
	{
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 8];	// ADCCH09 - ADCCH08			PIN01 - PIN00
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化		
	}
	if( Chn_num > 9 && Chn_num < 16)
	{
		GPIO_InitStructure.GPIO_Pin = ETA_Channel_To_PIN[Chn_num - 10];	// ADCCH15 - ADCCH10 			PIN05 - PIN00
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	}
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
 
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}				  
//获得ADC值
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_15
//返回值:转换结果
u16 Get_Adc(u8 ch)   
{
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
