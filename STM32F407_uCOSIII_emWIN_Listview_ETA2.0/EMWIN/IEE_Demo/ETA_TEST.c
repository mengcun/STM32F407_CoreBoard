//#include <stddef.h>
//#include <string.h>
//#include "WM.h"
//#include "sys.h"
//#include "rtc.h"
//#include "usart.h"
#include "DIALOG.h"
#include "WindowDLG.h"
//#include "ICONVIEW.h"
#include "TEXT.h"
#include "ETAConfig.h"
#include "ETA_TEST.h"

/*********************************************************************
*
*       _cbDialog_test
*/
void _cbDialog_test(WM_MESSAGE * pMsg) {
  WM_HWIN hTestFramwin;
	
	DROPDOWN_Handle hTestDropdown;
	
	BUTTON_Handle hTestButtonSetTo0;
	BUTTON_Handle hTestButtonSetTo1;
	BUTTON_Handle hTestButtonSetAll;
	BUTTON_Handle hTestButtonResetAll;
	
	BUTTON_Handle hTestButtonGetADC;
	
	TEXT_Handle hTestTextSetETA;
	TEXT_Handle hTestTextResetETA;
	TEXT_Handle hTestTextSetAllETA;
	TEXT_Handle hTestTextResetAllETA;

	EDIT_Handle hTestTextADC;
	EDIT_Handle hTestTextValue;
		
  int     NCode;
  int     Id;
	extern unsigned char IdInDropdown;	//From ETAConfig.c
		
  hTestFramwin = pMsg->hWin;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
		
		// Initialization of 'FRAMEWIN'
		FRAMEWIN_SetFont(hTestFramwin, &GUI_Font24B_ASCII);
    FRAMEWIN_SetTextAlign(hTestFramwin, GUI_TA_HCENTER);
	  FRAMEWIN_AddCloseButton(hTestFramwin, FRAMEWIN_BUTTON_RIGHT, 0);
		FRAMEWIN_AddMaxButton(hTestFramwin, FRAMEWIN_BUTTON_RIGHT, 0);
		// Initialization of 'ID_DROPDOWN_ADCTest'
    hTestDropdown = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_ADCTest);
		Init_DropDown(hTestDropdown);
	
		// Initialization of 'ID_BUTTON_SET_0'
    hTestButtonSetTo0 = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SET_0);
		Init_Button(hTestButtonSetTo0);
	
		// Initialization of 'ID_BUTTON_SET_1'
    hTestButtonSetTo1 = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SET_1);
		Init_Button(hTestButtonSetTo1);
		
		// Initialization of 'ID_BUTTON_SETALL'
    hTestButtonSetAll = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SETALL);
		Init_Button(hTestButtonSetAll);
					
		// Initialization of 'ID_BUTTON_RESETALL'
    hTestButtonResetAll = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_RESETALL);
		Init_Button(hTestButtonResetAll);
										
		// Initialization of 'ID_BUTTON_GET_ADC'
    hTestButtonGetADC = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_GET_ADC);
		Init_Button(hTestButtonGetADC);

		// Initialization of 'ID_TEXT_RESETETA'
    hTestTextResetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETETA);
		Init_Text(hTestTextResetETA);
		
		// Initialization of 'ID_TEXT_SETETA'
    hTestTextSetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETETA);
		Init_Text(hTestTextSetETA);

		// Initialization of 'ID_TEXT_SETALL'
    hTestTextSetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETALL);
		Init_Text(hTestTextSetAllETA);
					
		// Initialization of 'ID_TEXT_RESETALL'
    hTestTextResetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETALL);
		Init_Text(hTestTextResetAllETA);
		// Initialization of 'ID_TEXT_RESETALL'
	  hTestTextADC = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ADC);
		Init_Text(hTestTextADC);
		// Initialization of 'ID_TEXT_RESETALL'		
	  hTestTextValue = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALVALUE);	
		Init_Text(hTestTextValue);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;

    switch(NCode) 
		{
		case WM_NOTIFICATION_SEL_CHANGED:
			  hTestDropdown = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_ADCTest);
				IdInDropdown = DROPDOWN_GetSel(hTestDropdown);
      break;
    case WM_NOTIFICATION_RELEASED: // Notifications sent by 'Button'
      switch(Id) 
			{
      case ID_BUTTON_SET_0:
				hTestTextResetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETETA);	//Need to get the handle
				hTestTextSetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETETA);
				hTestTextSetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETALL);	
				hTestTextResetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETALL);
			
				TEXT_SetText(hTestTextSetETA, "");
				TEXT_SetText(hTestTextSetAllETA, "");						
				TEXT_SetText(hTestTextResetAllETA, "");						
			
				Exec_ETA_SET_LOW(hTestTextResetETA, IdInDropdown);
				break;
      case ID_BUTTON_SET_1:
				hTestTextResetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETETA);	//Need to get the handle
				hTestTextSetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETETA);
				hTestTextSetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETALL);	
				hTestTextResetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETALL);
			
				TEXT_SetText(hTestTextResetETA, "");
				TEXT_SetText(hTestTextSetAllETA, "");						
				TEXT_SetText(hTestTextResetAllETA, "");	
			
				Exec_ETA_SET_HIGH(hTestTextSetETA, IdInDropdown);
				break;
			case ID_BUTTON_SETALL:
				hTestTextResetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETETA);	//Need to get the handle
				hTestTextSetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETETA);
				hTestTextSetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETALL);	
				hTestTextResetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETALL);	
			
				TEXT_SetText(hTestTextResetETA, "");
				TEXT_SetText(hTestTextSetETA, "");				
				TEXT_SetText(hTestTextResetAllETA, "");	
			
				Exec_ETA_SETALL_HIGH(hTestTextSetAllETA);
				break;
			case ID_BUTTON_RESETALL:
				hTestTextResetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETETA);	//Need to get the handle
				hTestTextSetETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETETA);
				hTestTextSetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SETALL);	
				hTestTextResetAllETA = WM_GetDialogItem(pMsg->hWin, ID_TEXT_RESETALL);	
			
				TEXT_SetText(hTestTextResetETA, "");
				TEXT_SetText(hTestTextSetETA, "");				
				TEXT_SetText(hTestTextSetAllETA, "");		
			
				Exec_ETA_SETALL_LOW(hTestTextResetAllETA);
				break;
			case ID_BUTTON_GET_ADC:
			  hTestTextADC = WM_GetDialogItem(pMsg->hWin, ID_TEXT_ADC);
				hTestTextValue = WM_GetDialogItem(pMsg->hWin, ID_TEXT_REALVALUE);	
								
				Exec_GET_ADC(hTestTextADC, hTestTextValue, IdInDropdown);
				break;
      }
      break;
		case WM_NOTIFICATION_CLICKED:
       // USER START (Optionally insert code for reacting on notification message)
       // USER END
      break;
    }
    break;
	case WM_PAINT:
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font20B_ASCII);
		GUI_DispStringHCenterAt("Please select the channel:", 120, 2);
		GUI_DispStringHCenterAt("Chanel 0-15 used for ADC:", 120, 25);
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}
