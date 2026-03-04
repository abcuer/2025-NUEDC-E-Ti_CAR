#ifndef _BEEP_H
#define _BEEP_H

#include "ti_msp_dl_config.h" 

#define BEEP_NUM 1

typedef enum
{
    BEEP = 0,
} BEEP_Type_e;

typedef enum
{
    BEEP_OFF = 0,
    BEEP_ON
} BEEP_Mode_e;

typedef enum
{
    BEEP_LOW_LEVEL_ON = 0, // 低电平开启
    BEEP_HIGH_LEVEL_ON,    // 高电平开启
} BEEP_ActiveLevel_e;

typedef struct
{
    GPIO_Regs* GPIO_Port;      // MSPM0 端口类型
    uint32_t GPIO_Pin;         // MSPM0 引脚位掩码
    BEEP_ActiveLevel_e ActiveLevel; 
} BeepStaticParam_s;

typedef struct
{
    BEEP_Mode_e CurrentMode;
} BeepRunningParam_s;

typedef struct
{
    BeepStaticParam_s StaticParam;
    BeepRunningParam_s RunningParam;
} BEEPInstance;

/* 外部调用接口 */
void BeepDeviceInit(void);
void SetBeepMode(BEEP_Type_e BeepType, BEEP_Mode_e Mode);

#endif