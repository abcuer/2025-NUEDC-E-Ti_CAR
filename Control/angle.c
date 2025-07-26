#include "speed.h"
#include "pid.h"

// 角度环
pid_t angle1;    // 单级角度环
pid_t angle2;	 // 串级角度环

int16_t ang = 0;

void angle_correction(void)
{
	if(Task == 1)
	{
		if( ang > 120) ang -= 180;
		else if( ang < -120) ang += 180;
	}
	else if(Task == 3 || Task == 4)
	{
		if(workstep == 1 || workstep == 2)
		{
			if( ang > 125) ang -= 180;
			else if( ang < -125) ang += 180;
		}
		if(workstep == 3 || workstep == 4)
		{
			if( ang > 70) ang -= 180;
			else if( ang < -70) ang += 180;
		}
	}
}

/******** 单级角度环 ********/
void  angle1_pid_control(int tar)
{
	angle1.target = tar;
	ang = Yaw;
	angle_correction();
	angle1.now = ang; 
	pid_cal(&angle1);
	pidout_limit(&angle1, 1000);
	Motor_left_Control(basespeed - angle1.out);
	Motor_right_Control(basespeed + angle1.out);
}

/******** 串级角度环 ********/
int angle2_pid_control(int tar)
{
	angle2.target = tar;
	ang = Yaw;
	angle_correction();
	angle2.now = ang; 
	pid_cal(&angle2);
	pidout_limit(&angle2, 1000);
	return angle2.out;
}

//*  串级角度环  */
void angleloop_pid_control(int angle_tar, int base)
{
	int speed_tar = angle2_pid_control(angle_tar);  
	speed_pid_control(speed_tar, base);
}
