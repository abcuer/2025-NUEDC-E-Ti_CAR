#include "headfile.h"

uint8_t lap_num = 0;
uint8_t task_num = 0;
uint8_t total_start_flag = 0;
uint8_t wait_flag = 0;

void System_Init(void)
{
	SYSCFG_DL_init();
	LedDeviceInit();
	BeepDeviceInit();
	KeyDeviceInit();
	EncoderInit();
	TimerDeviceInit();
	UartDeviceInit();
}

void TaskSelect(void)
{	
	if(total_start_flag == 0)
	{
		if (Key_GetNum(lap_num_key)) 
		{
			SetLedMode(LED_GREEN, LED_ON);
			lap_num++;
			if(lap_num > 5) lap_num = 0;
		}
		
		if(Key_GetNum(task_num_key))
		{
			SetLedMode(LED_BLUE, LED_ON);
			task_num ++;
			if (task_num > 2) task_num = 0; 
		}
		
		if(Key_GetNum(total_start_key))
		{
			total_start_flag = 1;
		}
	}
	else
	{
		if(wait_flag == 0)
		{
			switch(task_num)
			{
				case First: 		FirstTask(); 		break;
				case Second: 	SecondTask(); 	break;
			}
		}
	}
}

void Wait_For_A_While(void)
{
		SetLedMode(LED_BLUE, LED_ON);
		SetLedMode(LED_GREEN, LED_ON);
		delay_ms(1000);
		wait_flag = 1;
		SetLedMode(LED_BLUE, LED_OFF);
		SetLedMode(LED_GREEN, LED_OFF);
}


