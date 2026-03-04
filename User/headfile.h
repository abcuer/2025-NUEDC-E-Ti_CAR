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
#include "delay.h"
#include "timer.h"
#include "uart.h"
/***************** Hardware *******************/
#include "led.h"
#include "key.h"
#include "beep.h"
#include "motor.h"
#include "encoder.h"
#include "gray.h"
#include "minipc.h"
/***************** Control *******************/
#include "speed.h"
#include "dist.h" 
#include "track.h"
#include "pid.h"
/***************** App ***********************/
#include "task.h"
#include "soundlight.h"
#include "utils.h"


#endif