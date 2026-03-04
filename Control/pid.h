#ifndef __PID_H
#define __PID_H

#include "stdint.h"
#include "task.h"

enum
{
  POSITION_PID = 0, 
  DELTA_PID,         
};

typedef enum
{
	TURN_90_PID = 0,
	TRACK_PID,
	TRACKLOOP_PID 
}PidSet_e;

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t mode;

}PID_Struct;

void PID_Update(PID_Struct *pid, uint32_t mode, float p, float i, float d);
void PID_Reset(PID_Struct *pid);
void PID_Calculate(PID_Struct *pid);
void PID_OutPutLimit(PID_Struct *pid, float duty);

void PID_Select(void);

extern uint8_t pid_flag;

#endif
