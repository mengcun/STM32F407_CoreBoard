#ifndef __ETA_H
#define __ETA_H
#include "sys.h"


void ETA_Init(int Chn_num);//≥ı ºªØ		 
void Adc_Init(int Chn_num);
u16 Get_Adc(u8 ch);   
u16 Get_Adc_Average(u8 ch,u8 times);

#endif
