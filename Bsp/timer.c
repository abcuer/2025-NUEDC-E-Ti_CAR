#include "timer.h"

void timer0_init(void)
{
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);	
}

void timer1_init(void)
{
	NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
}

void timer3_init(void)
{
	NVIC_ClearPendingIRQ(TIMER_3_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_3_INST_INT_IRQN);
}


