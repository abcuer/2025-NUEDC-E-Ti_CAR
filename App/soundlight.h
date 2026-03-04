#ifndef __SOUNDLIGHT_H
#define __SOUNDLIGHT_H

#include "stdint.h"
typedef struct
{
	uint8_t flag;
	uint8_t time;
}SoundLight_Struct;

void SoundLightRun(void);
void SoundLightUpdate(void);


#endif
