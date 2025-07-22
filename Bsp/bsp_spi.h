#ifndef _BSP_SPI_H__
#define _BSP_SPI_H__

#include "board.h"

//CS引脚的输出控制 
//x=0时输出低电平
//x=1时输出高电平
#define SPI_CS(x)  ( (x) ? DL_GPIO_setPins(CS_PORT,CS_PIN_PIN) : DL_GPIO_clearPins(CS_PORT,CS_PIN_PIN) )
uint8_t spi_read_write_byte(uint8_t dat);
#endif
