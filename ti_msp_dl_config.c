/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gPWMBackup;
DL_TimerA_backupConfig gTIMER_0Backup;
DL_TimerA_backupConfig gTIMER_2Backup;
DL_TimerG_backupConfig gTIMER_3Backup;
DL_SPI_backupConfig gSPIBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_TIMER_1_init();
    SYSCFG_DL_TIMER_2_init();
    SYSCFG_DL_TIMER_3_init();
    SYSCFG_DL_UART_2_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWMBackup.backupRdy 	= false;
	gTIMER_0Backup.backupRdy 	= false;
	gTIMER_2Backup.backupRdy 	= false;
	gTIMER_3Backup.backupRdy 	= false;

	gSPIBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(PWM_INST, &gPWMBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_0_INST, &gTIMER_0Backup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_2_INST, &gTIMER_2Backup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_3_INST, &gTIMER_3Backup);
	retStatus &= DL_SPI_saveConfiguration(SPI_INST, &gSPIBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(PWM_INST, &gPWMBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_0_INST, &gTIMER_0Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_2_INST, &gTIMER_2Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_3_INST, &gTIMER_3Backup, false);
	retStatus &= DL_SPI_restoreConfiguration(SPI_INST, &gSPIBackup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_INST);
    DL_TimerA_reset(TIMER_0_INST);
    DL_TimerG_reset(TIMER_1_INST);
    DL_TimerA_reset(TIMER_2_INST);
    DL_TimerG_reset(TIMER_3_INST);
    DL_UART_Main_reset(UART_2_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_INST);
    DL_TimerA_enablePower(TIMER_0_INST);
    DL_TimerG_enablePower(TIMER_1_INST);
    DL_TimerA_enablePower(TIMER_2_INST);
    DL_TimerG_enablePower(TIMER_3_INST);
    DL_UART_Main_enablePower(UART_2_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_C0_IOMUX,GPIO_PWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_C0_PORT, GPIO_PWM_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_C1_IOMUX,GPIO_PWM_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_C1_PORT, GPIO_PWM_C1_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_2_IOMUX_TX, GPIO_UART_2_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_2_IOMUX_RX, GPIO_UART_2_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_IOMUX_SCLK, GPIO_SPI_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_IOMUX_PICO, GPIO_SPI_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_IOMUX_POCI, GPIO_SPI_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_IOMUX_CS0, GPIO_SPI_IOMUX_CS0_FUNC);

    DL_GPIO_initDigitalOutput(BUZZER_Buzzer_IOMUX);

    DL_GPIO_initDigitalInputFeatures(Gray_IOB_R3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY3_KEY_3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(CS_PIN_IOMUX);

    DL_GPIO_initDigitalOutputFeatures(LED_Blue_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(LED_Green_IOMUX);

    DL_GPIO_initDigitalInputFeatures(KEY_task_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY_start_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(Motor_left_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(Motor_left_AIN2_IOMUX);

    DL_GPIO_initDigitalOutput(Motor_right_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(Motor_right_BIN2_IOMUX);

    DL_GPIO_initDigitalInputFeatures(Encoder_left_E1A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Encoder_left_E1B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Encoder_right_E2A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Encoder_right_E2B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_L4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_L3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_L2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_L1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_R1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_R2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(Gray_IOA_R4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(SR04_Trig_IOMUX);

    DL_GPIO_initDigitalInputFeatures(SR04_Echo_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(OLED_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_SDA_IOMUX);

    DL_GPIO_clearPins(GPIOA, CS_PIN_PIN |
		LED_Blue_PIN |
		LED_Green_PIN);
    DL_GPIO_setPins(GPIOA, BUZZER_Buzzer_PIN |
		SR04_Trig_PIN |
		OLED_SCL_PIN |
		OLED_SDA_PIN);
    DL_GPIO_enableOutput(GPIOA, BUZZER_Buzzer_PIN |
		CS_PIN_PIN |
		LED_Blue_PIN |
		LED_Green_PIN |
		SR04_Trig_PIN |
		OLED_SCL_PIN |
		OLED_SDA_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_9_EDGE_RISE |
		DL_GPIO_PIN_8_EDGE_RISE);
    DL_GPIO_setLowerPinsInputFilter(GPIOA, DL_GPIO_PIN_2_INPUT_FILTER_8_CYCLES);
    DL_GPIO_setUpperPinsInputFilter(GPIOA, DL_GPIO_PIN_31_INPUT_FILTER_8_CYCLES);
    DL_GPIO_clearInterruptStatus(GPIOA, Encoder_left_E1A_PIN |
		Encoder_left_E1B_PIN);
    DL_GPIO_enableInterrupt(GPIOA, Encoder_left_E1A_PIN |
		Encoder_left_E1B_PIN);
    DL_GPIO_setPins(GPIOB, Motor_left_AIN1_PIN |
		Motor_left_AIN2_PIN |
		Motor_right_BIN1_PIN |
		Motor_right_BIN2_PIN);
    DL_GPIO_enableOutput(GPIOB, Motor_left_AIN1_PIN |
		Motor_left_AIN2_PIN |
		Motor_right_BIN1_PIN |
		Motor_right_BIN2_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_7_EDGE_RISE |
		DL_GPIO_PIN_6_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOB, Encoder_right_E2A_PIN |
		Encoder_right_E2B_PIN);
    DL_GPIO_enableInterrupt(GPIOB, Encoder_right_E2A_PIN |
		Encoder_right_E2B_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_enableMFCLK();
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOB_INT_IRQn, 0);

}


/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 4000000 Hz / (8 * (3 + 1))
 */
static const DL_TimerG_ClockConfig gPWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 3U
};

static const DL_TimerG_PWMConfig gPWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_init(void) {

    DL_TimerG_setClockConfig(
        PWM_INST, (DL_TimerG_ClockConfig *) &gPWMClockConfig);

    DL_TimerG_initPWMMode(
        PWM_INST, (DL_TimerG_PWMConfig *) &gPWMConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerG_setCounterControl(PWM_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerG_setCaptureCompareOutCtl(PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_INST);


    
    DL_TimerG_setCCPDirection(PWM_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000 Hz = 4000000 Hz / (8 * (99 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 99U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (10ms * 40000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerA_setClockConfig(TIMER_0_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerA_initTimerMode(TIMER_0_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_0_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_0_INST_INT_IRQN, 0);
    DL_TimerA_enableClock(TIMER_0_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000 Hz = 4000000 Hz / (8 * (99 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_1ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 99U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_1_INST_LOAD_VALUE = (10ms * 40000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_1TimerConfig = {
    .period     = TIMER_1_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_1_init(void) {

    DL_TimerG_setClockConfig(TIMER_1_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_1ClockConfig);

    DL_TimerG_initTimerMode(TIMER_1_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_1TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_1_INST , DL_TIMERG_INTERRUPT_LOAD_EVENT);
	NVIC_SetPriority(TIMER_1_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_1_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (8000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   800000 Hz = 8000000 Hz / (4 * (9 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_2ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_2_INST_LOAD_VALUE = (1ms * 800000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_2TimerConfig = {
    .period     = TIMER_2_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_2_init(void) {

    DL_TimerA_setClockConfig(TIMER_2_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_2ClockConfig);

    DL_TimerA_initTimerMode(TIMER_2_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_2TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_2_INST , DL_TIMERA_INTERRUPT_LOAD_EVENT);
	NVIC_SetPriority(TIMER_2_INST_INT_IRQN, 2);
    DL_TimerA_enableClock(TIMER_2_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_3ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_3_INST_LOAD_VALUE = (100us * 32000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_3TimerConfig = {
    .period     = TIMER_3_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_3_init(void) {

    DL_TimerG_setClockConfig(TIMER_3_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_3ClockConfig);

    DL_TimerG_initTimerMode(TIMER_3_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_3TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_3_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_3_INST_INT_IRQN, 2);
    DL_TimerG_enableClock(TIMER_3_INST);





}



static const DL_UART_Main_ClockConfig gUART_2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_2_init(void)
{
    DL_UART_Main_setClockConfig(UART_2_INST, (DL_UART_Main_ClockConfig *) &gUART_2ClockConfig);

    DL_UART_Main_init(UART_2_INST, (DL_UART_Main_Config *) &gUART_2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_2_INST, UART_2_IBRD_32_MHZ_115200_BAUD, UART_2_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_2_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_2_INST);
}

static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_115200_BAUD, UART_0_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO4_POL1_PHA1,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
    .chipSelectPin = DL_SPI_CHIP_SELECT_0,
};

static const DL_SPI_ClockConfig gSPI_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_init(void) {
    DL_SPI_setClockConfig(SPI_INST, (DL_SPI_ClockConfig *) &gSPI_clockConfig);

    DL_SPI_init(SPI_INST, (DL_SPI_Config *) &gSPI_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     2000000 = (32000000)/((1 + 7) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_INST, 7);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /* Initialize the period to 1.00 μs */
    DL_SYSTICK_init(32);
    /* Enable the SysTick and start counting */
    DL_SYSTICK_enable();
}

