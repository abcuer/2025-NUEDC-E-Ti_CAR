#include "headfile.h"
#include "distance.h"

float carL_dis = 0;
float carR_dis = 0;


/*** 直接获取总距离
***/
void get_distance1(void)
{
	carR_dis = WHEEL_DIST*1000.0f * -Get_Encoder_countB;
	carL_dis = WHEEL_DIST*1000.0f * Get_Encoder_countA;
}

void clear_distance1(void)
{
	carL_dis = 0;
	carR_dis = 0;
	Get_Encoder_countA = 0;
	Get_Encoder_countB = 0;
}

static int lastCountA = 0;
static int lastCountB = 0;

/*** 周期性获取距离
	放在定时器中断中: 可计算10ms内小车行驶距离
***/

// 例如在 10ms 周期定时器中
/*		void Timer_ISR(void)
		{
			distance2 += get_distance();
		}
*/
float get_distance2(void)
{
    int currentCountA = Get_Encoder_countA;
    int currentCountB = Get_Encoder_countB;

    int deltaA = abs(currentCountA - lastCountA);
    int deltaB = abs(currentCountB - lastCountB);

    lastCountA = currentCountA;
    lastCountB = currentCountB;

    float deltaDis_mm = WHEEL_DIST*1000.0f * ((float)deltaA + (float)deltaB) / 2.0f;

    return deltaDis_mm / 10.0f; // 返回单位厘米
}

//float dist_pid_control(float dist_tar)
//{
//	float pulse_tar = dist_tar / Wheel_dist;
//	float puise = (fabs(Get_Encoder_countB) + fabs(Get_Encoder_countA)) / 2.0;
//	dist.now = puise;
//	dist.target = pulse_tar;
//	pid_cal(&dist);
//	return dist.out;
////	if(Increase<2)
////	{
////		motor_stop();
////	} 
//}	
pid_t dist;

	
void dist2_pid_control(float dist_tar_cm)  // 以“厘米”为单位
{
	//目标脉冲 = 目标行驶距离 ÷ 每个脉冲对应的轮子前进距离
    float pulse_tar = dist_tar_cm / (100.0f * WHEEL_DIST);
    float puise = (abs(Get_Encoder_countB) + abs(Get_Encoder_countA)) / 2.0;
    dist.now = puise;
    dist.target = pulse_tar;
    pid_cal(&dist);
    Motor_left_Control(dist.out);
    Motor_right_Control(dist.out);
    // 误差很小就停车
    if(fabs(dist.target - dist.now) < 2.0f)  // 脉冲误差阈值
    {
        motor_stop();
    }
}

/**
 * @brief 位移PID控制函数，让小车移动指定距离
 * @param dist_tar_cm 目标位移（单位：厘米）
 * @return PID输出值（通常用于控制电机PWM）
 */
 
float dist_pid_control(float dist_tar_cm)
{
    // 将目标距离从 cm 转换为 m，并计算目标对应的脉冲数（考虑减速比）
    float pulse_tar = (dist_tar_cm / 100.0f) / WHEEL_DIST;
    // 获取当前小车两轮的平均编码器值（即当前位移对应的脉冲数）
    float puise = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    dist.now = puise;
    dist.target = pulse_tar;
    pid_cal(&dist);
	if(fabs(dist.out) < 5.0f) dist.out = 0;  // 避免微抖动
    return dist.out;
}

void distloop_pid_control(float dist_tar, int base)
{
	int speed_tar = dist_pid_control(dist_tar);
	speed_pid_control(speed_tar, base);
    if(fabs(dist.target - dist.now) < 50.0f)  // 脉冲误差阈值
    {
       motor_stop(); // 连续5次满足条件才停
    }
}
/*  轮子一圈脉冲：编码器线序*倍频*减速比
	13*2*28 = 728
	每脉冲度数 = 360 / 电机旋转一圈的编码器脉冲数
*/
/** 使用编码器进行pid转向 **/
pid_t encoder_to_ang;
float One_Wheel_angle = 360.0f / 728.0f;

void encoder_to_angle(float angle_tar)
{
    encoder_to_ang.target = angle_tar / One_Wheel_angle;
    encoder_to_ang.now = (Get_Encoder_countB - Get_Encoder_countA) / 2.0f;
    
    float error = encoder_to_ang.target - encoder_to_ang.now;

    // 判断是否到达目标角度
    if (fabsf(error) < 2.0f) // 允许误差小于 2 脉冲（视精度而定）
    {
        Motor_left_Control(0);   // 停止电机
        Motor_right_Control(0);
        return; // 不再执行 PID 控制
    }
    pid_cal(&encoder_to_ang);
    pidout_limit(&encoder_to_ang, 3000);
    Motor_left_Control( - encoder_to_ang.out);
    Motor_right_Control( + encoder_to_ang.out);
}

