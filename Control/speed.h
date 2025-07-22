#ifndef _speed_h
#define _speed_h

void speed_cal(float filter_alpha);
int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
void speed_pid_control(int speed_tar, int base);
void speed2_pid_control(int speed_tar);

#endif