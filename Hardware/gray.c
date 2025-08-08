#include "headfile.h"

#define LineFlagTime 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

int8_t L4,L3,L2,L1,R1,R2,R3,R4;

//void Gray_Read(void) 
//{
//	L3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 1 : 0;
//	L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 1 : 0;
//	L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
//	M  = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_M_PIN) ? 1 : 0;
//	R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 1 : 0;
//	R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 1 : 0;
//	R3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 1 : 0;
//}

void Gray_Read(void) 
{
	No_Mcu_Ganv_Sensor_Task_Without_tick(&sensor);
	Digtal=Get_Digtal_For_User(&sensor);
	L4 = !((Digtal >> 0) & 0x01);
	L3 = !((Digtal >> 1) & 0x01);
	L2 = !((Digtal >> 2) & 0x01);
	L1 = !((Digtal >> 3) & 0x01);
	R1 = !((Digtal >> 4) & 0x01);
	R2 = !((Digtal >> 5) & 0x01);
	R3 = !((Digtal >> 6) & 0x01);
	R4 = !((Digtal >> 7) & 0x01);
}

void Sensor_Calibration(No_MCU_Sensor *sensor)
{
    static uint8_t last_key_state = 1;  // 上次按键状态
    static uint8_t calib_step = 0;      // 校准步骤（必须是 static）
    uint8_t curr_state = DL_GPIO_readPins(KEY_task_PORT, KEY_task_PIN);  // 当前按键状态

    // 检测按键下降沿（从 1 到 0）
    if (last_key_state == 1 && curr_state == 0)
    {
        delay_ms(40);  
        curr_state = DL_GPIO_readPins(KEY_task_PORT, KEY_task_PIN);
        if (curr_state == 0)
        {
            if (calib_step == 0)
            {
				LED_Blue_ON();
                // 第一次按键：白色环境
                Get_Anolog_Value(sensor, white);
				delay_ms(1000);
				LED_Blue_OFF();
                calib_step = 1;
            }
            else if (calib_step == 1)
            {
                // 第二次按键：黑色环境
				LED_Green_ON();
                Get_Anolog_Value(sensor, black);
				delay_ms(1000);
				LED_Green_OFF();
                No_MCU_Ganv_Sensor_Init(sensor, white, black);
                calib_step = 0;
            }
        }
    }

    last_key_state = curr_state;
}


//void Sensor_OneKey_Calibration(No_MCU_Sensor *sensor)
//{
//    static uint8_t last_key_state = 1;  // 按键上次状态
//	uint8_t calib_step = 0;
//    uint8_t curr_state = DL_GPIO_readPins(KEY_task_PORT, KEY_task_PIN);

//    // 检测按键下降沿
//    if (last_key_state == 1 && curr_state == 0)
//    {
//        delay_ms(50); // 简单防抖
//        curr_state = DL_GPIO_readPins(KEY_task_PORT, KEY_task_PIN);
//        if (curr_state == 0)
//        {
//            if (calib_step == 0)
//            {
//                Get_Anolog_Value(sensor, white);
//                calib_step = 1;
//            }
//            else if (calib_step == 1)
//            {
//                Get_Anolog_Value(sensor, black);

//                // 完成校准
//                No_MCU_Ganv_Sensor_Init(sensor, white, black);
//                calib_step = 0;
//            }
//        }
//    }

//    last_key_state = curr_state;
//}


void Get_Light_TTL(void)
{
	Gray_Read();
    static int full_black_count = 0;
    static int debounce_time = 0;
    static int lap_detected = 0;

    debounce_time++;

    // 检测是否全黑（经过终点线）
    if (L3 && L2 && L1)
    {
        full_black_count++;
    }
    else
    {
        full_black_count = 0;
        lap_detected = 0; // 允许重新检测下一圈
    }

    if (full_black_count >= 3 && !lap_detected && debounce_time >= 100)
    {
		turn_angle_flag = 1;
        lap_flag++;          // 拐角
        lap_detected = 1;     // 防止连续触发
        debounce_time = 0;

		if(Task == 1)
		{
			if (lap_flag >= 4)   // 4个拐角
			{
				lap_count++;    // 圈数+1
				lap_flag = 0;
			}
		} 
		else if(Task == 2)
		{
			if (lap_flag >= 5)   // 5个拐角
			{
				lap_count++;    // 圈数+1
				lap_flag = 1;
			}
		}
		SoundLight();
    }
} 
