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
#define ANGLE_PID 	2
#define TRACK_PID 	3
#define TRACK_MIDDLELINE 	4

extern uint8_t motor_left_dir;
extern uint8_t motor_right_dir;
extern int Get_Encoder_countA;
extern int Get_Encoder_countB;
extern float speedA;
extern float speedB;
extern float carL_dis;
extern float carR_dis;

extern float basespeed;
extern uint8_t Task;
extern uint8_t first_flag;
extern uint8_t start_flag;
extern int16_t Line_flag;
extern float angle_initial;
extern int16_t baisetime;
extern uint8_t workstep;

extern uint8_t pid_flag;
extern int speed_tar;
extern int angle_tar;

//extern uint8_t hc05_data;
//extern uint8_t hc05_flag;

extern uint32_t nowtime;

#endif