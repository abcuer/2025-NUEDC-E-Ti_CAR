#include "headfile.h"

volatile unsigned int msHcCount = 0;//ms计数
volatile float utl_dist = 0;

/******************************************************************
 * 函 数 名 称：bsp_ultrasonic
 * 函 数 说 明：超声波初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：TRIG引脚负责发送超声波脉冲串
******************************************************************/
void Ultrasonic_Init(void)
{

    //清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_2_INST_INT_IRQN);
    //使能定时器中断
    NVIC_EnableIRQ(TIMER_2_INST_INT_IRQN);

}
/******************************************************************
 * 函 数 名 称：Open_Timer
 * 函 数 说 明：打开定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
******************************************************************/
void Open_Timer(void)
{

    DL_TimerA_setTimerCount(TIMER_2_INST, 0);   // 清除定时器计数

    msHcCount = 0;

    DL_TimerA_startCounter(TIMER_2_INST);   // 使能定时器
}

/******************************************************************
 * 函 数 名 称：Get_TIMER_Count
 * 函 数 说 明：获取定时器定时时间
 * 函 数 形 参：无
 * 函 数 返 回：数据
 * 作       者：LC
 * 备       注：
******************************************************************/
uint32_t Get_TIMER_Count(void)
{
    uint32_t time  = 0;
    time   = msHcCount*1000;                         // 得到us
    time  += DL_TimerA_getTimerCount(TIMER_2_INST);  // 得到ms

    DL_TimerA_setTimerCount(TIMER_2_INST, 0);   // 清除定时器计数
    delay_ms(1);
    return time ;
}

/******************************************************************
 * 函 数 名 称：Close_Timer
 * 函 数 说 明：关闭定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
******************************************************************/
void Close_Timer(void)
{
    DL_TimerA_stopCounter(TIMER_2_INST);     // 关闭定时器
}

/******************************************************************
 * 函 数 名 称：TIMER_2_INST_IRQHandler
 * 函 数 说 明：定时器中断服务函数
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：1ms进入一次
******************************************************************/
void TIMER_2_INST_IRQHandler(void)
{
    // 获取当前中断向量编号
   if(DL_TimerA_getPendingInterrupt(TIMER_2_INST))
	{
		if(DL_TIMER_IIDX_LOAD) 
		{	
			msHcCount++;
		}
	}
}

/******************************************************************
 * 函 数 名 称：Hcsr04GetLength
 * 函 数 说 明：获取测量距离
 * 函 数 形 参：无
 * 函 数 返 回：测量距离
 * 作       者：LC
 * 备       注：无
******************************************************************/
volatile float t = 0;
float Hcsr04GetLength(void)
{
        /*测5次数据计算一次平均值*/
        volatile float length = 0;
		t = 0;
        volatile float sum = 0;
        volatile unsigned int  i = 0;

		Close_Timer();

//        while(i != 3)  // 减少测量次数，加快频率
//		{
			SR04_TRIG(0);
			delay_1us(10);
			SR04_TRIG(1);
			delay_1us(15);
			SR04_TRIG(0);

			while(SR04_ECHO() == 0);  // 等待回响开始
			Open_Timer();
			i++;
			while(SR04_ECHO() > 0);   // 等待回响结束
			Close_Timer();

			delay_ms(6);  // 缩短等待间隔

			t = (float)Get_TIMER_Count();
			length = t / 58.0f;  // 距离(cm)
			sum += length;
//		}
        length = sum;//五次平均值
        utl_dist = length;
        return length;
}