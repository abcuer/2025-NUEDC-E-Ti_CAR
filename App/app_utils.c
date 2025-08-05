#include "headfile.h"

uint8_t SoundLight_flag = 0;
uint16_t SoundLight_time = 0;

uint8_t target_lap = 0;

void Task_select(void)
{
	uint8_t Key1 = Key_GetNum1();
	uint8_t Key2 = Key_GetNum2();
	uint8_t Key3 = Key_GetNum3();
	
	// 切换任务
	if(start_flag == 0)
	{
		if (Key1 == 1) 
		{
			LED_Green_ON();
			target_lap++;
		}
		if(Key2 == 1)
		{
			LED_Blue_ON();
			Task ++;
		}
		if(Key3 == 1)
		{
			start_flag = 1;
		}
		if (Task > 2) Task = 0; 
		if(target_lap > 5) target_lap = 0;
	}
	
	// 执行任务
	if(start_flag == 1)
	{
		if(first_flag == 1)
		{
			switch(Task)
			{
				case 1: Task_1(); break;
				case 2: Task_2(); break;
			}
		}
	}
}

void capture_initial_yaw(void) 
{
		LED_Blue_ON();
		delay_ms(50);
		LED_Blue_OFF();
		delay_ms(50); 
		LED_Green_ON();
		delay_ms(100);
		first_flag = 1;
		LED_Green_OFF();
		delay_ms(50);
}

void SoundLight(void)
{
	if(SoundLight_flag == 0)
	{
		Buzzer_ON();
		LED_Blue_ON();
		LED_Green_ON();
		SoundLight_flag = 1;
	}
}

void UpdateSoundLight(void)
{
    if(SoundLight_flag)
    {
        SoundLight_time++;

		if(SoundLight_time >= 12) 
		{
			Buzzer_OFF();
			LED_Blue_OFF();
			LED_Green_OFF();
			SoundLight_time = 0;
			SoundLight_flag = 0; 
		}
        
    }
}

extern uint8_t turn_flag;

void params_clear(void)
{
	Task = 0;
	lap_flag = 0;
    lap_count = 0;
    turn_angle_flag = 0;
	turn_flag = 0;
    pid_flag = 0;
    basespeed = 0;
	target_lap = 0;
	workstep = 0;
}
