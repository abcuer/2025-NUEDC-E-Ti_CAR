#include "headfile.h"

#define LineFlagTime 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

int8_t L3,L2,L1,M,R1,R2,R3;

void Gray_Read(void) 
{
	L3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 1 : 0;
	L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 1 : 0;
	L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
	M  = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_M_PIN) ? 1 : 0;
	R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 1 : 0;
	R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 1 : 0;
	R3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 1 : 0;
}

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
				SoundLight();
				lap_flag = 1;
			}
		}
    }
} 
