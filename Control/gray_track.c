#include "headfile.h"


pid_t trackLine1;   // 单级寻迹环
pid_t trackLine2;	// 串级寻迹环

float left[4]  = {-1,-2, -3, -4};  // L1 ~ L4
float right[4] = {1, 2, 3, 4}; // R1 ~ R4

/***** 单级寻迹环 ****/
void track1_pid_control(float targetValue, float basespeed)
{ 	
	Gray_Read();
	float sum = L4 + L3 + L2 + L1 + R1+ R2 + R3 + R4;
	if (sum < 0.001f) sum = 1.0f; // 或者其他默认值，防止除零
	float currentValue = (L4 * left[3] + L3 * left[2] + L2 * left[1] + L1 * left[0] + R1 * right[0] + R2 * right[1] + R3 * right[2] + R4 * right[3]) / sum;
	trackLine1.now = currentValue;
	trackLine1.target = targetValue;
	pid_cal(&trackLine1);
	// 电机输出限幅
	pidout_limit(&trackLine1, 1000);
	Motor_left_Control(basespeed - trackLine1.out);
	Motor_right_Control(basespeed + trackLine1.out);
}

/***** 串级寻迹环 ****/
int track2_pid_control(float targetValue)
{
	Gray_Read();
	float sum = L4 + L3 + L2 + L1 + R1+ R2 + R3 + R4;
	if (sum < 0.001f) sum = 1.0f; // 或者其他默认值，防止除零
	float currentValue = (L4 * left[3] + L3 * left[2] + L2 * left[1] + L1 * left[0] + R1 * right[0] + R2 * right[1] + R3 * right[2] + R4 * right[3]) / sum;
	trackLine2.now = currentValue;
	trackLine2.target = targetValue;
	pid_cal(&trackLine2);
	// 电机输出限幅
	pidout_limit(&trackLine2, 1000);
	return trackLine2.out;
}

/*  串级寻迹环  */
/* track_tar一般为0 */
void trackloop_pid_control(float track_tar, int base)
{
	Gray_Read();
	int speed_tar = track2_pid_control(track_tar);
	speed_pid_control(speed_tar, base);
}
