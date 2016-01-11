/**
 * @file reg_config.h
 * @brief SMPS regulator configuration. At this time only simple PI voltage regulator is implemented.
 * @todo: average current control
 * @author raiden00
 * @date 2015-09-28
 */

/******************************************************************************
 * project: edm_gen
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef SMPS_REG_CONFIG_H_
#define SMPS_REG_CONFIG_H_

#include "unisp/conf/mcu_config.h"
#include "unisp/conf/smps_config.h"

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

/*
  @TODO: all
  Digital Current Mode Controll. Describe later .....

  Charackteristic equation : (s^2)*L*C + s*C*RA + KP*RA + (KI/s)*RA
  RA - current compensator proportional gain
  KP - voltage compensator proportional gain
  KI - voltage compensator inte... gain

*/


/*
  +====================================+
  | CORRECTION CONSTANTs
  +====================================+
*/
//#define SMPS_PID_VOLTAGE_CORRECTION_SLOPE ((float)2-0.96)
//#define SMPS_PID_VOLTAGE_CORRECTION_INTERCEPT ((float)-4.3)
#define SMPS_PID_VOLTAGE_CORRECTION_SLOPE ((float)1)
#define SMPS_PID_VOLTAGE_CORRECTION_INTERCEPT ((float)0)

/*
  +====================================+
  | PID CONSTANTs
  +====================================+
*/

#define SMPS_PID_VOLTAGE_SCALING_F32 ((float) SMPS_OUT_VOLTAGE_TO_DUTY_RATIO_F32) //!<
//#define SMPS_VOLTAGE_KP_F32 ((float) 8) //!<voltage compensator proportional gain
//#define SMPS_VOLTAGE_KP_F32 ((float) 1.1) //!<voltage compensator proportional gain
#define SMPS_VOLTAGE_KP_F32 ((float) 1.00) //!<voltage compensator proportional gain
#define SMPS_VOLTAGE_KI_F32 ((float) 0.03) //!<voltage compensator integral gain
#define SMPS_VOLTAGE_KD_F32 ((float) 0.0) //!<voltage compensator differential gain (=0)
#define SMPS_CURRENT_KP_F32 ((float) 0.0) //!< current compensator proportional gain
#define SMPS_CURRENT_KI_F32 ((float) 0.0) //!< current compensator integral gain (=0)
#define SMPS_CURRENT_KD_F32 ((float) 0.0) //!< current compensator differential gain (=0)
/* #define SMPS_VOLT_REG_KP_SCALING_F32 ((float) 1.0) //!< voltage compensator proportional gain scaling. From voltage to current output */
/* #define SMPS_VOLT_REG_KD_SCALING_F32 ((float) 1.0) //!< voltage compensator integral gain scaling. From voltage to current output */
/* #define SMPS_VOLT_REG_KI_SCALING_F32 ((float) 1.0)//!< voltage compensator differential gain scaling. From voltage to current output */
/* #define SMPS_CURR_REG_KP_SCALING_F32 ((float) 1.0)//!< current compensator proportional gain scaling. From current to voltage output. */
/* #define SMPS_CURR_REG_KD_SCALING_F32 ((float) 1.0)//!< current compensator integral gain scaling. From current to voltage output. */
/* #define SMPS_CURR_REG_KI_SCALING_F32 ((float) 1.0)//!< current compensator differential gain scaling. From current to voltage output. */
/* #define SMPS_VOLT_REG_SAMPLE_TIME_F32 ((float) 1.0) //!< voltage compensator sampling time. In sec. @TODO todo */
/* #define SMPS_CURR_REG_SAMPLE_TIME_F32 ((float) 1.0) //!< current compensator sampling time. In sec. @TODO todo */
#define SMPS_PID_VOLTAGE_OUT_SATURATION_MAX_F32 ((float) SMPS_OUT_VOLTAGE_MAX_F32)
#define SMPS_PID_CURRENT_OUT_SATURATION_MAX_F32 ((float) SMPS_PRIM_CURRENT_MAX_F32)
#define SMPS_PID_REG_DEADBAND_F32 ((float) 0.5)

/* #define CONTROL_LOOP_FREQUENCY //!< */
/* #define INTEGRAL_VOLTAGE_BW //!< */
/* #define PROPORTIONAL_VOLTAGE_BW //!< */
/* #define PROPORTIONAL_CURRENT_BW //!< */
/* #define SMPS_PRIM_CURRENT_ERROR_TO_DUTY_SCALE_F32 ((float)(0.0)) */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* SMPS_REG_CONFIG_H_ */
