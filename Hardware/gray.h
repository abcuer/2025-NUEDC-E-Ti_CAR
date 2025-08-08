#ifndef _gray_h
#define _gray_h
#include "headfile.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h" 

void Gray_Read(void);
void Sensor_Calibration(No_MCU_Sensor *sensor);
void Get_Light_TTL(void);

extern int8_t L4;
extern int8_t L3;
extern int8_t L2;
extern int8_t L1;
extern int8_t R1;
extern int8_t R2;
extern int8_t R3;
extern int8_t R4;

#endif