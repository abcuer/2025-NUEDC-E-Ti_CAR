#ifndef __DIST_H
#define __DIST_H

#define PI 3.14159265
#define MOTOR_REDUCTION_RATIO 28.0f   // 减速比
#define ENCODER_RESOLUTION 730.0f     // 转一圈脉冲数：编码器线数*几倍频*减速比
									  // 13*2*28 = 728
#define WHEEL_DIAMETER 0.065f		  // 轮子直径D
#define WHEEL_CIRCUMFERENCE (PI * WHEEL_DIAMETER)  // 轮子周长=PI*D
#define WHEEL_DIST (WHEEL_CIRCUMFERENCE / ENCODER_RESOLUTION) // 轮子单脉冲前进距离
															  // 3.1416*0.065/730=0.0002797 米/脉冲
															  //                 ≈ 0.2797 毫米/脉冲		


void GetDistance(void);      // 直接获取一段距离
void ClearDistance(void);	   // 清除获取的距离

extern float carL_dis;
extern float carR_dis;

#endif