#include "encoder.h"

int encoder_left_count = 0;
int encoder_right_count = 0;

/*
		E1A E1B: encoder_left_count
		Pin: A09 A08
		E2A E2B: encoder_right_count  
		Pin: B07 B08
*/

void EncoderInit(void)
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
				encoder_left_count--;
		}
		else
		{
				encoder_left_count++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT, Encoder_left_E1A_PIN);
	}
	
	else if ((gpioA & Encoder_left_E1B_PIN) == Encoder_left_E1B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1A_PIN))
		{
				encoder_left_count++;
		}
		else
		{
				encoder_left_count--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT,Encoder_left_E1B_PIN);
	}
	
	// BÁºñÁ†ÅÂô®
	if ((gpioB & Encoder_right_E2A_PIN) == Encoder_right_E2A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2B_PIN))
		{
				encoder_right_count--;
		}
		else
		{
				encoder_right_count++;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2A_PIN);
	}
	else if ((gpioB & Encoder_right_E2B_PIN) == Encoder_right_E2B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2A_PIN))
		{
				encoder_right_count++;
		}
		else
		{
				encoder_right_count--;
		}
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2B_PIN);
	}
}

