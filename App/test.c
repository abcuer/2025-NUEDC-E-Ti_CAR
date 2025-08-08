#include "headfile.h"

void test(void)
{
		//初始化传感器，不带黑白值
		No_MCU_Ganv_Sensor_Init_Frist(&sensor);
		No_Mcu_Ganv_Sensor_Task_Without_tick(&sensor);
		Get_Anolog_Value(&sensor,Anolog);
	//此时打印的ADC的值，可用通过这个ADC作为黑白值的校准
	//也可以自己写按键逻辑完成一键校准功能
		delay_ms(100);
	//得到黑白校准值之后，初始化传感器
		No_MCU_Ganv_Sensor_Init(&sensor,white,black);
}

void test1(void)
{
	//有时基传感器常规任务，包含模拟量，数字量，归一化量
//			No_Mcu_Ganv_Sensor_Task_With_tick(&sensor)
	//获取传感器数字量结果(只有当有黑白值传入进去了之后才会有这个值！！)
//	Digtal=Get_Digtal_For_User(&sensor);
//	printf("Digtal %d-%d-%d-%d-%d-%d-%d-%d\r\n",(Digtal>>0)&0x01,(Digtal>>1)&0x01,(Digtal>>2)&0x01,(Digtal>>3)&0x01,(Digtal>>4)&0x01,(Digtal>>5)&0x01,(Digtal>>6)&0x01,(Digtal>>7)&0x01);
	Gray_Read();
	printf("%d %d %d %d %d %d %d %d\r\n", L4, L3, L2, L1, R1, R2, R3, R4);
	
	//获取传感器模拟量结果(有黑白值初始化后返回1 没有返回 0)
//	if(Get_Anolog_Value(&sensor,Anolog)){
//	printf("Anolog %d-%d-%d-%d-%d-%d-%d-%d\r\n",Anolog[0],Anolog[1],Anolog[2],Anolog[3],Anolog[4],Anolog[5],Anolog[6],Anolog[7]);
//	}
	
	//获取传感器归一化结果(只有当有黑白值传入进去了之后才会有这个值！！有黑白值初始化后返回1 没有返回 0)
//	if(Get_Normalize_For_User(&sensor,Normal)){
//	printf("Normalize %d-%d-%d-%d-%d-%d-%d-%d\r\n",Normal[0],Normal[1],Normal[2],Normal[3],Normal[4],Normal[5],Normal[6],Normal[7]);
//	}
	//经典版理论性能1khz，只需要delay1ms，青春版100hz，需要delay10ms，否则不能正常使用
	delay_ms(1000);
}

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


//void test(void)
//{
//	pid_flag = TURN_90_PID;
//  bias = 30;
//	basespeed = 20;
//}


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