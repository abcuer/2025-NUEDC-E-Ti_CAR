#include "headfile.h"
#include "dist.h"

float carL_dis = 0;
float carR_dis = 0;

/*** 直接获取总距离  ***/
void GetDistance(void)
{
	carR_dis = WHEEL_DIST*1000.0f * -encoder_right_count;
	carL_dis = WHEEL_DIST*1000.0f * encoder_left_count;
}

void ClearDistance(void)
{
	carL_dis = 0;
	carR_dis = 0;
	encoder_left_count = 0;
	encoder_right_count = 0;
}
