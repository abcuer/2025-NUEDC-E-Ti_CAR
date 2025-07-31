#include "headfile.h"

#define TURNTIME 60000

uint8_t workstep = 0;
int32_t turn_time = 0;
uint8_t turn_flag = 0;
uint8_t turn_angle_flag = 0;
uint8_t lap_flag = 0;
uint8_t lap_count = 0;


void Task_1(void)
{
	switch(workstep)
	{
		case 0: 
			pid_Init(&trackLine1, POSITION_PID, 155, 0, 40);  // 单级寻迹环
			lap_flag = 0;
			lap_count = 0;
			turn_angle_flag = 0;
			turn_time = 0;
			pid_flag = 0;
			basespeed = 280;	
			workstep++;
			break;

		case 1:
			if(lap_count >= target_lap)
			{
				if(!turn_flag)  // 进入转弯阶段
				{
					turn_flag = 1;
					turn_time = 0;
				}

				if(turn_flag)
				{
					pid_flag = TURN_90_PID;
					bias = 190;
					basespeed = 20;
					turn_time++;

					if(turn_time > TURNTIME)
					{
						turn_flag = 0;
						motor_stop();
						params_clear();
						LED_Blue_ON();
					}
				}
				break;
			}
			// ✅ 只在非转弯阶段检测是否压线
			if(!turn_flag)
			{
				Get_Light_TTL();
				pid_flag = TRACK1_PID;

				if(turn_angle_flag)
				{
					turn_flag = 1;
					turn_time = 0;
				}
			}
			else  // 正在转弯
			{
				Get_Light_TTL();
				pid_flag = TURN_90_PID;
				bias = 200;
				basespeed = 20;
				turn_time++;

				if(turn_time > TURNTIME)
				{
					turn_angle_flag = 0;
					turn_flag = 0;
					basespeed = 280;
				}
			}
			break;
	}
}


