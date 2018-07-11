#ifndef _COMMONITOR_H
#define _COMMONITOR_H
#include "DIALOG.h"
/*********************************************************************
*
*       ETA Listitem Index
*/
static const char * ETA_Listitem[][1] = {
  { ""}
};
void Init_Text_Commonitor(TEXT_Handle hMonitorText);
void Init_ListviewCOM(LISTVIEW_Handle hSystemListviewLIN);
void Init_ListviewETA(LISTVIEW_Handle hSystemListviewETA);
void Init_DropDownBRLIN(DROPDOWN_Handle hDropdown_Baudrate);
void Init_DropDownBRCAN(DROPDOWN_Handle hDropdown_Baudrate);

#endif
