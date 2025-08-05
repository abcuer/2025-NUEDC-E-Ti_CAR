#include "headfile.h"

uint8_t workstep = 0;
uint8_t turn_flag = 0;
uint8_t turn_angle_flag = 0;
uint8_t lap_flag = 0;
uint8_t lap_count = 0;

#define TURN_DISTANCE 228

void Task_1(void)
{
	switch(workstep)
	{
		case 0: 
			pid_Init(&trackLine1, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			lap_flag = 0;
			lap_count = 0;
			turn_angle_flag = 0;
			pid_flag = 0;
			basespeed = 280;
			workstep++;
			break;

		case 1:
			if(lap_count >= target_lap)
			{
				if(!turn_flag)  // 首次进入转弯阶段
				{
					turn_flag = 1;
					clear_distance1();  // ✅ 清除累计编码器距离
				}

				get_distance1();  // ✅ 实时更新距离

				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				// ✅ 距离判断是否完成90度转弯
				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					turn_flag = 0;
					motor_stop();
					params_clear();
					LED_Blue_ON();  // ✅ 圈数完成，转弯完成
				}
				break;
			}

			// ✅ 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Get_Light_TTL();
				pid_flag = TRACK1_PID;

				if(turn_angle_flag)
				{
					turn_flag = 1;
					clear_distance1();  // ✅ 进入拐角转弯，也清零距离
				}
			}
			else  // 拐角转弯阶段
			{
				get_distance1();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					turn_angle_flag = 0;
					turn_flag = 0;
					basespeed = 280;
				}
			}
			break;
	}
}

void Task_2(void)
{
	switch(workstep)
	{
		case 0: 
			pid_Init(&trackLine1, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			lap_flag = 0;
			lap_count = 0;
			turn_angle_flag = 0;
			pid_flag = 0;
			basespeed = 260;
			workstep++;
			break;

		case 1:
			if(lap_count >= target_lap)  // ✅ 圈数达成，直接停车
			{
				motor_stop();          // 停止电机
				params_clear();        // 清除 PID 状态等
				clear_distance1();
				break;                 // 不再执行后续逻辑
			}

			// ✅ 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Get_Light_TTL();
				pid_flag = TRACK1_PID;

				if(turn_angle_flag)
				{
					turn_flag = 1;
					clear_distance1();  // ✅ 进入拐角转弯，也清零距离
				}
			}
			else  // 拐角转弯阶段
			{
				get_distance1();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					turn_angle_flag = 0;
					turn_flag = 0;
					basespeed = 260;
				}
			}
			break;
	}
}


