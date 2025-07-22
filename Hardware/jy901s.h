#ifndef __JY901S_H
#define __JY901S_H
#include "ti_msp_dl_config.h"

void jy901s_Init(void);
void jy901s_ReceiveData(uint8_t RxData);

extern float Roll,Pitch,Yaw;

#endif
