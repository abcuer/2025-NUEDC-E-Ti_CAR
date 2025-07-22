#ifndef _KEY_H_
#define _KEY_H_
#include "ti_msp_dl_config.h"
#include "board.h"

uint8_t Key_GetState(void);
void Key_Tick(void);
uint8_t Key_GetNum(void);

//uint8_t Key_GetNum1(void);
//uint8_t Key_GetNum2(void);

#endif
