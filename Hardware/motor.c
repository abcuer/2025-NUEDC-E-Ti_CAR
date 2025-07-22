#include "motor.h"
#define offset 30

/*
×óÂÖ: GPIOB Pin_18¢PPin_19  PWM2(GPIOB PIn_1)
ÓÒÂÖ: GPIOB Pin_20  Pin_24 	PWM1(GPIOB Pin_2)
*/


uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

void Motor_left_duty(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        AIN1_OUT(1);
        AIN2_OUT(0);
    }
    else
    {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed ,GPIO_PWM_C0_IDX);
}

void Motor_right_duty(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        BIN1_OUT(1);
        BIN2_OUT(0);
    }
    else
    {
        BIN1_OUT(0);
        BIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed + offset,GPIO_PWM_C1_IDX);
}

void Motor_left_Control(float speed)
{
    if( motor_left_dir == 1 )
    {
        AIN1_OUT(1);
        AIN2_OUT(0);
    }
    else
    {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + offset, GPIO_PWM_C0_IDX);
}

void Motor_right_Control(float speed)
{
    if( motor_right_dir == 1 )
    {
        BIN1_OUT(1);
        BIN2_OUT(0);
    }
    else
    {
        BIN1_OUT(0);
        BIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + offset,GPIO_PWM_C1_IDX);
}

void motor_stop(void)
{
	AIN1_OUT(1);
    AIN2_OUT(1);
	
	BIN1_OUT(1);
    BIN2_OUT(1);
	
}