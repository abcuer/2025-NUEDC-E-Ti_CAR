#include "headfile.h"

uint8_t SoundLight_flag = 0;
uint16_t SoundLight_time = 0;
extern uint8_t lap_count;
float angle_initial = 0;

void System_Init(void)
{
	board_init(); // 延迟 串口
	jy901s_Init();
	HC05_Init();
	encoder_Init();
	timer0_init();
	timer1_init();
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
		if(Key == 3)
		{
		
		}
		if (Task > 4) Task = 0; 
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
 
void detect_OA_line(void)
{
    static int yaw_match_count = 0;
    static int detected = 0;
    static int cooldown = 0;

    cooldown++;

    // 判断是否在 -10° ~ 10° 范围内（激光笔对准OA线）
    if (Yaw >= -10 && Yaw <= 10)
    {
        yaw_match_count++;
    }
    else
    {
        yaw_match_count = 0;
        detected = 0;  // 允许下一次检测
    }

    // 若连续检测命中3次，且冷却时间够
    if (yaw_match_count >= 3 && !detected && cooldown >= 100)
    {
        stop_flag++;
        detected = 1;
        cooldown = 0;
    }

    // 如果 stop_flag 达到 2，小车停车
    if (stop_flag >= 2)
    {
        motor_stop();  // 替换为你的停车函数
    }
}


void detect_line_flag(void)
{
    static int line_detect_count = 0;
    static int debounce_time = 0;
    static int detected = 0;

    debounce_time++;

    if (L3 && L2 && L1 && R1 && R2 && R3)
    {
        line_detect_count++;
    }
    else
    {
        line_detect_count = 0;
        detected = 0; // 允许下一次检测
    }

    // 连续检测命中3次，且时间隔足够
    if (line_detect_count >= 3 && !detected && debounce_time >= 100)
    {
        line_flag++;       // 增加标志线计数
        detected = 1;      // 防止连续多次累加
        debounce_time = 0;
    }
}


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
extern uint8_t turn_flag;

void params_clear(void)
{
	Task = 0;
	stop_flag = 0;
	line_flag = 0;
	workstep = 0;
}
