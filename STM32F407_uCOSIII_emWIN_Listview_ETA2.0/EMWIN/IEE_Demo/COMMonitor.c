#include "DIALOG.h"
#include "WindowDLG.h"
#include "COMMonitor.h"

/*********************************************************************
*
*       Init_Text_Commonitor
*	
*/
void Init_Text_Commonitor(TEXT_Handle hMonitorText)
{
	GUI_SetTextMode(GUI_TM_TRANS);
  TEXT_SetTextAlign(hMonitorText, GUI_TA_HCENTER | GUI_TA_VCENTER);
  TEXT_SetTextColor(hMonitorText, 0X00FF00);
  TEXT_SetWrapMode(hMonitorText, GUI_WRAPMODE_WORD);
  TEXT_SetFont(hMonitorText, GUI_FONT_13_ASCII);
}

/*********************************************************************
*
*       Init_ListviewCOM
*	
*/
void Init_ListviewCOM(LISTVIEW_Handle hSystemListviewCOM)
{
	HEADER_Handle hListViewHeader;
	
  hListViewHeader = LISTVIEW_GetHeader(hSystemListviewCOM);
  HEADER_SetBkColor(hListViewHeader, 0X000000);
  HEADER_SetTextColor(hListViewHeader, 0XFF0000);
  HEADER_SetHeight(hListViewHeader, 16);
	HEADER_SetFont(hListViewHeader, GUI_FONT_13_ASCII);

  LISTVIEW_SetBkColor(hSystemListviewCOM, 0, 0X000000);
  LISTVIEW_SetTextColor(hSystemListviewCOM,LISTVIEW_CI_UNSEL, GUI_GREEN);
	LISTVIEW_SetTextAlign(hSystemListviewCOM, 0, GUI_TA_LEFT | GUI_TA_VCENTER);
	LISTVIEW_SetFont(hSystemListviewCOM, GUI_FONT_13_ASCII);
	
  LISTVIEW_AddColumn(hSystemListviewCOM, 480,"DATA IN BUS", GUI_TA_LEFT | GUI_TA_VCENTER);
	  
}
/*********************************************************************
*
*       Init_ListviewETA
*	
*/
void Init_ListviewETA(LISTVIEW_Handle hSystemListviewETA)
{
	HEADER_Handle hListViewHeader;
	
  hListViewHeader = LISTVIEW_GetHeader(hSystemListviewETA);
  HEADER_SetBkColor(hListViewHeader, 0X000000);
	HEADER_SetTextColor(hListViewHeader, 0XFF0000);
  HEADER_SetHeight(hListViewHeader, 16);
	HEADER_SetFont(hListViewHeader, GUI_FONT_13_ASCII);
	
  LISTVIEW_SetDefaultBkColor(LISTVIEW_CI_UNSEL| LISTVIEW_CI_SEL, 0X000000);
	LISTVIEW_SetTextAlign(hSystemListviewETA, 0, GUI_TA_LEFT | GUI_TA_VCENTER);
	LISTVIEW_SetFont(hSystemListviewETA, GUI_FONT_13_ASCII);
  LISTVIEW_SetBkColor(hSystemListviewETA, 0, 0X000000);
	
}
/*********************************************************************
*
*       Init_DropDownBRLIN
*	
*/
void Init_DropDownBRLIN(DROPDOWN_Handle hDropdown_Baudrate)
{
		DROPDOWN_SetFont(hDropdown_Baudrate, &GUI_Font13_ASCII);
		DROPDOWN_SetTextColor(hDropdown_Baudrate, DROPDOWN_CI_UNSEL, 0X00FF00);
		DROPDOWN_SetTextColor(hDropdown_Baudrate, DROPDOWN_CI_SEL, 0XFF0000);
	
		DROPDOWN_SetBkColor(hDropdown_Baudrate, DROPDOWN_CI_UNSEL, 0X000000);
		DROPDOWN_SetBkColor(hDropdown_Baudrate, DROPDOWN_CI_SEL, 0X000000);
	  DROPDOWN_SetColor(hDropdown_Baudrate,DROPDOWN_CI_BUTTON | DROPDOWN_CI_ARROW, 0X000000);
		
		DROPDOWN_SetItemSpacing(hDropdown_Baudrate,8);
	
	  DROPDOWN_AddString(hDropdown_Baudrate, "19200");		
	  DROPDOWN_AddString(hDropdown_Baudrate, "38400");
	  DROPDOWN_AddString(hDropdown_Baudrate, "50000");
	  DROPDOWN_AddString(hDropdown_Baudrate, "115200");
	  DROPDOWN_AddString(hDropdown_Baudrate, "9600");
	  DROPDOWN_AddString(hDropdown_Baudrate, "");
}
/*********************************************************************
*
*       Init_DropDownBRCAN
*	
*/
void Init_DropDownBRCAN(DROPDOWN_Handle hDropdown_Baudrate)
{
		DROPDOWN_SetFont(hDropdown_Baudrate, &GUI_Font13_ASCII);
		DROPDOWN_SetTextColor(hDropdown_Baudrate, DROPDOWN_CI_UNSEL, 0X00FF00);
		DROPDOWN_SetTextColor(hDropdown_Baudrate, DROPDOWN_CI_SEL, 0XFF0000);
	
		DROPDOWN_SetBkColor(hDropdown_Baudrate, DROPDOWN_CI_UNSEL, 0X000000);
		DROPDOWN_SetBkColor(hDropdown_Baudrate, DROPDOWN_CI_SEL, 0X000000);
	  DROPDOWN_SetColor(hDropdown_Baudrate,DROPDOWN_CI_BUTTON | DROPDOWN_CI_ARROW, 0X000000);
		
		DROPDOWN_SetItemSpacing(hDropdown_Baudrate,3);
	
	  DROPDOWN_AddString(hDropdown_Baudrate, "50000");
	  DROPDOWN_AddString(hDropdown_Baudrate, "");
}
