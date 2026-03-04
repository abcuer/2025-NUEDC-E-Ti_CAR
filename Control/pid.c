#include "pid.h"
#include "speed.h"
#include "track.h"

void PID_Update(PID_Struct *pid, uint32_t mode, float p, float i, float d)
{
	pid->mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

void PID_Reset(PID_Struct *pid)
{
    pid->error[0] = 0;
    pid->error[1] = 0;
    pid->error[2] = 0;
    pid->pout = 0;
    pid->iout = 0;
    pid->dout = 0;
    pid->out = 0;
    pid->now = 0;
    pid->target = 0;
}

void PID_Calculate(PID_Struct *pid)
{
	pid->error[0] = pid->target - pid->now;

	if(pid->mode == DELTA_PID)  
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->mode == POSITION_PID)  
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void PID_OutPutLimit(PID_Struct *pid, float duty)
{
	if(pid->out >= duty)	pid->out = duty;
	if(pid->out <= -duty) 	pid->out = -duty;
}

uint8_t pid_flag = 0;

void PID_Select(void)
{
	switch(pid_flag)
	{
		case TURN_90_PID:
			turn_90_control(basespeed, bias);
			break;
		case TRACK_PID:
			TrackPidCtrl(basespeed);
			break;
		case TRACKLOOP_PID:
			TrackCascadeCtrl(0, basespeed);
			break;
		default:
			break;
	}
}


