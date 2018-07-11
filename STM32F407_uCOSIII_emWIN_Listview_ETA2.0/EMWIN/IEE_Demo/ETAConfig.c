#include "DIALOG.h"
#include "eta.h"
#include "usart.h"
#include <stdbool.h>

unsigned char Flag_CANOE_EXEC_ETA = 3;
unsigned char IdInDropdown;	//The number Selected in the Dropdown
char AdcDatabuf[14];

/*********************************************************************
*
*       ETA Channel Index
*/
const static uint8_t ETA_Channel[] = 
{
	ADC_Channel_0,	
	ADC_Channel_1,	
	ADC_Channel_2,	
	ADC_Channel_3,	
	ADC_Channel_4,	
	ADC_Channel_5,	
	ADC_Channel_6,	
	ADC_Channel_7,	
	ADC_Channel_8,	
	ADC_Channel_9,	
	ADC_Channel_10,	
	ADC_Channel_11,	
	ADC_Channel_12,
	ADC_Channel_13,	
	ADC_Channel_14,	
	ADC_Channel_15
};
//ETA设置高电平

void ETA311(void){PFout(14) = 1;}	//CH31 HIGH
void ETA301(void){PFout(13) = 1;}	//CH30 HIGH
void ETA291(void){PFout(11) = 1;}	//CH29 HIGH
void ETA281(void){PFout(10) = 1;}	//CH28 HIGH
void ETA271(void){PFout(9) = 1;}	//CH27 HIGH
void ETA261(void){PFout(8) = 1;}	//CH26 HIGH
void ETA251(void){PFout(7) = 1;}	//CH25 HIGH

void ETA241(void){PGout(8) = 1;}	//CH24 HIGH
void ETA231(void){PGout(7) = 1;}	//CH23 HIGH
void ETA221(void){PGout(6) = 1;}	//CH22 HIGH
void ETA211(void){PGout(5) = 1;}	//CH21 HIGH
void ETA201(void){PGout(4) = 1;}	//CH20 HIGH
void ETA191(void){PGout(3) = 1;}	//CH19 HIGH
void ETA181(void){PGout(2) = 1;}	//CH18 HIGH
void ETA171(void){PGout(1) = 1;}	//CH17 HIGH
void ETA161(void){PGout(0) = 1;}	//CH16 HIGH


void ETA151(void){PCout(5) = 1;}	//CH15 HIGH
void ETA141(void){PCout(4) = 1;}	//CH14 HIGH
void ETA131(void){PCout(3) = 1;}	//CH13 HIGH
void ETA121(void){PCout(2) = 1;}	//CH12 HIGH
void ETA111(void){PCout(1) = 1;}	//CH11 HIGH
void ETA101(void){PCout(0) = 1;}	//CH10 HIGH

void ETA091(void){PBout(1) = 1;}	//CH09 HIGH
void ETA081(void){PBout(0) = 1;}	//CH08 HIGH

void ETA071(void){PAout(7) = 1;}	//CH07 HIGH
void ETA061(void){PAout(6) = 1;}	//CH06 HIGH
void ETA051(void){PAout(5) = 1;}	//CH05 HIGH
void ETA041(void){PAout(4) = 1;}	//CH04 HIGH
void ETA031(void){PAout(3) = 1;}	//CH03 HIGH
void ETA021(void){PAout(2) = 1;}	//CH02 HIGH
void ETA011(void){PAout(1) = 1;}	//CH01 HIGH
void ETA001(void){PAout(0) = 1;}	//CH00 HIGH


//ETA设置低电平

void ETA310(void){PFout(14) = 0;}	//CH31 LOW
void ETA300(void){PFout(13) = 0;}	//CH30 LOW
void ETA290(void){PFout(11) = 0;}	//CH29 LOW
void ETA280(void){PFout(10) = 0;}	//CH28 LOW
void ETA270(void){PFout(9) = 0;}	//CH27 LOW
void ETA260(void){PFout(8) = 0;}	//CH26 LOW
void ETA250(void){PFout(7) = 0;}	//CH25 LOW

void ETA240(void){PGout(8) = 0;}	//CH24 LOW
void ETA230(void){PGout(7) = 0;}	//CH23 LOW
void ETA220(void){PGout(6) = 0;}	//CH22 LOW
void ETA210(void){PGout(5) = 0;}	//CH21 LOW
void ETA200(void){PGout(4) = 0;}	//CH20 LOW
void ETA190(void){PGout(3) = 0;}	//CH19 LOW
void ETA180(void){PGout(2) = 0;}	//CH18 LOW
void ETA170(void){PGout(1) = 0;}	//CH17 LOW
void ETA160(void){PGout(0) = 0;}	//CH16 LOW

void ETA150(void){PCout(5) = 0;}	//CH15 LOW
void ETA140(void){PCout(4) = 0;}	//CH14 LOW
void ETA130(void){PCout(3) = 0;}	//CH13 LOW
void ETA120(void){PCout(2) = 0;}	//CH12 LOW
void ETA110(void){PCout(1) = 0;}	//CH11 LOW
void ETA100(void){PCout(0) = 0;}	//CH10 LOW

void ETA090(void){PBout(1) = 0;}	//CH09 LOW
void ETA080(void){PBout(0) = 0;}	//CH08 LOW

void ETA070(void){PAout(7) = 0;}	//CH07 LOW
void ETA060(void){PAout(6) = 0;}	//CH06 LOW
void ETA050(void){PAout(5) = 0;}	//CH05 LOW
void ETA040(void){PAout(4) = 0;}	//CH04 LOW
void ETA030(void){PAout(3) = 0;}	//CH03 LOW
void ETA020(void){PAout(2) = 0;}	//CH02 LOW
void ETA010(void){PAout(1) = 0;}	//CH01 LOW
void ETA000(void){PAout(0) = 0;}	//CH00 LOW

void (*SET_ETA_HIGH_ARRAY[32])(void) = 
{ 
	ETA001,
	ETA011,
	ETA021,
	ETA031,
	ETA041,
	ETA051,
	ETA061,
	ETA071,
	ETA081,
	ETA091,
	ETA101,
	ETA111,
	ETA121,
	ETA131,
	ETA141,
	ETA151,
	ETA161,
	ETA171,
	ETA181,
	ETA191,
	ETA201,
	ETA211,
	ETA221,
	ETA231,
	ETA241,
	ETA251,
	ETA261,
	ETA271,
	ETA281,
	ETA291,
	ETA301,
	ETA311,
};
void (*SET_ETA_LOW_ARRAY[32])(void) = 
{
	
	ETA000,
	ETA010,
	ETA020,
	ETA030,
	ETA040,
	ETA050,
	ETA060,
	ETA070,
	ETA080,
	ETA090,
	ETA100,
	ETA110,
	ETA120,
	ETA130,
	ETA140,
	ETA150,
	ETA160,
	ETA170,
	ETA180,
	ETA190,
	ETA200,
	ETA210,
	ETA220,
	ETA230,
	ETA240,
	ETA250,
	ETA260,
	ETA270,
	ETA280,
	ETA290,
	ETA300,
	ETA310,
};

/*********************************************************************
*
*       Init_DropDownValue
*	
*/
void Init_DropDown(DROPDOWN_Handle hDropDown)
{
		int i;
		DROPDOWN_SetFont(hDropDown, &GUI_Font20B_ASCII);
		DROPDOWN_SetTextColor(hDropDown, 0, 0x00BB00);
		DROPDOWN_SetTextColor(hDropDown, 2, GUI_BLACK);
		DROPDOWN_SetBkColor(hDropDown, 0, GUI_YELLOW);
		DROPDOWN_SetBkColor(hDropDown, 2, GUI_RED);
		DROPDOWN_SetAutoScroll(hDropDown, 1);
		DROPDOWN_SetScrollbarWidth(hDropDown, 25);
		DROPDOWN_SetItemSpacing(hDropDown,10);
		
		for (i = 0; i < 32; i++)
		{
			char ChannelBuf[5] = {0};
			AddStringToString(ChannelBuf, "Chn");
			AddIntToString(ChannelBuf, i);
			DROPDOWN_AddString(hDropDown, ChannelBuf);		
		}	
	  DROPDOWN_AddString(hDropDown, "");
	  DROPDOWN_AddString(hDropDown, "");
	  DROPDOWN_AddString(hDropDown, "");
}
/*********************************************************************
*
*       Init_Button
*	
*/
void Init_Button(BUTTON_Handle hButton)
{
	BUTTON_SetFont(hButton, &GUI_Font20B_ASCII);
	BUTTON_SetTextColor(hButton, 0, 0XFF0000);
	BUTTON_SetTextColor(hButton, 1, GUI_YELLOW);
	BUTTON_SetTextColor(hButton, 2, 0XFF0000);
}
/*********************************************************************
*
*       Init_Text
*	
*/
void Init_Text(TEXT_Handle hTestText)
{
	GUI_SetTextMode(GUI_TM_TRANS);
	TEXT_SetText(hTestText, "");
  TEXT_SetTextAlign(hTestText, GUI_TA_LEFT | GUI_TA_VCENTER);
  TEXT_SetTextColor(hTestText, 0XFF0000);
  TEXT_SetFont(hTestText, GUI_FONT_20_ASCII);
}
/*********************************************************************
*
*       Exec_ETA_SET_HIGH
*	
*/
unsigned char Exec_ETA_SET_HIGH(TEXT_Handle hTestTextSetETA, int IdSelectedInDropdown)
{
	char ETAStatusbuf[40] = {0};
	ETA_Init(IdSelectedInDropdown);
	(*SET_ETA_HIGH_ARRAY[IdSelectedInDropdown])();
	AddStringToString(ETAStatusbuf, "Successfully Set ETA Channel ");
	AddIntToString(ETAStatusbuf, IdSelectedInDropdown);
	TEXT_SetText(hTestTextSetETA, ETAStatusbuf);
	return 0;

}
/*********************************************************************
*
*       Exec_ETA_SET_LOW
*	
*/
unsigned char Exec_ETA_SET_LOW(TEXT_Handle hTestTextResetETA, int IdSelectedInDropdown)
{
	char ETAStatusbuf[40] = {0};
	ETA_Init(IdSelectedInDropdown);
	(*SET_ETA_LOW_ARRAY[IdSelectedInDropdown])();
  AddStringToString(ETAStatusbuf, "Successfully Reset ETA Channel ");
	AddIntToString(ETAStatusbuf, IdSelectedInDropdown);
	TEXT_SetText(hTestTextResetETA, ETAStatusbuf);
	return 0;
}

/*********************************************************************
*
*       Exec_ETA_SETALL_HIGH
*	
*/
unsigned char Exec_ETA_SETALL_HIGH(TEXT_Handle hTestTextSetAllETA)
{
	char ETAStatusbuf[40] = {0};
	char i;
	for (i = 0; i <32; i++)
	{
		ETA_Init(i);
		(*SET_ETA_HIGH_ARRAY[i])();
	}
	AddStringToString(ETAStatusbuf, "Successfully Set ETA All Channel");
	TEXT_SetText(hTestTextSetAllETA, ETAStatusbuf);
	return 0;
}
/*********************************************************************
*
*       Exec_ETA_SETALL_LOW
*	
*/
unsigned char Exec_ETA_SETALL_LOW(TEXT_Handle hTestTextResetAllETA)
{
	char ETAStatusbuf[40] = {0};
	char i;
	for (i = 0; i <32; i++)
	{
		ETA_Init(i);		
		(*SET_ETA_LOW_ARRAY[i])();
	}
	AddStringToString(ETAStatusbuf, "Successfully Reset ETA All Channel");
	TEXT_SetText(hTestTextResetAllETA, ETAStatusbuf);
	return 0;

}
/*********************************************************************
*
*       Exec_GET_ADC
*	
*/
unsigned char Exec_GET_ADC(TEXT_Handle hTestTextADC, TEXT_Handle hTestTextValue, int IdInDropdown)
{
	char 		Adcbuf[30] = {0};
	char 		RealValuebuf[30] = {0};
	float 	tempf;
	int     tempi;
	int 		ADCValue;
	//Init the Chn 0-15 as Input for get adc value.
	Adc_Init(IdInDropdown);

	if (IdInDropdown >15)
	{
		AddStringToString(Adcbuf, "Channel Are 0-15!!");
		TEXT_SetText(hTestTextADC, Adcbuf);
		AddStringToString(RealValuebuf, "Please Reselect!");
		TEXT_SetText(hTestTextValue, RealValuebuf);
		return 0;
	}
	ADCValue = Get_Adc_Average(ETA_Channel[IdInDropdown],20);//获取通道5的转换值，20次取平均;
				
	AddStringToString(Adcbuf, "CH");
	AddIntToString(Adcbuf, IdInDropdown);
	AddStringToString(Adcbuf, "_ADC: ");
	AddIntToString(Adcbuf, ADCValue);
	TEXT_SetText(hTestTextADC, Adcbuf);
			
	tempi = ADCValue*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
	AddStringToString(RealValuebuf, "CH");
	AddIntToString(RealValuebuf, IdInDropdown);
	AddStringToString(RealValuebuf, "_REAL: ");
	AddIntToString(RealValuebuf, tempi);
	tempf = ADCValue*(3.3/4096) - tempi;              //把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111
	tempi = tempf * 1000;                           	//小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数
	AddStringToString(RealValuebuf, ".");
	AddIntToString(RealValuebuf, tempi);
	TEXT_SetText(hTestTextValue, RealValuebuf);
	return 0;
}
/*********************************************************************
*
*       Rounding
*	
*/
int Rounding(float Float)
{
	bool positive = Float > 0;
	int c;
	if (!positive) {
			Float *= (-1.0f);
	}
  c = (int)Float;
	c = positive ? c : ((c + 1) * (-1));
	return c;
}
/*********************************************************************
*
*       CANOE_Exe_ETA_Status
*	
*/
unsigned char CANOE_SET_ETA_Status(unsigned char Chn, unsigned char Status)
{
	char 		EtaStatus[15] = {0};
	unsigned char i;

	if (Status == 0X48)	// SET ETA HIGH
	{		
		ETA_Init(Chn);
		(*SET_ETA_HIGH_ARRAY[Chn])();
		//Package the data, ASCII form
		EtaStatus[0] = 0X53;											// S
		EtaStatus[1] = 0X45;											// E
		EtaStatus[2] = 0X54;											// T
		EtaStatus[3] = 0X43;											// C
		EtaStatus[4] = 0X48;											// H
		EtaStatus[5] = USART_RX_BUF[3]; 					// (0 -3)
		EtaStatus[6] = USART_RX_BUF[4];					// (0 -9)
		EtaStatus[7] = 0X3D;											// =
		EtaStatus[8] = 0X3D;											// =
		EtaStatus[9] = 0X48;											// H
		EtaStatus[10] = 0X49;										// I
		EtaStatus[11] = 0X47;										// G
		EtaStatus[12] = 0X48;										// H				
		EtaStatus[13] = 0X0D;										// <CR>
		EtaStatus[14] = 0X0A;										// <LF>
		for(i = 0; i < 15; i++)
		{
			USART_SendData(USART1, EtaStatus[i]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
		}
		Flag_CANOE_EXEC_ETA = 1;
	}
	else if (Status == 0X4C )	// SET ETA LOW
	{		
		ETA_Init(Chn);
		(*SET_ETA_LOW_ARRAY[Chn])();
		//Package the data, ASCII form
		EtaStatus[0] = 0X53;											// S
		EtaStatus[1] = 0X45;											// E
		EtaStatus[2] = 0X54;											// T
		EtaStatus[3] = 0X43;											// C
		EtaStatus[4] = 0X48;											// H
		EtaStatus[5] = USART_RX_BUF[3]; 					// (0 -3)
		EtaStatus[6] = USART_RX_BUF[4];					// (0 -9)
		EtaStatus[7] = 0X3D;											// =
		EtaStatus[8] = 0X3D;											// =
		EtaStatus[9] = 0X4C;											// L
		EtaStatus[10] = 0X4F;										// O
		EtaStatus[11] = 0X57;										// W
		EtaStatus[12] = 0X0D;										// <CR>
		EtaStatus[13] = 0X0A;										// <LF>	
		for(i = 0; i < 14; i++)
		{
			USART_SendData(USART1, EtaStatus[i]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
		}
		Flag_CANOE_EXEC_ETA = 0;
	}
	return 0;
}
/*********************************************************************
*
*       CANOE_GET_ETA_Status
*	
*/
unsigned char CANOE_GET_ETA_Status(unsigned char Chn)
{
	float 	tempf;
	char    tempi;
	char 		tempfi1;
	char 		tempfi2;
	char 		tempfi3;
	char		i;
	int 		ADCValue;
	Adc_Init(Chn);
	if (Chn >15)
	{
		//Channel Are 0-15!! Please reselect
		return 0;
	}
	ADCValue = Get_Adc_Average(ETA_Channel[Chn],20);//获取通道5的转换值，20次取平均;
							
	tempi = ADCValue*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1234
	tempf = ADCValue*(3.3/4096) - tempi;  //把已经显示的整数部分去掉，留下小数部分，比如3.1234-3=0.1234
	tempfi1 = Rounding(tempf * 10);									//小数部分乘以10，例如：0.1234就转换为1.234，然后取整， 得到1
	tempfi2 = Rounding(tempf * 100 - tempfi1 * 10);			//小数部分乘以100，例如：0.1234就转换为12.34，然后取整得到12，减去 1*10， 得到2
	tempfi3 = Rounding(tempf * 1000 - tempfi1 * 100 - tempfi2 * 10);		//小数部分乘以1000，例如：0.1234就转换为123.4，然后取整得到123，减去 1*100，再减去 2*10 得到3
	
	//Package the data, ASCII form
	AdcDatabuf[0] = 0X43;											// C
	AdcDatabuf[1] = 0X48;											// H
	AdcDatabuf[2] = USART_RX_BUF[3];					// (0 -1)
	AdcDatabuf[3] = USART_RX_BUF[4];					// (0 -9)
	AdcDatabuf[4] = 0X3D;											// =
	AdcDatabuf[5] = 0X3D; 										// =
	AdcDatabuf[6] = tempi + 0X30;							// Int Value
	AdcDatabuf[7] = 0X2E;											//.
	AdcDatabuf[8] = tempfi1 + 0X30;						//十分位
	AdcDatabuf[9] = tempfi2 + 0X30;						//百分位
	AdcDatabuf[10] = tempfi3 + 0X30;					//千分位
	AdcDatabuf[11] = 0X56;										// V
	AdcDatabuf[12] = 0X0D;										// <CR>				
	AdcDatabuf[13] = 0X0A;										// <LF>
	for(i = 0; i < 14; i++)
	{
		USART_SendData(USART1, AdcDatabuf[i]);         //向串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束	
	}
	Flag_CANOE_EXEC_ETA = 2;
	return 0;
}
