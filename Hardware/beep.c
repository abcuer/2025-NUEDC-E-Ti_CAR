#include "beep.h"

static BEEPInstance beep[BEEP_NUM];

/**
 * @brief 根据当前状态更新 GPIO 电平 (适配 MSPM0)
 */
static void UpdateBeepPinLevel(BEEP_Type_e BeepType)
{
    BEEPInstance *instance = &beep[BeepType];
    
    // 逻辑：如果模式为 ON，且为低电平触发，则清除引脚（输出低）
    bool shouldPinSet; 
    
    if (instance->RunningParam.CurrentMode == BEEP_ON) {
        // 开启状态：如果是高有效则置位，低有效则复位
        shouldPinSet = (instance->StaticParam.ActiveLevel == BEEP_HIGH_LEVEL_ON);
    } else {
        // 关闭状态：逻辑与开启相反
        shouldPinSet = (instance->StaticParam.ActiveLevel == BEEP_LOW_LEVEL_ON);
    }

    if (shouldPinSet) {
        DL_GPIO_setPins(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin);
    } else {
        DL_GPIO_clearPins(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin);
    }
}

/**
 * @brief 设置蜂鸣器开关状态
 */
void SetBeepMode(BEEP_Type_e BeepType, BEEP_Mode_e Mode)
{
    if (BeepType >= BEEP_NUM) return;
    
    beep[BeepType].RunningParam.CurrentMode = Mode;
    UpdateBeepPinLevel(BeepType);
}

/**
 * @brief 单个蜂鸣器内部初始化
 */
static void Beep_Init(BeepStaticParam_s *config, BEEP_Type_e BeepType)
{
    if (BeepType >= BEEP_NUM) return; 
    
    beep[BeepType].StaticParam = *config;
    // 硬件初始化由 SYSCFG_DL_init 完成
    SetBeepMode(BeepType, BEEP_OFF);
}

/**
 * @brief 蜂鸣器设备总初始化
 */
void BeepDeviceInit(void)
{ 
    BeepStaticParam_s config;

    config.GPIO_Port = BEEP_PORT;         
    config.GPIO_Pin = BEEP_ONE_PIN; 
    config.ActiveLevel = BEEP_LOW_LEVEL_ON; 
    
    Beep_Init(&config, BEEP);
}
