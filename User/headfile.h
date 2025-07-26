#ifndef _headfile_h
#define _headfile_h

#pragma once

#include "ti_msp_dl_config.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
/******************* BSP **********************/
#include "board.h"
#include "timer.h"
/***************** Hardware *******************/
#include "key.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "encoder.h"
#include "gray.h"
#include "jy901s.h"
#include "sr04.h"
#include "hc05.h"
#include "oled.h"
#include "IMU.h"
/***************** Control *******************/
#include "pid.h"
#include "speed.h"
#include "angle.h"
#include "gray_track.h"
#include "distance.h"
/***************** App ***********************/
#include "app_utils.h"
#include "app_task.h"
#include "test.h"

#define SPEED_PID 	1
#define ANGLE1_PID 	2
#define ANGLE2_PID 	3
#define TRACK1_PID 	4
#define TRACK2_PID 	5

/******** IMU *********/
extern uint32_t nowtime;

/** Speed **/
extern float speedA;
extern float speedB;
extern uint8_t motor_left_dir;
extern uint8_t motor_right_dir;

/******** pid ********/
extern uint8_t pid_flag;
extern int speed_tar;
extern int angle_tar;

/******** angle ********/
extern float angle_initial;

/******** distance ********/
extern int Get_Encoder_countA;
extern int Get_Encoder_countB;
extern float carL_dis;
extern float carR_dis;

/******** Task ********/
extern uint8_t Task;
extern float basespeed;
extern uint8_t Line_flag;
extern uint8_t first_flag;
extern uint8_t start_flag;
extern int16_t baisetime;
extern uint8_t workstep;

extern uint8_t line_flag;
extern uint8_t stop_flag;

#endif