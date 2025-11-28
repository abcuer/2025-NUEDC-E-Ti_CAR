#ifndef _MINPC_H
#define _MINPC_H


void minpc_init(void);
void uart_send_bytes(uint8_t *buf, uint16_t len);
void send_cmd(uint8_t cmd, uint8_t *data, uint8_t len);
void process_cmd(uint8_t task, uint8_t *data, uint8_t len);


#endif