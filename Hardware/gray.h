#ifndef _gray_h
#define _gray_h
#include "headfile.h"

typedef struct{
	uint8_t left[3];
	uint8_t M;
	uint8_t right[3];
} GRAY_Struct;

void Gray_Update(void);

extern GRAY_Struct gray;


#endif