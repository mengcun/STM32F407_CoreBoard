#ifndef  __LIN_H
#define  __LIN_H

#include "sys.h"	    

void LIN_Slave_int(int baud_rate);
void LIN_MasterSendFrameHead( u8 PID, u8 DLC );
u8 CalculateEnhancedChecksum(u8 pid, u8* buff, u8 bytes);

#endif
