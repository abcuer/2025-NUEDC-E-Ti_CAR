#ifndef _speed_h
#define _speed_h

void speed_cal(float filter_alpha);
int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
/***  串级处理用的速度环  ***/
void speed_pid_control(int speed_tar, int base);
 /***  速度环转向90度  ***/
void turn_90_control(int speed_tar, int offset);

#endif