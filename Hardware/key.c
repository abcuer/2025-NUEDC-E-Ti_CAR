#include "key.h"
#include "delay.h" // 确保包含延时函数头文件

static KEYInstance key[KEY_NUM];

/**
 * @brief 获取原始物理电平对应的按键状态 (适配 MSPM0)
 */
static KEY_State_e GetKeyState(KEY_Type_e KeyType)
{
    KEYInstance *ins = &key[KeyType];
    
    // MSPM0 读取逻辑：readPins 返回位掩码
    uint32_t pinVal = DL_GPIO_readPins(ins->StaticParam.GPIO_Port, ins->StaticParam.GPIO_Pin);
    
    // 判断物理电平是否符合“按下”设置
    bool isPressed = (ins->StaticParam.PressLevel == KEY_LOW_LEVEL_PRESS) ? (pinVal == 0) : (pinVal != 0);
    
    return isPressed ? KEY_PRESSED : KEY_RELEASED;
}

/**
 * @brief 内部初始化函数
 */
static void Key_Init(KeyStaticParam_s *config, KEY_Type_e KeyType)
{
    if (KeyType >= KEY_NUM) return;
    
    key[KeyType].StaticParam = *config;
    // 默认初始状态为松开
    key[KeyType].RunningParam.LastState = KEY_RELEASED;
}

/**
 * @brief 按键设备总初始化
 */
void KeyDeviceInit(void)
{
    KeyStaticParam_s config;

    // 配置 KEY_TASK
    config.GPIO_Port = KEY_LapNum_PORT;
    config.GPIO_Pin = KEY_LapNum_PIN;
    config.PressLevel = KEY_LOW_LEVEL_PRESS;
    config.Mode = KEY_MODE_NORMAL;
    Key_Init(&config, lap_num_key);

    // 配置 KEY_START
    config.GPIO_Port = KEY_TaskNum_PORT;
    config.GPIO_Pin = KEY_TaskNum_PIN;
    config.PressLevel = KEY_LOW_LEVEL_PRESS;
    config.Mode = KEY_MODE_NORMAL;
    Key_Init(&config, task_num_key);
	
	config.GPIO_Port = KEY_TotalStart_PORT;
    config.GPIO_Pin = KEY_TotalStart_PIN;
    config.PressLevel = KEY_LOW_LEVEL_PRESS;
    config.Mode = KEY_MODE_NORMAL;
    Key_Init(&config, total_start_key);
}

/**
 * @brief 获取按键触发事件 (松开触发风格)
 * @return 1: 有效触发（松开瞬间）, 0: 无触发
 */
uint8_t Key_GetNum(KEY_Type_e KeyType)
{
    if (KeyType >= KEY_NUM) return 0;
    
    KEYInstance *instance = &key[KeyType];
    KEY_State_e currentState = GetKeyState(KeyType);
    uint8_t key_event = 0;

    if (currentState == KEY_RELEASED && instance->RunningParam.LastState == KEY_PRESSED)
    {
        delay_ms(40); 
        if (GetKeyState(KeyType) == KEY_RELEASED)
        {
            key_event = 1; // 触发事件
        }
    }
    
    instance->RunningParam.LastState = currentState;
    
    return key_event;
}