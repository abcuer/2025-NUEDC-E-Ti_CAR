#include "headfile.h"

uint8_t SoundLight_flag = 0;
uint16_t SoundLight_time = 0;
extern uint8_t lap_count;
float angle_initial = 0;
uint8_t target_lap = 0;

void System_Init(void)
{
//	board_init(); // 延迟 串口
//	jy901s_Init();
//	HC05_Init();
//	encoder_Init();
//	timer0_init();
//	timer1_init();
//	Ultrasonic_Init();
//	OLED_Init();
//    OLED_Clear();
//	delay_ms(100);//等待部署
//	IMU_init();
//	timer3_init();
//	delay_ms(20);
}

void Task_select(void)
{
	uint8_t Key = Key_GetNum();
		
	// 切换任务
	if(start_flag == 0)
	{
		if (Key == 1) 
		{
			LED_Green_ON();
			Task++;
		}
		if(Key == 2)
		{
			LED_Blue_ON();
			start_flag = 1;
		}
		if(Key == 3)  // 圈数判断
		{
			target_lap++;
		}
		if (Task > 4) Task = 0; 
		if(target_lap > 6) target_lap = 0;
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

void detect_turn_angle_flag(void)
{
    static int turn_angle_detect_count = 0;
    static int debounce_time = 0;
    static int detected = 0;
    static int detect_timer = 0;

    debounce_time++;
    detect_timer++;

    if (L4 && L3 && L2 && L1 )
    {
        turn_angle_detect_count++;
    }
    else if (!L4 && !L3 && !L2 && !L1)  // 完全离开，允许下次检测
    {
        detected = 0;
    }
    else
    {
        turn_angle_detect_count = 0;
    }

    if (turn_angle_detect_count >= 3 && !detected && debounce_time >= 100)
    {
        turn_angle_flag = 1;
        lap_flag++;    
        debounce_time = 0;
        detect_timer = 0;
        detected = 1;
    }

    if (detect_timer >= 500)  // 超时重置
    {
        turn_angle_detect_count = 0;
        debounce_time = 0;
        detect_timer = 0;
    }

    if (lap_flag >= 4)
    {
        lap_count++;
        lap_flag = 0;
    }
}


//void detect_turn_angle_flag(void)
//{
//    static int turn_angle_detect_count = 0;
//    static int debounce_time = 0;
//    static int detected = 0;

//    debounce_time++;

//    if (L4 && L3 && L2 && L1 )
//    {
//        turn_angle_detect_count++;
//    }
//    else
//    {
//        turn_angle_detect_count = 0;
//        detected = 0; // 允许下一次检测
//    }

//    // 连续检测命中3次，且时间隔足够
//	if (turn_angle_detect_count >= 3 && !detected && debounce_time >= 100)
//	{
//		turn_angle_flag = 1;
//		lap_flag++;    
//		debounce_time = 0;
//		detected = 1; // 防止重复触发
//	}
//	
//	if(lap_flag >= 4)
//	{
//		lap_count++;
//		lap_flag = 0;  // 清零防止重复加圈
//	}
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

extern int16_t turn_time;

void params_clear(void)
{
	Task = 0;
	lap_flag = 0;
    lap_count = 0;
    turn_angle_flag = 0;
    turn_time = 0;
    pid_flag = 0;
    basespeed = 0;
	target_lap = 0;
	workstep = 0;
}
