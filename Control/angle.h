#ifndef _angle_h
#define _angle_h

void angle_correction(void);

/******** 单级角度环 ********/
void  angle1_pid_control(int tar);
/******** 串级角度环 ********/
int angle2_pid_control(int tar);
void angleloop_pid_control(int angle_tar, int base);

#endif