#ifndef _gray_track_h
#define _gray_track_h

/*** 单级寻迹环 ***/
void track1_pid_control(float targetValue, float basespeed);
/*** 串级寻迹环 ***/
int track2_pid_control(float targetValue);
void trackloop_pid_control(float track_tar, int base);

/** 速度环差值寻迹 **/
//float track_midde_line(float targetValue);
//void trackloop2_pid_control(float track_tar, int base);

#endif