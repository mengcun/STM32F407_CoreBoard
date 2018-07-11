#ifndef _ETACONFIG_H
#define _ETACONFIG_H
#include "DIALOG.h"


void Init_DropDown(DROPDOWN_Handle hDropDown);
void Init_Button(BUTTON_Handle hButton);
void Init_Text(TEXT_Handle hTestText);
//void Init_Edit(EDIT_Handle hTestEdit);

unsigned char Exec_ETA_SET_LOW(TEXT_Handle hTestTextResetETA, int IdSelectedInDropdown);
unsigned char Exec_ETA_SET_HIGH(TEXT_Handle hTestTextSetETA, int IdSelectedInDropdown);
unsigned char Exec_ETA_SETALL_LOW(TEXT_Handle hTestTextResetAllETA);
unsigned char Exec_ETA_SETALL_HIGH(TEXT_Handle hTestTextSetAllETA);
unsigned char Exec_GET_ADC(TEXT_Handle hTestTextADC, TEXT_Handle hTestTextValue, int IdInDropdown);

unsigned char CANOE_SET_ETA_Status(unsigned char Chn, unsigned char Status);
unsigned char CANOE_GET_ETA_Status(unsigned char Chn);

#endif
