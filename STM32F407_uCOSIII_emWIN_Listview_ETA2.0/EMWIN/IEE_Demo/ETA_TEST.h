#ifndef _ETA_TEST_H
#define _ETA_TEST_H

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_FRAMEWIN_ETA 					(GUI_ID_USER + 0x00)
#define ID_BUTTON_SET_0          	(GUI_ID_USER + 0x01)
#define ID_BUTTON_SET_1			    	(GUI_ID_USER + 0x02)
#define ID_BUTTON_SETALL					(GUI_ID_USER + 0x03)
#define ID_BUTTON_RESETALL				(GUI_ID_USER + 0x04)
#define ID_BUTTON_GET_ADC         (GUI_ID_USER + 0x05)
#define ID_DROPDOWN_ADCTest			  (GUI_ID_USER + 0x06)
#define ID_TEXT_SETETA			  		(GUI_ID_USER + 0x07)
#define ID_TEXT_RESETETA			  	(GUI_ID_USER + 0x08)
#define ID_TEXT_SETALL			  		(GUI_ID_USER + 0x09)
#define ID_TEXT_RESETALL			  	(GUI_ID_USER + 0x0A)
#define ID_TEXT_ADC			  				(GUI_ID_USER + 0x0B)
#define ID_TEXT_REALVALUE			  	(GUI_ID_USER + 0x0C)

/*********************************************************************
*
*       _aDialogCreate_Test
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Test[] = {
	{ FRAMEWIN_CreateIndirect, "ETA TEST", 		ID_FRAMEWIN_ETA,       100,   26,700,  480, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", 		ID_DROPDOWN_ADCTest, 	 12,  56,  130,  300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "RESET",       ID_BUTTON_SET_0,       200, 130, 100,  40,	0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "SET", 				ID_BUTTON_SET_1, 			 200, 50,  100,  40,	0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "SET ALL", 		ID_BUTTON_SETALL,      200, 210, 100,  40,	0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "RESET ALL", 	ID_BUTTON_RESETALL,    200, 290, 100,  40,	0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "GET ADC",     ID_BUTTON_GET_ADC,     200, 370, 100,  40,	0, 0x0, 0 },  
  { TEXT_CreateIndirect, 		 "TEXT0", 			ID_TEXT_RESETETA, 		 320, 130, 350,  40, 	0, 0x190, 0 },
  { TEXT_CreateIndirect,		 "TEXT1", 			ID_TEXT_SETETA, 			 320, 50,  350,  40, 	0, 0x190, 0 },
  { TEXT_CreateIndirect,		 "SETALL", 			ID_TEXT_SETALL, 			 320, 210, 350,  40, 	0, 0x190, 0 },
  { TEXT_CreateIndirect,		 "RESETALL", 		ID_TEXT_RESETALL, 	 	 320, 290, 350,  40, 	0, 0x190, 0 },
  { TEXT_CreateIndirect,		 "ADC", 				ID_TEXT_ADC, 			 		 320, 370, 160,  40, 	0, 0x0, 	0 },
  { TEXT_CreateIndirect,		 "REALVALUE", 	ID_TEXT_REALVALUE, 		 480, 370, 160,  40, 	0, 0x0, 	0 },
	
	// USER START (Optionally insert additional widgets)
  // USER END
};

void _cbDialog_test(WM_MESSAGE * pMsg);

#endif
