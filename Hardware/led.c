#include "led.h"

static LEDInstance led[LED_NUM];

/**
 * @brief 根据当前状态更新GPIO电平
 */
static void UpdatePinLevel(LED_Type_e LedType)
{
    LEDInstance *instance = &led[LedType];

    bool isLogicOn = (instance->RunningParam.CurrentMode == LED_ON);
    bool shouldPinHigh = (instance->StaticParam.ActiveLevel == LED_HIGH_LEVEL_ON) ? isLogicOn : !isLogicOn;

    if (shouldPinHigh) {
        DL_GPIO_setPins(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin);
    } else {
        DL_GPIO_clearPins(instance->StaticParam.GPIO_Port, instance->StaticParam.GPIO_Pin);
    }
}

/**
 * @brief 设置LED状态
 */
void SetLedMode(LED_Type_e LedType, LED_Mode_e Mode)
{
    if (LedType >= LED_NUM) return;

    if (Mode == LED_TOGGLE)
    {
        DL_GPIO_togglePins(led[LedType].StaticParam.GPIO_Port, led[LedType].StaticParam.GPIO_Pin);
        
        // 同步内部状态记录
        led[LedType].RunningParam.CurrentMode = 
            (led[LedType].RunningParam.CurrentMode == LED_ON) ? LED_OFF : LED_ON;
    }
    else
    {
        led[LedType].RunningParam.CurrentMode = Mode;
        UpdatePinLevel(LedType);
    }
}

/**
 * @brief 初始化单个LED
 */
static void Led_Init(LedStaticParam_s *config, LED_Type_e LedType)
{
    if (LedType >= LED_NUM) return; 
    led[LedType].StaticParam = *config;
    // GPIO 初始化已在 SYSCFG_DL_GPIO_init() 中完成
    SetLedMode(LedType, LED_OFF);
}

/**
 * @brief 硬件设备初始化映射
 */
void LedDeviceInit(void)
{ 
    LedStaticParam_s config;

    // 蓝色 LED 配置
    config.GPIO_Port = LED_PORT;
    config.GPIO_Pin = LED_BLUE_PIN;
    config.ActiveLevel = LED_HIGH_LEVEL_ON; // 根据你的代码中 PULL_DOWN 推测为高有效
    Led_Init(&config, LED_BLUE);

    // 绿色 LED 配置
    config.GPIO_Port = LED_PORT;
    config.GPIO_Pin = LED_GREEN_PIN;
    config.ActiveLevel = LED_HIGH_LEVEL_ON;
    Led_Init(&config, LED_GREEN);
}
