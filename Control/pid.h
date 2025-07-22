#ifndef __PID_h_
#define __PID_h_
#include "headfile.h"

enum
{
  POSITION_PID = 0, 
  DELTA_PID,         
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;


extern pid_t trackLine;
extern pid_t trackLine2;
extern pid_t angle;
extern pid_t dist;
extern pid_t encoder_to_ang;

void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d);
void pid_clear(pid_t *pid);
void pid_cal(pid_t *pid);
void pidout_limit(pid_t *pid, float duty);
void PID_select(void);

#endif
