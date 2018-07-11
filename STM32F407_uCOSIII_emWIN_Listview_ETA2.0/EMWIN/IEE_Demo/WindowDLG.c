#include <stddef.h>
#include <string.h>
#include "WM.h"
#include "rtc.h"
#include "usart.h"
#include "WindowDLG.h"
#include "ICONVIEW.h"
#include "ETA_TEST.h"
#include "ETAConfig.h"
#include "COMMonitor.h"
#include "lin.h"
#include "can.h"

int 			 Sel;
int        NumRowRXD;
int        NumRowTXD;
int        NumRowCAN;

int				 TimerDelay = 2;

WM_HWIN    hListviewRXD;
WM_HWIN    hListviewTXD;

WM_HWIN    hListviewLIN;
WM_HWIN    hListviewCAN;

WM_HWIN    hDropdown_BaudrateLIN;
WM_HWIN    hDropdown_BaudrateCAN;

extern unsigned char Flag_DataReady1;
extern unsigned char Flag_DataReady2;
extern char  LIN_RXD_buf1[33];
extern char  LIN_RXD_buf2[33];

extern unsigned char  Flag_CANDataReady;

extern unsigned char ChannelNumber;	// from usart.c	
extern char CAN_RXD_buf[24];
	
int Number = 0;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       DISPLAY_DATE__WEEK_TIME
*	
*/
void DISPLAY_DATE_WEEK_TIME(WM_MESSAGE * pMsg)
{
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	// time	
	sprintf(tbuf,"%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes); 
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	//date
	sprintf(dbuf,"20%02d-%02d-%02d/",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);	
	//week
	sprintf(wbuf,(char*)weeks[RTC_DateStruct.RTC_WeekDay - 1]);
}
/*********************************************************************
*
*       Check_Prepare_ListviewETA
*	
*/
void Check_Prepare_ListviewETA(LISTVIEW_Handle hListviewRXD, LISTVIEW_Handle hListviewTXD)
{	
	int i;
	NumRowRXD = LISTVIEW_GetNumRows(hListviewRXD);
	NumRowTXD = LISTVIEW_GetNumRows(hListviewTXD);

	if (NumRowRXD > 30 || NumRowTXD > 30)
	{
		for (i = 0; i <= 31; i++)	
		{
			LISTVIEW_DeleteRow(hListviewRXD, NumRowRXD - i);
			LISTVIEW_DeleteRow(hListviewTXD, NumRowTXD - i);
		}
		NumRowRXD = 0;
		NumRowTXD = 0;	
	}
	LISTVIEW_AddRow(hListviewRXD, ETA_Listitem[0]);
	LISTVIEW_AddRow(hListviewTXD, ETA_Listitem[0]);
}
/*********************************************************************
*
*       Check_Prepare_ListviewLINCAN
*	
*/
unsigned char Check_Prepare_ListviewLINCAN(LISTVIEW_Handle hListviewLINCAN)
{	
	int i;
	if (Number > 30)
	{
		for (i = 0; i <= 31; i++)	
		{LISTVIEW_DeleteRow(hListviewLINCAN, i);}	
		for (i = 0; i <= 31; i++)	
		{LISTVIEW_InsertRow(hListviewLINCAN, i, ETA_Listitem[0]);}	
		Number = 0;
		return 0;
	}
	return 0;
}
/*********************************************************************
*
*       UART3_ETA_Exec
*/
unsigned char UART3_ETA_Exec(void)
{
	u8 t;
	u8 Status;
	u8 ExeType;
	u8 ETA_INFO[3];
	
	for(t=3;t<6;t++)
	{ETA_INFO[t-3] = USART_RX_BUF[t];}
	ExeType = USART_RX_BUF[0];		//S or G
	ChannelNumber = (ETA_INFO[0] - 0X30) * 10 + (ETA_INFO[1] - 0X30);	//0-31
	Status = ETA_INFO[2];	// H or L	
	//SET ETA
	if (ExeType == 0x53)
	{
		if (ChannelNumber > 0X1F || (Status != 0X48 && Status != 0X4C))
		{return 0;}// Chn is invalid
		CANOE_SET_ETA_Status(ChannelNumber, Status);	
		return 0;
	}
		//GET ETA
	else if (ExeType == 0x47)
	{
		if (ChannelNumber > 0X10)
		{return 0;}// Chn is invalid or operation is invalid
		CANOE_GET_ETA_Status(ChannelNumber);
		return 0;
	}	
	return 0;
}	
/*********************************************************************
*
*       Display_ListviewItemTextETA
*	
*/
void Display_ListviewItemTextETA(void)
{
	extern unsigned char Flag_CANOE_EXEC_ETA;	//from ETAConfig.c
	extern char AdcDatabuf[14];
	extern unsigned char Flag_ETAMessageReady;
	char RecTextbuf[10] = {"SET"};
	char SendTextbuf[10] = {"CH"};
	char GetTextbuf[10] = {"GET"};
	char AdcValuebuf[20] = {NULL};
	int i;
	if (Flag_ETAMessageReady == 1)
	{UART3_ETA_Exec();}
	switch (Flag_CANOE_EXEC_ETA)
	{
		case 0:		//SET ETA LOW
			Check_Prepare_ListviewETA(hListviewRXD, hListviewTXD);
			if (ChannelNumber < 10)	
			{
				AddStringToString(RecTextbuf, "0");
				AddStringToString(SendTextbuf, "0");
			}	
			AddIntToString(RecTextbuf, ChannelNumber);		
			AddIntToString(SendTextbuf, ChannelNumber);	
			
		  AddStringToString(RecTextbuf, "LO");
		  AddStringToString(SendTextbuf, "==LO");
			
			LISTVIEW_SetItemText(hListviewRXD, 0, NumRowRXD, RecTextbuf);
			LISTVIEW_SetItemTextColor(hListviewRXD, 0, NumRowRXD, LISTVIEW_CI_UNSEL, GUI_GREEN);
			
			LISTVIEW_SetItemText(hListviewTXD, 0, NumRowTXD, SendTextbuf);
			LISTVIEW_SetItemTextColor(hListviewTXD, 0, NumRowTXD, LISTVIEW_CI_UNSEL, GUI_GREEN);
			Flag_CANOE_EXEC_ETA = 3;
			Flag_ETAMessageReady = 0;			
			break;
		case 1:		//SET ETA HIGH
			Check_Prepare_ListviewETA(hListviewRXD, hListviewTXD);
			if (ChannelNumber < 10)	
			{
				AddStringToString(RecTextbuf, "0");
				AddStringToString(SendTextbuf, "0");
			}	
		  AddIntToString(RecTextbuf, ChannelNumber);		
			AddIntToString(SendTextbuf, ChannelNumber);	
			
		  AddStringToString(RecTextbuf, "HI");
		  AddStringToString(SendTextbuf, "==HI");
			
			LISTVIEW_SetItemText(hListviewRXD, 0, NumRowRXD, RecTextbuf);
			LISTVIEW_SetItemTextColor(hListviewRXD, 0, NumRowRXD, LISTVIEW_CI_UNSEL, GUI_GREEN);
				
			LISTVIEW_SetItemText(hListviewTXD, 0, NumRowTXD, SendTextbuf);
			LISTVIEW_SetItemTextColor(hListviewTXD, 0, NumRowTXD, LISTVIEW_CI_UNSEL, GUI_GREEN);
			Flag_CANOE_EXEC_ETA = 3;
			Flag_ETAMessageReady = 0;			
			break;		
		case 2:		//GET ETA ADC VALUE
			Check_Prepare_ListviewETA(hListviewRXD, hListviewTXD);			
			if (ChannelNumber < 10)	
			{AddStringToString(GetTextbuf, "0");}		
			AddIntToString(GetTextbuf, ChannelNumber);			
		  AddStringToString(GetTextbuf, "_V");	
		
			LISTVIEW_SetItemText(hListviewRXD, 0, NumRowRXD, GetTextbuf);
			LISTVIEW_SetItemTextColor(hListviewRXD, 0, NumRowRXD, LISTVIEW_CI_UNSEL, GUI_GREEN);
			
			for (i = 6; i <=sizeof(AdcDatabuf); i++)
			{AdcValuebuf[i-6] = AdcDatabuf[i];}
						
			LISTVIEW_SetItemText(hListviewTXD, 0, NumRowTXD, AdcValuebuf);
			LISTVIEW_SetItemTextColor(hListviewTXD, 0, NumRowTXD, LISTVIEW_CI_UNSEL, GUI_GREEN);	

			Flag_CANOE_EXEC_ETA = 3;
			Flag_ETAMessageReady = 0;		
			break;
		default:
			break;
	}				
}
/*********************************************************************
*
*       Display_ListviewItemTextLIN
*	
*/
unsigned char Display_ListviewItemTextLIN(void)
{
	int i;
	/*MGW中会不停发送00来唤醒ECU，这里只能做到不让00在帧的开始显示出来，注意LIN_RXD_buf1[0]中存放的是0对应的ASCII码的16进制表示*/
	/*由于MGW不定时发送的唤醒信号/服务信号，会受到A4 00 00 00的消息，导致接收到的两帧显示在同一行的情况*/
	if (/*(LIN_RXD_buf1[0]!=0X30)&&(LIN_RXD_buf1[1]!=0X30)&&(LIN_RXD_buf1[0]!=0X20)&&*/Flag_DataReady1)	
	{
		LISTVIEW_SetItemText(hListviewLIN, 0, Number, LIN_RXD_buf1);
		Flag_DataReady1 = 0;	
		Number = Number + 1;
		Check_Prepare_ListviewLINCAN(hListviewLIN);			
		for (i = 0; i<33; i++)
		{LIN_RXD_buf1[i] = NULL;}	//这里没有使用memset函数，因为memset函数在初始化时按4字节为一个小块，进行操作的，这里只对33个字节初始化使用for循环会更快一些
		return 0;
	}
	if (/*(LIN_RXD_buf1[0]!=0X30)&&(LIN_RXD_buf1[1]!=0X30)&&(LIN_RXD_buf1[0]!=0X20)&&*/Flag_DataReady2)
	{
		LISTVIEW_SetItemText(hListviewLIN, 0, Number, LIN_RXD_buf2);
		Flag_DataReady2 = 0;		
		Number = Number + 1;
		Check_Prepare_ListviewLINCAN(hListviewLIN);			
		for (i = 0; i<33; i++)
		{LIN_RXD_buf2[i] = NULL;}
		return 0;
	}
	return 0;
}
/*********************************************************************
*
*       Display_ListviewItemTextCAN
*	
*/
unsigned char Display_ListviewItemTextCAN(void)
{
	if (Flag_CANDataReady)	
	{
		LISTVIEW_SetItemText(hListviewCAN, 0, Number, CAN_RXD_buf);
		Flag_CANDataReady = 0;	
		Number = Number + 1;
		Check_Prepare_ListviewLINCAN(hListviewCAN);			
		return 0;
	}	
	return 0;
}

/*********************************************************************
*
*       _cbWin
*/
static void _cbWin(WM_MESSAGE * pMsg) 
{
  WM_HWIN    hWin;
  WM_HWIN    hDtext1;
  int        Id;
  int        NCode;	
  unsigned char IdSelectedDropdown;	//The number Selected in the Dropdown

	hWin      = pMsg->hWin;
		
  switch (pMsg->MsgId) {
  case WM_PRE_PAINT:
    GUI_MULTIBUF_Begin();
    break;
  case WM_POST_PAINT:
    GUI_MULTIBUF_End();
    break;
  case WM_CREATE:
    break;
  case WM_DELETE:
    break;
  case WM_TIMER:
		DISPLAY_DATE_WEEK_TIME(pMsg);
		WM_InvalidateWindow(hWin);
		WM_RestartTimer(pMsg->Data.v, TimerDelay);
    break;
	case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
    NCode = pMsg->Data.v;                 // Notification code
    switch (Id) {
    case GUI_ID_ICONVIEW0:
      switch (NCode) 
			{
      case WM_NOTIFICATION_SEL_CHANGED:
        //Get the index of the currently selected icon
        Sel  = ICONVIEW_GetSel(pMsg->hWinSrc);
				//Get the window handle of a dialog box item (widget).
				hDtext1 = WM_GetDialogItem(hWin, GUI_ID_TEXT3);	
				switch (Sel)
				{
					case 0:
						TEXT_SetText(hDtext1, _aBitmapItem[Sel].pExplanation);
						break;
					case 1:
						GUI_CreateDialogBox(_aDialogCreate_Test, GUI_COUNTOF(_aDialogCreate_Test), &_cbDialog_test, 0, 0, 0);
					  TEXT_SetText(hDtext1, _aBitmapItem[Sel].pExplanation);
						break;
					default:
						break;	
				}			
      }
      break;
		case GUI_ID_DROPDOWN0:
			switch (NCode) 
			{
			case WM_NOTIFICATION_SEL_CHANGED:
				IdSelectedDropdown = DROPDOWN_GetSel(hDropdown_BaudrateLIN);
				switch (IdSelectedDropdown)
				{
					case 0:
						LIN_Slave_int(19200);
						break;
					case 1:
						LIN_Slave_int(38400);
						break;
					case 2:
						LIN_Slave_int(50000);
						break;
					case 3:
						LIN_Slave_int(115200);	
						break;					
					case 4:
						LIN_Slave_int(9600);
					break;
					default:
						break;
				}
      break;
			}
			break;
		case GUI_ID_DROPDOWN1:
			switch (NCode) 
			{
			case WM_NOTIFICATION_SEL_CHANGED:
				IdSelectedDropdown = DROPDOWN_GetSel(hDropdown_BaudrateCAN);
				switch (IdSelectedDropdown)
				{
					case 0:
						CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);      // CAN1初始化正常模式,波特率3000/6= 500Kbps    
						break;
					default:
						break;
				}
      break;
			}
			break;
    }
    break;
  case WM_PAINT:
		//Draw main window background
		GUI_SetBkColor(0x000000);	
		//显示LIN上的通信内容
		Display_ListviewItemTextLIN();		
		//显示CAN上的通信内容
		Display_ListviewItemTextCAN();
		//显示ETA上的通信内容
		Display_ListviewItemTextETA();	 	
		// Draw time
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(GUI_FONT_20B_ASCII);
    GUI_DispStringAt(dbuf, 580, 4);
		// Draw week
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(GUI_FONT_20B_ASCII);
    GUI_DispStringAt(wbuf, 677, 4);
    // Draw alarm icon
//    GUI_DrawBitmap(&_bmAlarm_16x16, 720, 3);   
    // Draw time
    GUI_SetColor(GUI_GREEN);
    GUI_SetFont(GUI_FONT_20B_ASCII);
    GUI_DispStringAt(tbuf, 740, 4);			
		break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) 
{
  PARA            Para  = {0};
  PARA          * pPara = &Para;
	WM_MESSAGE  pMsg1;
  WM_HWIN  hIcon;
  WM_HWIN  hText;
	WM_HWIN  hTextETA;
	WM_HWIN  hTextLIN;
	WM_HWIN  hTextCAN;
	char i;

	// Initialize the GUI
	GUI_Init();
	
	// Enable skinning
	BUTTON_SetDefaultSkin   (BUTTON_SKIN_FLEX);
  CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
//  DROPDOWN_SetDefaultSkin (DROPDOWN_SKIN_FLEX);
  FRAMEWIN_SetDefaultSkin (FRAMEWIN_SKIN_FLEX);
//  HEADER_SetDefaultSkin   (HEADER_SKIN_FLEX);
  MENU_SetDefaultSkin   	(MENU_SKIN_FLEX);
  MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
  MENU_SetDefaultSkin   	(MENU_SKIN_FLEX); 
	PROGBAR_SetDefaultSkin  (PROGBAR_SKIN_FLEX);
  RADIO_SetDefaultSkin    (RADIO_SKIN_FLEX);
  SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
  SLIDER_SetDefaultSkin   (SLIDER_SKIN_FLEX);
  SPINBOX_SetDefaultSkin   (SPINBOX_SKIN_FLEX);
	
	// Get the time first when power on
	DISPLAY_DATE_WEEK_TIME(&pMsg1);
	
  // Initialize parameter structure
  pPara->xSizeLCD = LCD_GetXSize();
  pPara->ySizeLCD = LCD_GetYSize();
	
  // Reduce size of desktop window to size of display
  WM_SetSize(WM_HBKWIN, pPara->xSizeLCD, pPara->ySizeLCD);
	
	//Enable the memdev to avoid falshing 
	WM_EnableMemdev(WM_HBKWIN);	
	
	hTextETA = TEXT_CreateEx(50, 23, 100, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT1, "ETA Communication");
	Init_Text_Commonitor(hTextETA);	
	hTextLIN = TEXT_CreateEx(190, 23, 100, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT2, "LIN Baudrate");
	Init_Text_Commonitor(hTextLIN);	
	hTextCAN = TEXT_CreateEx(600, 23, 100, 25, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT2, "CAN Baudrate");
	Init_Text_Commonitor(hTextCAN);	
	
	hDropdown_BaudrateLIN = DROPDOWN_CreateEx(300, 25, 100, 120, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_DROPDOWN0);
	hDropdown_BaudrateCAN = DROPDOWN_CreateEx(700, 25, 100, 120, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_DROPDOWN1);
	Init_DropDownBRLIN(hDropdown_BaudrateLIN);
	Init_DropDownBRCAN(hDropdown_BaudrateCAN);

	// Create ETAReceive Listview widget
	hListviewRXD = LISTVIEW_Create	(50, 50, 60, 425, WM_HBKWIN, 1, WM_CF_SHOW, 0);
	Init_ListviewETA(hListviewRXD);
	LISTVIEW_AddColumn(hListviewRXD, 60, "ETA_Rec",GUI_TA_LEFT);
	
	// Create ETASend Listview widget
	hListviewTXD = LISTVIEW_Create	(120, 50, 60, 425, WM_HBKWIN, 1, WM_CF_SHOW, 0);	
	Init_ListviewETA(hListviewTXD);	
	LISTVIEW_AddColumn(hListviewTXD, 60, "ETA_Send",GUI_TA_LEFT);

	// Create LIN Communication Listview widget
	hListviewLIN = LISTVIEW_Create	(190, 50, 470, 425, WM_HBKWIN, 1, WM_CF_SHOW, 0);	
	Init_ListviewCOM(hListviewLIN);	
	for (i = 0; i <= 31; i++)	
	{LISTVIEW_AddRow(hListviewLIN, ETA_Listitem[0]);}
	
	// Create CAN Communication Listview widget
	hListviewCAN = LISTVIEW_Create	(660, 50, 140, 425, WM_HBKWIN, 1, WM_CF_SHOW, 0);	
	Init_ListviewCOM(hListviewCAN);	
	for (i = 0; i <= 31; i++)	
	{LISTVIEW_AddRow(hListviewCAN, ETA_Listitem[0]);}
					
  // Set the callback to manage the windows.
	WM_SetCallback(WM_HBKWIN, _cbWin);

  // Create TEXT widget for explanation every Icon
	hText = TEXT_CreateEx(0, 1, 300, 23, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT3, "");
	Init_Text_Commonitor(hText);	
	// Create iconview widget
  hIcon = ICONVIEW_CreateEx(0, 25, 40, 200, WM_HBKWIN, WM_CF_SHOW | WM_CF_HASTRANS, ICONVIEW_CF_AUTOSCROLLBAR_V, GUI_ID_ICONVIEW0, 30, 60);		
	for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) {
			// Add icons to the widget
			ICONVIEW_AddBitmapItem(hIcon, _aBitmapItem[i].pBitmap, _aBitmapItem[i].pText);
		}

	ICONVIEW_SetBkColor(hIcon, ICONVIEW_CI_SEL, GUI_WHITE);
  ICONVIEW_SetFont(hIcon, &GUI_Font13B_ASCII);

 	//Redraw every 60 seconds
	WM_CreateTimer(WM_HBKWIN, 0, TimerDelay, 0);		
}

/*************************** End of file ****************************/
