#ifndef __SPEED_H
#define __SPEED_H

#define MaxPWM 1220

typedef struct{
	float kp;
	float ki;
} SPEED_PID_Struct;

void GetSpeed(float filter_alpha);
int LeftSpeedPidCtrl(int target, int current);
int RightSpeedPidCtrl(int target, int current);

void SpeedPidCtrl(int tar, int base);
void turn_90_control(int tar, int offset);

extern float left_speed;
extern float right_speed;

#endif