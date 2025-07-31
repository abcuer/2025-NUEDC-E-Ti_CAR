/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "headfile.h"

uint8_t Task = 0;
uint8_t start_flag = 0;
uint8_t first_flag = 0;
float basespeed = 0;

int main(void)
{
	board_init(); // 延迟 串口
//	HC05_Init();
	encoder_Init();
	timer0_init();
	timer1_init();
	
	pid_Init(&trackLine1, POSITION_PID, 155, 0, 40);  // 单级寻迹环
	pid_Init(&trackLine2, POSITION_PID, 6, 0, 30);  // 串级寻迹环

	while(1) 
	{   
		Task_select();
	}
}


// pid控制
void TIMER_0_INST_IRQHandler(void)   //PID运算  10ms  优先级最高
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		if(DL_TIMER_IIDX_ZERO) 
		{	
			speed_cal(0.2); 
			PID_select();
		}
	}
}

void TIMER_1_INST_IRQHandler(void)	// 声光检测  10ms  优先级高
{
	if(DL_TimerG_getPendingInterrupt(TIMER_1_INST))
	{
		if(DL_TIMER_IIDX_LOAD)
		{	
			if (Task == 1 && first_flag == 0)   capture_initial_yaw();
			UpdateSoundLight();
		}
	}
}


