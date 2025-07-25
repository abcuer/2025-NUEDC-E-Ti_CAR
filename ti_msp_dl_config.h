/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM */
#define PWM_INST                                                           TIMG6
#define PWM_INST_IRQHandler                                     TIMG6_IRQHandler
#define PWM_INST_INT_IRQN                                       (TIMG6_INT_IRQn)
#define PWM_INST_CLK_FREQ                                                2500000
/* GPIO defines for channel 0 */
#define GPIO_PWM_C0_PORT                                                   GPIOB
#define GPIO_PWM_C0_PIN                                            DL_GPIO_PIN_2
#define GPIO_PWM_C0_IOMUX                                        (IOMUX_PINCM15)
#define GPIO_PWM_C0_IOMUX_FUNC                       IOMUX_PINCM15_PF_TIMG6_CCP0
#define GPIO_PWM_C0_IDX                                      DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_C1_PORT                                                   GPIOB
#define GPIO_PWM_C1_PIN                                            DL_GPIO_PIN_3
#define GPIO_PWM_C1_IOMUX                                        (IOMUX_PINCM16)
#define GPIO_PWM_C1_IOMUX_FUNC                       IOMUX_PINCM16_PF_TIMG6_CCP1
#define GPIO_PWM_C1_IDX                                      DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (999U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG0)
#define TIMER_1_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                           (499U)
/* Defines for TIMER_2 */
#define TIMER_2_INST                                                     (TIMA1)
#define TIMER_2_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_2_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_2_INST_LOAD_VALUE                                          (1999U)
/* Defines for TIMER_3 */
#define TIMER_3_INST                                                     (TIMG7)
#define TIMER_3_INST_IRQHandler                                 TIMG7_IRQHandler
#define TIMER_3_INST_INT_IRQN                                   (TIMG7_INT_IRQn)
#define TIMER_3_INST_LOAD_VALUE                                          (7999U)



/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_FREQUENCY                                            4000000
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOA
#define GPIO_UART_2_TX_PORT                                                GPIOA
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_22
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_21
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM47)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM46)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM47_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM46_PF_UART2_TX
#define UART_2_BAUD_RATE                                                (115200)
#define UART_2_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_2_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_1
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_0
#define GPIO_UART_0_IOMUX_RX                                      (IOMUX_PINCM2)
#define GPIO_UART_0_IOMUX_TX                                      (IOMUX_PINCM1)
#define GPIO_UART_0_IOMUX_RX_FUNC                       IOMUX_PINCM2_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                       IOMUX_PINCM1_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)




/* Defines for SPI */
#define SPI_INST                                                           SPI0
#define SPI_INST_IRQHandler                                     SPI0_IRQHandler
#define SPI_INST_INT_IRQN                                         SPI0_INT_IRQn
#define GPIO_SPI_PICO_PORT                                                GPIOB
#define GPIO_SPI_PICO_PIN                                        DL_GPIO_PIN_17
#define GPIO_SPI_IOMUX_PICO                                     (IOMUX_PINCM43)
#define GPIO_SPI_IOMUX_PICO_FUNC                     IOMUX_PINCM43_PF_SPI0_PICO
#define GPIO_SPI_POCI_PORT                                                GPIOA
#define GPIO_SPI_POCI_PIN                                        DL_GPIO_PIN_10
#define GPIO_SPI_IOMUX_POCI                                     (IOMUX_PINCM21)
#define GPIO_SPI_IOMUX_POCI_FUNC                     IOMUX_PINCM21_PF_SPI0_POCI
/* GPIO configuration for SPI */
#define GPIO_SPI_SCLK_PORT                                                GPIOA
#define GPIO_SPI_SCLK_PIN                                        DL_GPIO_PIN_11
#define GPIO_SPI_IOMUX_SCLK                                     (IOMUX_PINCM22)
#define GPIO_SPI_IOMUX_SCLK_FUNC                     IOMUX_PINCM22_PF_SPI0_SCLK
#define GPIO_SPI_CS0_PORT                                                 GPIOB
#define GPIO_SPI_CS0_PIN                                         DL_GPIO_PIN_25
#define GPIO_SPI_IOMUX_CS0                                      (IOMUX_PINCM56)
#define GPIO_SPI_IOMUX_CS0_FUNC                       IOMUX_PINCM56_PF_SPI0_CS0



/* Port definition for Pin Group BUZZER */
#define BUZZER_PORT                                                      (GPIOA)

/* Defines for Buzzer: GPIOA.23 with pinCMx 53 on package pin 24 */
#define BUZZER_Buzzer_PIN                                       (DL_GPIO_PIN_23)
#define BUZZER_Buzzer_IOMUX                                      (IOMUX_PINCM53)
/* Port definition for Pin Group Gray_IOB */
#define Gray_IOB_PORT                                                    (GPIOB)

/* Defines for R3: GPIOB.8 with pinCMx 25 on package pin 60 */
#define Gray_IOB_R3_PIN                                          (DL_GPIO_PIN_8)
#define Gray_IOB_R3_IOMUX                                        (IOMUX_PINCM25)
/* Port definition for Pin Group KEY3 */
#define KEY3_PORT                                                        (GPIOB)

/* Defines for KEY_3: GPIOB.9 with pinCMx 26 on package pin 61 */
#define KEY3_KEY_3_PIN                                           (DL_GPIO_PIN_9)
#define KEY3_KEY_3_IOMUX                                         (IOMUX_PINCM26)
/* Port definition for Pin Group CS */
#define CS_PORT                                                          (GPIOA)

/* Defines for PIN: GPIOA.29 with pinCMx 4 on package pin 36 */
#define CS_PIN_PIN                                              (DL_GPIO_PIN_29)
#define CS_PIN_IOMUX                                              (IOMUX_PINCM4)
/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for Blue: GPIOA.26 with pinCMx 59 on package pin 30 */
#define LED_Blue_PIN                                            (DL_GPIO_PIN_26)
#define LED_Blue_IOMUX                                           (IOMUX_PINCM59)
/* Defines for Green: GPIOA.27 with pinCMx 60 on package pin 31 */
#define LED_Green_PIN                                           (DL_GPIO_PIN_27)
#define LED_Green_IOMUX                                          (IOMUX_PINCM60)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for task: GPIOA.2 with pinCMx 7 on package pin 42 */
#define KEY_task_PIN                                             (DL_GPIO_PIN_2)
#define KEY_task_IOMUX                                            (IOMUX_PINCM7)
/* Defines for start: GPIOA.31 with pinCMx 6 on package pin 39 */
#define KEY_start_PIN                                           (DL_GPIO_PIN_31)
#define KEY_start_IOMUX                                           (IOMUX_PINCM6)
/* Port definition for Pin Group Motor_left */
#define Motor_left_PORT                                                  (GPIOB)

/* Defines for AIN1: GPIOB.18 with pinCMx 44 on package pin 15 */
#define Motor_left_AIN1_PIN                                     (DL_GPIO_PIN_18)
#define Motor_left_AIN1_IOMUX                                    (IOMUX_PINCM44)
/* Defines for AIN2: GPIOB.19 with pinCMx 45 on package pin 16 */
#define Motor_left_AIN2_PIN                                     (DL_GPIO_PIN_19)
#define Motor_left_AIN2_IOMUX                                    (IOMUX_PINCM45)
/* Port definition for Pin Group Motor_right */
#define Motor_right_PORT                                                 (GPIOB)

/* Defines for BIN1: GPIOB.20 with pinCMx 48 on package pin 19 */
#define Motor_right_BIN1_PIN                                    (DL_GPIO_PIN_20)
#define Motor_right_BIN1_IOMUX                                   (IOMUX_PINCM48)
/* Defines for BIN2: GPIOB.24 with pinCMx 52 on package pin 23 */
#define Motor_right_BIN2_PIN                                    (DL_GPIO_PIN_24)
#define Motor_right_BIN2_IOMUX                                   (IOMUX_PINCM52)
/* Port definition for Pin Group Encoder_left */
#define Encoder_left_PORT                                                (GPIOA)

/* Defines for E1A: GPIOA.9 with pinCMx 20 on package pin 55 */
// pins affected by this interrupt request:["E1A","E1B"]
#define Encoder_left_INT_IRQN                                   (GPIOA_INT_IRQn)
#define Encoder_left_INT_IIDX                   (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define Encoder_left_E1A_IIDX                                (DL_GPIO_IIDX_DIO9)
#define Encoder_left_E1A_PIN                                     (DL_GPIO_PIN_9)
#define Encoder_left_E1A_IOMUX                                   (IOMUX_PINCM20)
/* Defines for E1B: GPIOA.8 with pinCMx 19 on package pin 54 */
#define Encoder_left_E1B_IIDX                                (DL_GPIO_IIDX_DIO8)
#define Encoder_left_E1B_PIN                                     (DL_GPIO_PIN_8)
#define Encoder_left_E1B_IOMUX                                   (IOMUX_PINCM19)
/* Port definition for Pin Group Encoder_right */
#define Encoder_right_PORT                                               (GPIOB)

/* Defines for E2A: GPIOB.7 with pinCMx 24 on package pin 59 */
// pins affected by this interrupt request:["E2A","E2B"]
#define Encoder_right_INT_IRQN                                  (GPIOB_INT_IRQn)
#define Encoder_right_INT_IIDX                  (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder_right_E2A_IIDX                               (DL_GPIO_IIDX_DIO7)
#define Encoder_right_E2A_PIN                                    (DL_GPIO_PIN_7)
#define Encoder_right_E2A_IOMUX                                  (IOMUX_PINCM24)
/* Defines for E2B: GPIOB.6 with pinCMx 23 on package pin 58 */
#define Encoder_right_E2B_IIDX                               (DL_GPIO_IIDX_DIO6)
#define Encoder_right_E2B_PIN                                    (DL_GPIO_PIN_6)
#define Encoder_right_E2B_IOMUX                                  (IOMUX_PINCM23)
/* Port definition for Pin Group Gray_IOA */
#define Gray_IOA_PORT                                                    (GPIOA)

/* Defines for L4: GPIOA.16 with pinCMx 38 on package pin 9 */
#define Gray_IOA_L4_PIN                                         (DL_GPIO_PIN_16)
#define Gray_IOA_L4_IOMUX                                        (IOMUX_PINCM38)
/* Defines for L3: GPIOA.12 with pinCMx 34 on package pin 5 */
#define Gray_IOA_L3_PIN                                         (DL_GPIO_PIN_12)
#define Gray_IOA_L3_IOMUX                                        (IOMUX_PINCM34)
/* Defines for L2: GPIOA.13 with pinCMx 35 on package pin 6 */
#define Gray_IOA_L2_PIN                                         (DL_GPIO_PIN_13)
#define Gray_IOA_L2_IOMUX                                        (IOMUX_PINCM35)
/* Defines for L1: GPIOA.15 with pinCMx 37 on package pin 8 */
#define Gray_IOA_L1_PIN                                         (DL_GPIO_PIN_15)
#define Gray_IOA_L1_IOMUX                                        (IOMUX_PINCM37)
/* Defines for R1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define Gray_IOA_R1_PIN                                         (DL_GPIO_PIN_17)
#define Gray_IOA_R1_IOMUX                                        (IOMUX_PINCM39)
/* Defines for R2: GPIOA.18 with pinCMx 40 on package pin 11 */
#define Gray_IOA_R2_PIN                                         (DL_GPIO_PIN_18)
#define Gray_IOA_R2_IOMUX                                        (IOMUX_PINCM40)
/* Defines for R4: GPIOA.14 with pinCMx 36 on package pin 7 */
#define Gray_IOA_R4_PIN                                         (DL_GPIO_PIN_14)
#define Gray_IOA_R4_IOMUX                                        (IOMUX_PINCM36)
/* Port definition for Pin Group SR04 */
#define SR04_PORT                                                        (GPIOA)

/* Defines for Trig: GPIOA.7 with pinCMx 14 on package pin 49 */
#define SR04_Trig_PIN                                            (DL_GPIO_PIN_7)
#define SR04_Trig_IOMUX                                          (IOMUX_PINCM14)
/* Defines for Echo: GPIOA.28 with pinCMx 3 on package pin 35 */
#define SR04_Echo_PIN                                           (DL_GPIO_PIN_28)
#define SR04_Echo_IOMUX                                           (IOMUX_PINCM3)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.24 with pinCMx 54 on package pin 25 */
#define OLED_SCL_PIN                                            (DL_GPIO_PIN_24)
#define OLED_SCL_IOMUX                                           (IOMUX_PINCM54)
/* Defines for SDA: GPIOA.25 with pinCMx 55 on package pin 26 */
#define OLED_SDA_PIN                                            (DL_GPIO_PIN_25)
#define OLED_SDA_IOMUX                                           (IOMUX_PINCM55)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_TIMER_2_init(void);
void SYSCFG_DL_TIMER_3_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
