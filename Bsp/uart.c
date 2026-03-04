#include "uart.h"

void UartDeviceInit(void)
{
	// MiniPC
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
}

