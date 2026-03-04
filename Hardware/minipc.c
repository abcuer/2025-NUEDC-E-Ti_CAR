#include "minipc.h"
#include "led.h"
#include "task.h"

typedef enum {
    STATE_WAIT_H1,
    STATE_WAIT_H2,
    STATE_WAIT_CMD,
    STATE_WAIT_LEN,
    STATE_WAIT_DATA,
    STATE_WAIT_CHECK,
    STATE_WAIT_T1,
    STATE_WAIT_T2
} RxState_t;

static volatile RxState_t rx_state = STATE_WAIT_H1;
static uint8_t rx_buf[MAX_FRAME_LEN];
static uint8_t rx_index = 0;
static uint8_t data_len = 0;

/**
 * @brief ????????
 */
void uart_send_bytes(uint8_t *buf, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        while (DL_UART_isBusy(UART_0_INST)); // ??????
        DL_UART_Main_transmitData(UART_0_INST, buf[i]);
    }
}

/**
 * @brief ?????????
 */
void Minipc_Send_Cmd(uint8_t cmd, uint8_t *data, uint8_t len) 
{
    if (len > (MAX_FRAME_LEN - 7)) return;

    uint8_t tx_buf[MAX_FRAME_LEN];
    tx_buf[0] = FRAME_HEADER1;
    tx_buf[1] = FRAME_HEADER2;
    tx_buf[2] = cmd;
    tx_buf[3] = len;

    uint8_t checksum = cmd ^ len;
    for (uint8_t i = 0; i < len; i++) {
        tx_buf[4 + i] = data[i];
        checksum ^= data[i];
    }

    tx_buf[4 + len] = checksum;
    tx_buf[5 + len] = FRAME_TAIL1;
    tx_buf[6 + len] = FRAME_TAIL2;

    uart_send_bytes(tx_buf, 7 + len);
}

/**
 * @brief ??????(??????? Task ????)
 */
void Minipc_Parse_Cmd(uint8_t cmd, uint8_t *data, uint8_t len) 
{
    switch (cmd) {
        case CMD_START_TASK:
            SetLedMode(LED_BLUE, LED_ON);
            break;

        case CMD_STOP_TASK:
            SetLedMode(LED_BLUE, LED_OFF);
            break;

        case CMD_SET_SPEED:
            if (len >= 4) { 
                basespeed = *(float*)data;
            }
            break;

        default:
            break;
    }
}

void UART_0_INST_IRQHandler(void) {
    if (DL_UART_getPendingInterrupt(UART_0_INST) == DL_UART_IIDX_RX) {
        uint8_t byte = DL_UART_Main_receiveData(UART_0_INST);

        switch (rx_state) {
            case STATE_WAIT_H1:
                if (byte == FRAME_HEADER1) rx_state = STATE_WAIT_H2;
                break;

            case STATE_WAIT_H2:
                rx_state = (byte == FRAME_HEADER2) ? STATE_WAIT_CMD : STATE_WAIT_H1;
                break;

            case STATE_WAIT_CMD:
                rx_buf[0] = byte; // ?? CMD
                rx_state = STATE_WAIT_LEN;
                break;

            case STATE_WAIT_LEN:
                data_len = byte;
                if (data_len > (MAX_FRAME_LEN - 7)) {
                    rx_state = STATE_WAIT_H1; // ??????
                } else {
                    rx_index = 0;
                    rx_state = (data_len > 0) ? STATE_WAIT_DATA : STATE_WAIT_CHECK;
                }
                break;

            case STATE_WAIT_DATA:
                rx_buf[1 + rx_index++] = byte;
                if (rx_index >= data_len) rx_state = STATE_WAIT_CHECK;
                break;

            case STATE_WAIT_CHECK: {
                uint8_t checksum = rx_buf[0] ^ data_len;
                for (uint8_t i = 0; i < data_len; i++) checksum ^= rx_buf[1 + i];
                
                rx_state = (checksum == byte) ? STATE_WAIT_T1 : STATE_WAIT_H1;
                break;
            }

            case STATE_WAIT_T1:
                rx_state = (byte == FRAME_TAIL1) ? STATE_WAIT_T2 : STATE_WAIT_H1;
                break;

            case STATE_WAIT_T2:
                if (byte == FRAME_TAIL2)
				{
					// 启动解析任务
                    Minipc_Parse_Cmd(rx_buf[0], &rx_buf[1], data_len);
                }
                rx_state = STATE_WAIT_H1;
                break;

            default:
                rx_state = STATE_WAIT_H1;
                break;
        }
    }
}