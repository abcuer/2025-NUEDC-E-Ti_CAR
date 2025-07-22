#ifndef _angle_h
#define _angle_h

void angle_correction(void);
int angle_pid_control(int tar);
void angleloop_pid_control(int angle_tar, int base);

#endif