#include "gray.h"

#define LineFlagTime 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

int8_t L4,L3,L2,L1,R1,R2,R3,R4;

void Gray_Read(void) 
{
    R4 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R4_PIN) ? 0 : 1;
    R3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 0 : 1;
    R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 0 : 1;
    R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 0 : 1;
    L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 0 : 1;
    L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 0 : 1;
    L3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 0 : 1;
	L4 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L4_PIN) ? 0 : 1;
}

void Get_Light_TTL(void)
{
	baisetime++;
	if(R4 == 1 ||R3 == 1 || R2 == 1 || R1 == 1 || L1 == 1 || L2 == 1 || L3 == 1 || L4 == 1)
	{
		LineFlagCNT++;
		// 空白识别
		if(LineFlagCNT >= 3)
		{
			Line_flag = 1;
			baisetime = 0;
			LineFlagCNT = 0;
		}
	}
	else if(baisetime >= LineFlagTime)
	{
		Line_flag = 0;
		baisetime = 0;
	}
}
