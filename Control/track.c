#include "headfile.h"

PID_Struct track_pid;   // 单级寻迹
PID_Struct track_loop_pid;	// 串级寻迹

Gray_Weight_Struct gray_weight =
{
	.left = {-1,-2, -3},  // L1 ~ L3
	.right = {1, 2, 3}
};
// 单级寻迹环
void TrackPidCtrl(float basespeed)
{ 	
	Gray_Update();
	float sum = gray.left[2] + gray.left[1] + gray.left[0] + gray.M + gray.right[0] + gray.right[1] + gray.right[2];
	if (sum < 0.001f) sum = 1.0f;
	float current = (gray.left[2] * gray_weight.left[2] + gray.left[1] * gray_weight.left[1] + gray.left[0] * gray_weight.left[0] + gray.M * 0.0f + gray.right[0] * gray_weight.right[0] + gray.right[1] * gray_weight.right[1] + gray.right[2] * gray_weight.right[2]) / sum;
	track_pid.now = current;
	track_pid.target = 0;
	PID_Calculate(&track_pid);
	PID_OutPutLimit(&track_pid, 1000);
	Motor_LeftCtrl(basespeed - track_pid.out);
	Motor_RightCtrl(basespeed + track_pid.out);
}

int TrackLoopPidCtrl(float target)
{
	Gray_Update();
	float sum = gray.left[2] + gray.left[1] + gray.left[0] + gray.M + gray.right[0] + gray.right[1] + gray.right[2];
	if (sum < 0.001f) sum = 1.0f;
	float current = (gray.left[2] * gray_weight.left[2] + gray.left[1] * gray_weight.left[1] + gray.left[0] * gray_weight.left[0] + gray.M * 0.0f + gray.right[0] * gray_weight.right[0] + gray.right[1] * gray_weight.right[1] + gray.right[2] * gray_weight.right[2]) / sum;
	track_loop_pid.now = current;
	track_loop_pid.target = target;
	PID_Calculate(&track_loop_pid);
	PID_OutPutLimit(&track_loop_pid, 1000);
	return track_loop_pid.out;
}
// 串级寻迹环
void TrackCascadeCtrl(float track_tar, int basespeed)
{
	int tar = TrackLoopPidCtrl(track_tar);
	SpeedPidCtrl(tar, basespeed);
}
