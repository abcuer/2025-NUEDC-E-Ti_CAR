#include "headfile.h"

static uint8_t RxBuffer[11];
static volatile uint8_t RxState = 0;
static uint8_t RxIndex = 0;
float Roll,Pitch,Yaw;
extern uint8_t Yaw_update; 

void jy901s_Init(void)
{
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
}

void jy901s_ReceiveData(uint8_t RxData)
{
	uint8_t i,sum=0;
	if (RxState == 0)	
	{
		if (RxData == 0x55)	
		{
			RxBuffer[RxIndex] = RxData;
			RxState = 1;
			RxIndex = 1;	
		}
	}
	else if (RxState == 1)
	{
		if (RxData == 0x53)
		{
			RxBuffer[RxIndex] = RxData;
			RxState = 2;
			RxIndex = 2;	
		}
	}
	else if (RxState == 2)
	{
		RxBuffer[RxIndex++] = RxData;
		if(RxIndex == 11)	
		{
			for(i=0;i<10;i++)
			{
				sum = sum + RxBuffer[i];	
			}
			if(sum == RxBuffer[10])		
			{
//				Roll = ((int16_t) ((int16_t) RxBuffer[3] << 8 | (int16_t) RxBuffer[2])) / 32768.0f * 180.0f;
//				Pitch = ((int16_t) ((int16_t) RxBuffer[5] << 8 | (int16_t) RxBuffer[4])) / 32768.0f * 180.0f;
				Yaw = ((int16_t) ((int16_t) RxBuffer[7] << 8 | (int16_t) RxBuffer[6])) / 32768.0f * 180.0f ;
				Yaw_update = 1;
 			}
			RxState = 0;
			RxIndex = 0;	
		}
	}
}

void UART_2_INST_IRQHandler(void)
{
	uint8_t jy901s_data =0;
    switch( DL_UART_getPendingInterrupt(UART_2_INST) )
    {
        case DL_UART_IIDX_RX:
            jy901s_data = DL_UART_Main_receiveData(UART_2_INST);
			jy901s_ReceiveData(jy901s_data);
			break;
		default:
            break;
    }
}


