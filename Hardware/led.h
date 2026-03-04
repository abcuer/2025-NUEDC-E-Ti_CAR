#ifndef __LED_H
#define __LED_H
#include "ti_msp_dl_config.h"

#define LED_NUM 2

typedef enum
{
    LED_BLUE = 0,
    LED_GREEN
} LED_Type_e;

typedef enum
{
    LED_OFF = 0,
    LED_ON,
    LED_TOGGLE
} LED_Mode_e;

typedef enum
{
    LED_LOW_LEVEL_ON = 0,
    LED_HIGH_LEVEL_ON,
} LED_ActiveLevel_e;

typedef struct
{
    GPIO_Regs* GPIO_Port;      // MSPM0 使用 GPIO_Regs*
    uint32_t GPIO_Pin;         // MSPM0 使用 uint32_t 位掩码
    LED_ActiveLevel_e ActiveLevel; 
} LedStaticParam_s;

typedef struct
{
    LED_Mode_e CurrentMode;
} LedRunningParam_s;

typedef struct
{
    LedStaticParam_s StaticParam;
    LedRunningParam_s RunningParam;
} LEDInstance;

/* 函数声明 */
void LedDeviceInit(void);
void SetLedMode(LED_Type_e LedType, LED_Mode_e Mode);

#endif
