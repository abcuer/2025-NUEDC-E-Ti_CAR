#include "headfile.h"

/************************ 速度环调参 ***************************/
//void test(void)
//{
//	pid_flag = SPEED_PID;
//	speed_tar = 50;     // 比赛用的速度不需要太快
//}

/************************ 单级角度环调参 ***************************/
//void test(void)
//{
//	pid_flag = ANGLE1_PID;
//	angle_tar = 50;   
//	basespeed = 300;
//}

/************************ 串级角度环调参 ***************************/
//void test(void)
//{
//	pid_flag = ANGLE2_PID;
//	angle_tar = 50;   
//	basespeed = 50;
//}

/************************ 单级寻迹环调参 ***************************/
//void test(void)
//{
//	pid_flag = TRACK1_PID;
//   
//	basespeed = 250;
//}

/************************ 串级寻迹环调参 ***************************/
//void test(void)
//{
//	pid_flag = TRACK2_PID;
//   
//	basespeed = 0;
//}


void test(void)
{
	pid_flag = TURN_90_PID;
  bias = 30;
	basespeed = 20;
}


/************************ ICM45686 SPI读取Yaw 超声波测距 ***************************/
//void test(void)
//{
//	float ypr[3];          // 上传yaw pitch roll的值
//	IMU_getYawPitchRoll(ypr);
//	uint32_t dist = (int) Hcsr04GetLength();
//	OLED_Refresh();        // 将数据刷新到屏幕上
//    OLED_ShowString(0, 0, (u8 *)"Yaw:", 12, 1);  // 字符串显示
//    OLED_ShowFloat(36, 0, ypr[0], 3, 12, 1);        // 显示数值（最大3位整数）
//	OLED_ShowString(0, 36, (u8 *)"dist:", 12, 1);  // 字符串显示
//    OLED_ShowFloat(36, 36, dist, 3, 12, 1);        // 显示数值（最大3位整数）
//	delay_ms(10);
//}

/************************ ICM45686 SPI读取Yaw ***************************/
//void test(void)
//{
//	float ypr[3];          // 上传yaw pitch roll的值
//	IMU_getYawPitchRoll(ypr);
//    printf("%f\r\n",ypr[0]);
//}

/************************ 超声波测距 ***************************/
//void test(void)
//{
//		uint32_t dist = (int) Hcsr04GetLength();
//		printf("%dcm\r\n", dist);
//		delay_ms(10);
//}

/************************ 速度环调参 ***************************/
//void test()
//{
//	speed_tar = 30;
//	pid_flag = SPEED_PID;
//}

/************************ 速度环调参 ***************************/
//void test()
//{
//	basespeed = 250;
//	pid_flag = TRACK_MIDDLELINE;
////	printf("%.2f, %.2f\r\n", speedA, -speedB);
//}




/*   串口通讯测试
void test(void)
{
    if(hc05_flag)
    {
        switch(hc05_data)
        {
            case '1': LED_Blue_ON(); break;
            case '2': LED_Blue_OFF(); break;
            case '3': LED_Green_ON(); break;
            case '4': LED_Green_OFF(); break;
        }
        uart0_send_char(hc05_data);  // 串口发送也必须在主循环中完成
        hc05_flag = 0;
    }
}
*/
/*   PID定时器选择性测试
void test(void)
{
	printf("%.2f, %.2f, %.2f\r\n", speedA, speedB, Yaw);
	speed_tar = 30;
	pid_flag = SPEED_PID;
}
*/
/************************ OLED驱动测试 ***************************/
//void test(void)
//{
//	OLED_ShowString(0,0,(uint8_t *)"ABC",8,1);//6*8 “ABC”
//	OLED_ShowString(0,8,(uint8_t *)"ABC",12,1);//6*12 “ABC”
//	OLED_ShowString(0,20,(uint8_t *)"ABC",16,1);//8*16 “ABC”
//	OLED_ShowString(0,36,(uint8_t *)"I LOVE YOU",24,1);//12*24 “ABC”
//	OLED_Refresh();
//	delay_ms(20);
//}