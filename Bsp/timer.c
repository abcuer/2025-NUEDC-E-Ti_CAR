#include "timer.h"

void TimerDeviceInit(void)
{
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);	
	
	NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
}

