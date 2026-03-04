#ifndef __KEY_H
#define __KEY_H

#include "ti_msp_dl_config.h" 

#define KEY_NUM 3 

typedef enum {
    lap_num_key = 0, 
    task_num_key,
	total_start_key	
} KEY_Type_e;

typedef enum {
    KEY_RELEASED = 0,
    KEY_PRESSED
} KEY_State_e;

typedef enum {
    KEY_LOW_LEVEL_PRESS = 0,
    KEY_HIGH_LEVEL_PRESS,
} KEY_PressLevel_e;

typedef enum {
    KEY_MODE_NORMAL = 0,     // 单次触发
    KEY_MODE_CONTINUOUS      // 连按模式
} KEY_Mode_e;

/* 静态参数：硬件连接属性 */
typedef struct {
    GPIO_Regs* GPIO_Port;        // MSPM0 端口类型 (GPIOA/GPIOB)
    uint32_t GPIO_Pin;           // MSPM0 引脚位掩码
    KEY_PressLevel_e PressLevel; // 按下时的有效电平
    KEY_Mode_e Mode;             // 检测模式
} KeyStaticParam_s;

/* 运行参数：实时状态属性 */
typedef struct {
    KEY_State_e LastState;       // 上次状态（用于边沿检测）
    uint32_t LastTick;           // 用于消抖或长按计时
} KeyRunningParam_s;

typedef struct {
    KeyStaticParam_s StaticParam;
    KeyRunningParam_s RunningParam;
} KEYInstance;

/* 外部调用接口 */
void KeyDeviceInit(void);
uint8_t Key_GetNum(KEY_Type_e KeyType);

#endif