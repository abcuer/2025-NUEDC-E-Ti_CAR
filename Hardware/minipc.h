#ifndef __MINIPC_H
#define __MINIPC_H

#include "stdint.h"
#include "ti_msp_dl_config.h"

#define FRAME_HEADER1  0xAA
#define FRAME_HEADER2  0x55
#define FRAME_TAIL1    0x0D
#define FRAME_TAIL2    0x0A
#define MAX_FRAME_LEN  256

#define CMD_START_TASK   0x01
#define CMD_STOP_TASK    0x02
#define CMD_SET_SPEED    0x03
#define CMD_HEARTBEAT    0x04

void Minipc_Send_Cmd(uint8_t cmd, uint8_t *data, uint8_t len);
void Minipc_Parse_Cmd(uint8_t cmd, uint8_t *data, uint8_t len);

#endif