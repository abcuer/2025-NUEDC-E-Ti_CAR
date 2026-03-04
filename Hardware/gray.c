#include "headfile.h"

GRAY_Struct gray = {0};

void Gray_Update(void) 
{
	gray.left[2] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 1 : 0;
	gray.left[1] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 1 : 0;
	gray.left[0] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
	gray.M  = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_M_PIN) ? 1 : 0;
	gray.right[0] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 1 : 0;
	gray.right[1] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 1 : 0;
	gray.right[2] = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 1 : 0;
}

