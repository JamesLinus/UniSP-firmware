/** \file smps_hal.h
 * \brief smps_hal.c header
 * \author raiden00
 * \date
 */

/******************************************************************************
* project: edm_gen
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc
*
******************************************************************************/
#ifndef SMPS_HAL_H_
#define SMPS_HAL_H_

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include <stdint.h>
#include <arm_math.h>
#include <stm32f334x8.h>
#include "unisp/inc/hal/hrtim.h"
#include "unisp/inc/hal/timer.h"
#include "unisp/inc/hal/dac.h"
#include "unisp/inc/hal/adc.h"
#include "unisp/inc/smps/smps_struct.h"
#include "unisp/conf/mcu_config.h"
#include "unisp/conf/smps_config.h"


/*
+=============================================================================+
| local definitions
+=============================================================================+
*/

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

#define SMPS_PWM_OUT_ENABLE HRTIM1_TIMER_A_O12EN

/*
+=============================================================================+
| module variables

+=============================================================================+
*/

/*
+=============================================================================+
| global variables
+=============================================================================+
*/


/*
+=============================================================================+
| global functions' declarations
+=============================================================================+
*/

inline void smps_bridge_pwm_enable(void);
inline void smps_bridge_pwm_disable(void);
inline void smps_bridge_pwm_frequency_set(uint32_t frequency);
inline void smps_bridge_pwm_duty_set(float duty);
inline float smps_bridge_pwm_duty_get(void);
inline void smps_bridge_pwm_out_voltage_set(float voltage);
inline void smps_bridge_max_current_set(float current);
inline float smps_bridge_pwm_out_voltage_get(void);
inline float smps_bridge_max_current_get(void);
inline void smps_fault_enable(void);
inline void smps_adc_reg_inj_start(void);
inline void smps_adc_reg_inj_stop(void);
void smps_control_loop_freq_set(uint32_t frequency);
inline void smps_control_loop_stop(void);
inline void smps_control_loop_start(void);
inline void smps_burst_mode_stop(void);
inline void smps_burst_mode_start(void);
inline void smps_burst_mode_update(float duty);
inline float smps_burst_mode_duty_get(void);

inline void smps_delay_ms(uint32_t delay_ms);
inline void smps_fan_duty_set(float duty);

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* SMPS_HAL_H_ */
