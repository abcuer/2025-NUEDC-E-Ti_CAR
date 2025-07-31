#include "headfile.h"

uint8_t SoundLight_flag = 0;
uint16_t SoundLight_time = 0;

float angle_initial = 0;
uint8_t target_lap = 0;

void Task_select(void)
{
	uint8_t Key1 = Key_GetNum1();
	uint8_t Key2 = Key_GetNum2();
	
	// 切换任务
	if(Task == 0)
	{
		LED_Blue_ON();
		LED_Green_ON();
		if (Key1 == 1) 
		{
			LED_Green_ON();
			target_lap++;
		}
		if(Key2 == 1)
		{
			LED_Blue_ON();
			Task = 1;
		}
//		if(Key == 3)  // 圈数判断
//		{
//		}
		if (Task > 1) Task = 0; 
		if(target_lap > 5) target_lap = 0;
	}
	
	// 执行任务
	if(target_lap > 0)
	{
		if(first_flag == 1)
		{
			switch(Task)
			{
				case 1: Task_1(); break;
				case 2: Task_2(); break;
				case 3: Task_3(); break;
				case 4: Task_4(); break;
			}
		}
	}
}


void capture_initial_yaw(void) 
{
		LED_Blue_ON();
		delay_ms(50);
		LED_Blue_OFF();
		LED_Green_ON();
		float ang1 = Yaw;
		delay_ms(50);
		float ang2 = Yaw;
		delay_ms(50);
		float ang3 = Yaw;
		angle_initial = (ang1 + ang2 + ang3) / 3;
		first_flag = 1;
		LED_Green_OFF();
		delay_ms(50);
}

//void detect_turn_angle_flag(void)
//{
//    static int turn_angle_detect_count = 0;
//    static int debounce_time = 0;
//    static int detected = 0;
//    static int detect_timer = 0;

//    debounce_time++;
//    detect_timer++;

//    if (L3 && L2 && L1)
//    {
//        turn_angle_detect_count++;
//    }
//    else if (!L3 && !L2 && !L1)  // 完全离开，允许下次检测
//    {
//        detected = 0;
//    }
//    else
//    {
//        turn_angle_detect_count = 0;
//    }

//    if (turn_angle_detect_count >= 3 && !detected && debounce_time >= 1)
//    {
//        turn_angle_flag = 1;
//        lap_flag++;    
//        debounce_time = 0;
//        detect_timer = 0;
//        detected = 1;
//    }

//    if (detect_timer >= 500)  // 超时重置
//    {
//        turn_angle_detect_count = 0;
//        debounce_time = 0;
//        detect_timer = 0;
//    }

//    if (lap_flag >= 4)
//    {
//        lap_count++;
//        lap_flag = 0;
//    }
//}

 
void SoundLight(void)
{
	if(SoundLight_flag == 0)
	{
		Buzzer_ON();
		LED_Blue_ON();
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
			SoundLight_time = 0;
			SoundLight_flag = 0; 
		}
        
    }
}

extern int32_t turn_time;
extern uint8_t turn_flag;

void params_clear(void)
{
	Task = 0;
	lap_flag = 0;
    lap_count = 0;
    turn_angle_flag = 0;
    turn_time = 0;
	turn_flag = 0;
    pid_flag = 0;
    basespeed = 0;
	target_lap = 0;
	workstep = 0;
}
