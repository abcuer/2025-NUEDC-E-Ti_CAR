#include "encoder.h"

int Get_Encoder_countA = 0;
int Get_Encoder_countB = 0;

/*
		E1A E1B: Get_Encoder_countA
		Pin: A09 A08
		E2A E2B: Get_Encoder_countB  
		Pin: B07 B08
*/

void encoder_Init(void)
{
	NVIC_ClearPendingIRQ(Encoder_left_INT_IRQN);
	NVIC_EnableIRQ(Encoder_left_INT_IRQN);
	NVIC_ClearPendingIRQ(Encoder_right_INT_IRQN);
	NVIC_EnableIRQ(Encoder_right_INT_IRQN);
}

/*******************************************************
∫Ø ˝π¶ƒ‹£∫Õ‚≤ø÷–∂œƒ£ƒ‚±‡¬Î∆˜–≈∫≈
»Îø⁄∫Ø ˝£∫Œﬁ
∑µªÿ  ÷µ£∫Œﬁ
***********************************************************/

void GROUP1_IRQHandler(void)
{
	uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_left_E1A_PIN | Encoder_left_E1B_PIN );
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB, Encoder_right_E2A_PIN | Encoder_right_E2B_PIN);

	// AÁºñÁ†ÅÂô®
	if ((gpioA & Encoder_left_E1A_PIN) == Encoder_left_E1A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1B_PIN))
		{
				Get_Encoder_countA--;
		}
		else
		{
				Get_Encoder_countA++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT, Encoder_left_E1A_PIN);
	}
	
	else if ((gpioA & Encoder_left_E1B_PIN) == Encoder_left_E1B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1A_PIN))
		{
				Get_Encoder_countA++;
		}
		else
		{
				Get_Encoder_countA--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT,Encoder_left_E1B_PIN);
	}
	
	// BÁºñÁ†ÅÂô®
	if ((gpioB & Encoder_right_E2A_PIN) == Encoder_right_E2A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2B_PIN))
		{
				Get_Encoder_countB--;
		}
		else
		{
				Get_Encoder_countB++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2A_PIN);
	}
	else if ((gpioB & Encoder_right_E2B_PIN) == Encoder_right_E2B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2A_PIN))
		{
				Get_Encoder_countB++;
		}
		else
		{
				Get_Encoder_countB--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2B_PIN);
	}
}

