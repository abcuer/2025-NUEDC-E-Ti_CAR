#include "gray.h"

#define LineFlagTime 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

int8_t L3,L2,L1,M,R1,R2,R3;

void Gray_Read(void) 
{
	L3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 1 : 0;
	L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 1 : 0;
	L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
	M  = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
	R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 1 : 0;
	R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 1 : 0;
	R3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 1 : 0;
}
