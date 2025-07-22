#include "headfile.h"

// 寻迹环
pid_t trackLine;
pid_t trackLine2;

float left[4]  = {0.25, 0.5, 0.75, 1.0};  // L1 ~ L4
float right[4] = {-0.25, -0.5, -0.75, -1.0}; // R1 ~ R4


void track_pid_control(float targetValue, float basespeed)
{ 	
	Gray_Read();
	float sum = R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4;
	if (sum < 0.001f) sum = 1.0f; // 或者其他默认值，防止除零
	float currentValue = (L4 * left[3] + L3 * left[2] + L2 * left[1] + L1 * left[0] + R1 * right[0] + R2 * right[1] + R3 * right[2] + R4 * right[3]) / sum;
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	Motor_left_Control(basespeed - trackLine.out);
	Motor_right_Control(basespeed + trackLine.out);
}

int track2_pid_control(float targetValue)
{
	Gray_Read();
	float sum = R1 + R2 + R3 + R4 + L1 + L2 + L3 + L4;
	if (sum < 0.001f) sum = 1.0f; // 或者其他默认值，防止除零
	float currentValue = (L4 * 1.0 + L3 * 0.75 + L2 * 0.5 + L1 * 0.25 + R1 * (-0.25) + R2 * (-0.5) + R3 * (-0.75) + R4 * (-1.0)) / sum;
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	return trackLine.out;
}

/*  串级寻迹环  */
/* track_tar一般为0 */
void trackloop_pid_control(float track_tar, int base)
{
	int speed_tar = track2_pid_control(track_tar);
	speed_pid_control(speed_tar, base);
}

// 模式匹配替代 currentValue 的估算值（仅在特定模式下使用）
int match_gray_pattern(uint8_t pattern, float *currentValue)
{
    switch (pattern)
    {
        case 0b00011000: *currentValue = 0.0f;   return 1;  // 完美居中
        case 0b00110000: // 小偏右
        case 0b00100000: *currentValue = -0.4f;  return 1;
															// 中偏右
        case 0b01100000: *currentValue = -0.7f;  return 1;
        case 0b01000000: *currentValue = -1.0f;  return 1;

        case 0b10000000: *currentValue = -1.5f;  return 1;  // 大偏右
															// 小偏左
        case 0b00001100: 
        case 0b00000100: *currentValue = 0.4f;   return 1;
															// 中偏左
        case 0b00000011: *currentValue = 0.7f;   return 1;
        case 0b00000010: *currentValue = 1.0f;   return 1;

        case 0b00000001: *currentValue = 1.5f;   return 1;  // 大偏左

        default: *currentValue = 0.0f;   return 1;
    }
}

float track_midde_line(float targetValue)
{
	Gray_Read();
	float currentValue = 0;
	uint8_t pattern = (R4 << 7) | (R3 << 6) | (R2 << 5) | (R1 << 4) | (L1 << 3) | (L2 << 2) | (L3 << 1) | L4;
	match_gray_pattern(pattern, &currentValue);
	trackLine.now = currentValue;
	trackLine.target = targetValue;
	pid_cal(&trackLine);
	// 电机输出限幅
	pidout_limit(&trackLine, 800);
	return trackLine.out;
}

void trackloop2_pid_control(float track_tar, int base)
{
	int speed_tar = track_midde_line(track_tar);
	speed_pid_control(speed_tar, base);
}
