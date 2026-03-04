#ifndef __TASK_H
#define __TASK_H
#include "stdint.h"

#define TURN_DISTANCE 228

void FirstTask(void);
void SecondTask(void);

extern uint8_t turn_flag;
extern uint8_t corner_detected;
extern uint8_t lap_count;

extern uint16_t bias;
extern float basespeed;

#endif