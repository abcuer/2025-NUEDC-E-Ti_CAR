#include "delay.h"
#include "ti_msp_dl_config.h"

void delay_us(uint32_t nus) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD; 

    ticks = nus * MCU_FREQ_MHZ; 

    told = SysTick->VAL; 

    while (1) {
        tnow = SysTick->VAL;
        if (tnow != told) {
            if (tnow < told) {
                tcnt += told - tnow;
            } else {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks) break; 
        }
    }
}

void delay_ms(uint32_t ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}
