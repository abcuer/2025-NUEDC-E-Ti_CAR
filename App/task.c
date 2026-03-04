#include "headfile.h"

uint8_t workstep = 0;		// 工作步骤
uint8_t turn_flag = 0;		// 转向标志
uint8_t lap_count = 0; 	// 行驶圈数
uint8_t corner_detected = 0;	// 触发转向标志
uint8_t corner_cnt = 0;	 // 路段/拐角计次

uint16_t bias = 0;	// 转角环补偿值
float basespeed = 0;	// 行驶速度

static void Task_Reset(void)
{
	task_num = 0;
	corner_cnt = 0;
    lap_count = 0;
    corner_detected = 0;
	turn_flag = 0;
    pid_flag = 0;
    basespeed = 0;
	lap_num = 0;
	workstep = 0;
}

/**
 * @brief 赛道拐角与圈数检测处理函数
 * @note  通过灰度传感器检测黑线，识别转弯标志并计数
 */
static void Track_DetectCorner(void)
{
	static int black_cnt = 0;      // 连续扫描到黑线的次数
    static int timer_ms = 0;       // 软件消抖计时器
    static int is_latched = 0;     // 防止单次拐角重复触发

    // 更新灰度传感器原始数据
    Gray_Update();

    // 1. 检测是否处于黑线/拐角标志区
    if (gray.left[2] && gray.left[1] && gray.left[0])
    {
        black_cnt++;
    }
    else
    {
        black_cnt = 0;
        is_latched = 0; // 离开黑线区域，重置锁存
    }

    timer_ms++;
    // 触发判断逻辑
    if (black_cnt >= 3 && !is_latched && timer_ms >= 100)
    {
        corner_detected = 1;  
        corner_cnt++;          
        is_latched = 1;       // 锁定当前触发，直到离开黑线
        timer_ms = 0;         // 重置消抖时间

        // 3. 圈数计算逻辑
        if(task_num == 1)
        {
            if (corner_cnt >= 4)
            {
                lap_count++;  // 圈数+1
                corner_cnt = 0;
            }
        } 
        else if(task_num == 2)
        {
            if (corner_cnt >= 5)
            {
                lap_count++;  // 圈数+1
                corner_cnt = 1; 
            }
        }
        // 触发声光反馈
        SoundLightRun();
    }
}


void FirstTask(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Update(&track_pid, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			lap_count = 0;
			corner_detected = 0;
			pid_flag = 0;
			basespeed = 280;
			workstep++;
			break;

		case 1:
			if(lap_count >= lap_num)
			{
				if(!turn_flag)  // 首次进入转弯阶段
				{
					turn_flag = 1;
					ClearDistance();  // 清除累计编码器距离
				}

				GetDistance();  // 实时更新距离
				bias = 190;
				basespeed = 20;
				pid_flag = TURN_90_PID;

				// 距离判断是否完成90度转弯
				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					Motor_Stop();
					Task_Reset();
					SetLedMode(LED_BLUE, LED_ON);  // 圈数完成，转弯完成
				}
				break;
			}

			// 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Track_DetectCorner();
				pid_flag = TRACK_PID;

				if(corner_detected)
				{
					turn_flag = 1;
					ClearDistance();  // 进入拐角转弯，也清零距离
				}
			}
			else  // 拐角转弯阶段
			{
				GetDistance();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					corner_detected = 0;
					turn_flag = 0;
					basespeed = 280;
				}
			}
			break;
	}
}

void SecondTask(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Update(&track_pid, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			corner_cnt = 0;
			lap_count = 0;
			corner_detected = 0;
			pid_flag = 0;
			basespeed = 260;
			workstep++;
			break;

		case 1:
			if(lap_count >= lap_num)  // 圈数达成，直接停车
			{
				Motor_Stop();          
				Task_Reset();    
				ClearDistance();
				break;                 // 不再执行后续逻辑
			}

			// 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Track_DetectCorner();
				pid_flag = TRACK_PID;

				if(corner_detected)
				{
					turn_flag = 1;
					ClearDistance();  // 进入拐角转弯，也清零距离
				}
			}
			else  // 拐角转弯阶段
			{
				GetDistance();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(fabs(carR_dis) >= TURN_DISTANCE)
				{
					corner_detected = 0;
					turn_flag = 0;
					basespeed = 260;
				}
			}
			break;
	}
}


