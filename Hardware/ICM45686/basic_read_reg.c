#include <stdio.h>
#include "inv_imu_driver.h"

#define ICM_USE_HARD_SPI


#if defined(ICM_USE_HARD_SPI)
#include "bsp_spi.h"
#elif defined(ICM_USE_I2C)
#include "bsp_iic.h"
#define ICM_I2C_ADDR 0x69
#endif

#define UI_I2C  0 /**< identifies I2C interface. */
#define UI_SPI4 1 /**< identifies 4-wire SPI interface. */


#define INV_MSG(level,msg, ...) 	      printf("%d," msg "\r\n", __LINE__, ##__VA_ARGS__)

static inv_imu_device_t  imu_dev; /* Driver structure */

//static uint8_t discard_accel_samples; /* Indicates how many accel samples should be discarded */
//static uint8_t discard_gyro_samples; /* Indicates how many gyro samples should be discarded */



int si_print_error_if_any(int rc);
#define SI_CHECK_RC(rc)                                                                            \
	do {                                                                                           \
		if (si_print_error_if_any(rc)) {                                                           \
			INV_MSG(INV_MSG_LEVEL_ERROR, "At %s (line %d)", __FILE__, __LINE__);                   \
			delay_ms(100);                                                                   \
			return rc;                                                                             \
		}                                                                                          \
	} while (0)

/*
 * Error codes
 */
int si_print_error_if_any(int rc)
{
	if (rc != 0) {
		switch (rc) {
		case INV_IMU_ERROR:
			printf("Unspecified error (%d)", rc);
			break;
		case INV_IMU_ERROR_TRANSPORT:
			printf("Error occurred at transport level (%d)", rc);
			break;
		case INV_IMU_ERROR_TIMEOUT:
			printf("Action did not complete in the expected time window (%d)",rc);
			break;
		case INV_IMU_ERROR_BAD_ARG:
			printf("Invalid argument provided (%d)", rc);
			break;
		case INV_IMU_ERROR_EDMP_BUF_EMPTY:
			printf("EDMP buffer is empty (%d)", rc);
			break;
		default:
			printf("Unknown error (%d)", rc);
			break;
		}
	}

	return rc;
}
/*******************************************************************************
* 名    称： icm42688_read_regs
* 功    能： 连续读取多个寄存器的值
* 入口参数： reg: 起始寄存器地址 *buf数据指针,uint16_t len长度
* 出口参数： 无
* 作　　者： Baxiange
* 创建日期： 2024-07-25
* 修    改：
* 修改日期：
* 备    注： 使用SPI读取寄存器时要注意:最高位为读写位，详见datasheet page50.
*******************************************************************************/
static int icm45686_read_regs(uint8_t reg, uint8_t* buf, uint32_t len)
{
#if defined(ICM_USE_HARD_SPI)
    reg |= 0x80;
    SPI_CS(0);
    /* 写入要读的寄存器地址 */
    spi_read_write_byte(reg);
    /* 读取寄存器数据 */
    while(len)
	{
		*buf = spi_read_write_byte(0x00);
		len--;
		buf++;
	}
    SPI_CS(1);
#elif defined(ICM_USE_I2C)
	IICreadBytes(ICM_I2C_ADDR, reg, len, buf);
#endif
	return 0;
}

static uint8_t io_write_reg(uint8_t reg, uint8_t value)
{
#if defined(ICM_USE_HARD_SPI)
    SPI_CS(0);
    /* 写入要读的寄存器地址 */
    /* 写入要读的寄存器地址 */
    spi_read_write_byte(reg);
    /* 读取寄存器数据 */
    spi_read_write_byte(value);
    SPI_CS(1);
#elif defined(ICM_USE_I2C)
	IICwriteBytes(ICM_I2C_ADDR, reg, 1, &value);
#endif
    return 0;
}

static int icm45686_write_regs(uint8_t reg, const uint8_t* buf, uint32_t len)
{
	int rc;

	for (uint32_t i = 0; i < len; i++) 
	{
		rc = io_write_reg(reg + i, buf[i]);
		if (rc)
			return rc;
	}
	return 0;
}

/* Initializes IMU device and apply configuration. */
int setup_imu(int use_ln, int accel_en, int gyro_en)
{
	int                      rc     = 0;
	uint8_t                  whoami = 0;
	inv_imu_int_pin_config_t int_pin_config;
	inv_imu_int_state_t      int_config;

	/* Init transport layer */
	imu_dev.transport.read_reg   = icm45686_read_regs;
	imu_dev.transport.write_reg  = icm45686_write_regs;
#if defined(ICM_USE_HARD_SPI)
	imu_dev.transport.serif_type = UI_SPI4;
#elif defined(ICM_USE_I2C)
	imu_dev.transport.serif_type = UI_I2C;
#endif
	imu_dev.transport.sleep_us   = delay_us;

	/* Wait 3 ms to ensure device is properly supplied  */
	delay_us(3000);

	/* In SPI, configure slew-rate to prevent bus corruption on DK-SMARTMOTION-REVG */
	if (imu_dev.transport.serif_type == UI_SPI3 || imu_dev.transport.serif_type == UI_SPI4) {
		drive_config0_t drive_config0;
		drive_config0.pads_spi_slew = DRIVE_CONFIG0_PADS_SPI_SLEW_TYP_10NS;
		rc |= inv_imu_write_reg(&imu_dev, DRIVE_CONFIG0, 1, (uint8_t *)&drive_config0);
		SI_CHECK_RC(rc);
		delay_us(2); /* Takes effect 1.5 us after the register is programmed */
	}

	/* Check whoami */
	rc |= inv_imu_get_who_am_i(&imu_dev, &whoami);
	SI_CHECK_RC(rc);
	if (whoami != INV_IMU_WHOAMI) {
		INV_MSG(INV_MSG_LEVEL_ERROR, "Erroneous WHOAMI value.");
		INV_MSG(INV_MSG_LEVEL_ERROR, "  - Read 0x%02x", whoami);
		INV_MSG(INV_MSG_LEVEL_ERROR, "  - Expected 0x%02x", INV_IMU_WHOAMI);
		return -1;
	}

	rc |= inv_imu_soft_reset(&imu_dev);
	SI_CHECK_RC(rc);

	/*
	 * Configure interrupts pins
	 * - Polarity High
	 * - Pulse mode
	 * - Push-Pull drive
	 */
	int_pin_config.int_polarity = INTX_CONFIG2_INTX_POLARITY_HIGH;
	int_pin_config.int_mode     = INTX_CONFIG2_INTX_MODE_PULSE;
	int_pin_config.int_drive    = INTX_CONFIG2_INTX_DRIVE_PP;
	rc |= inv_imu_set_pin_config_int(&imu_dev, INV_IMU_INT1, &int_pin_config);
	SI_CHECK_RC(rc);

	/* Interrupts configuration */
	memset(&int_config, INV_IMU_DISABLE, sizeof(int_config));
	int_config.INV_UI_DRDY = INV_IMU_ENABLE;
	rc |= inv_imu_set_config_int(&imu_dev, INV_IMU_INT1, &int_config);
	SI_CHECK_RC(rc);

	/* Set FSR */
	rc |= inv_imu_set_accel_fsr(&imu_dev, ACCEL_CONFIG0_ACCEL_UI_FS_SEL_4_G);
	rc |= inv_imu_set_gyro_fsr(&imu_dev, GYRO_CONFIG0_GYRO_UI_FS_SEL_1000_DPS);
	SI_CHECK_RC(rc);

	/* Set ODR */
	rc |= inv_imu_set_accel_frequency(&imu_dev, ACCEL_CONFIG0_ACCEL_ODR_200_HZ);
	rc |= inv_imu_set_gyro_frequency(&imu_dev, GYRO_CONFIG0_GYRO_ODR_200_HZ);
	SI_CHECK_RC(rc);

	/* Set BW = ODR/4 */
	rc |= inv_imu_set_accel_ln_bw(&imu_dev, IPREG_SYS2_REG_131_ACCEL_UI_LPFBW_DIV_4);
	rc |= inv_imu_set_gyro_ln_bw(&imu_dev, IPREG_SYS1_REG_172_GYRO_UI_LPFBW_DIV_4);
	SI_CHECK_RC(rc);

	/* Sensor registers are not available in ULP, so select RCOSC clock to use LP mode. */
	rc |= inv_imu_select_accel_lp_clk(&imu_dev, SMC_CONTROL_0_ACCEL_LP_CLK_RCOSC);
	SI_CHECK_RC(rc);

	/* Set power modes */
	if (use_ln) {
		if (accel_en)
			rc |= inv_imu_set_accel_mode(&imu_dev, PWR_MGMT0_ACCEL_MODE_LN);
		if (gyro_en)
			rc |= inv_imu_set_gyro_mode(&imu_dev, PWR_MGMT0_GYRO_MODE_LN);
	} else {
		if (accel_en)
			rc |= inv_imu_set_accel_mode(&imu_dev, PWR_MGMT0_ACCEL_MODE_LP);
		if (gyro_en)
			rc |= inv_imu_set_gyro_mode(&imu_dev, PWR_MGMT0_GYRO_MODE_LP);
	}

	/* Discard N samples at 50Hz to ignore samples at sensor enabling time */
//	if (accel_en)
//		discard_accel_samples = (ACC_STARTUP_TIME_US / 20000) + 1;
//	if (gyro_en)
//		discard_gyro_samples = (GYR_STARTUP_TIME_US / 20000) + 1;

	SI_CHECK_RC(rc);

	return rc;
}
int bsp_IcmGetRawData(float accel_mg[3], float gyro_dps[3], float *temp_degc)
{
	int rc = 0;
	inv_imu_sensor_data_t d;
	
	rc |= inv_imu_get_register_data(&imu_dev, &d);
	SI_CHECK_RC(rc);
	
	accel_mg[0] = (float)(d.accel_data[0] * 4 /* mg */) / 32.768;
	accel_mg[1] = (float)(d.accel_data[1] * 4 /* mg */) / 32.768;
	accel_mg[2] = (float)(d.accel_data[2] * 4 /* mg */) / 32.768;
	gyro_dps[0] = (float)(d.gyro_data[0] * 1000 /* dps */) / 32768.0;
	gyro_dps[1] = (float)(d.gyro_data[1] * 1000 /* dps */) / 32768.0;
	gyro_dps[2] = (float)(d.gyro_data[2] * 1000 /* dps */) / 32768.0;
	*temp_degc  = (float)25 + ((float)d.temp_data / 128);
	return 0;
}
	
	
