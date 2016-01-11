/**
 * @file smps.h
 * @brief smps.c header
 * @author raiden00
 * @date
 */

/******************************************************************************
* project: UniSP
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc
*
******************************************************************************/
#ifndef SMPS_H_
#define SMPS_H_

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
#include "unisp/inc/smps/smps_struct.h"
#include "unisp/inc/smps/smps_hal.h"
#include "unisp/conf/mcu_config.h"
#include "unisp/conf/smps_config.h"

/*
+=============================================================================+
| global variables
+=============================================================================+
*/

extern volatile struct SMPS_status gSmps_stat; //!< smps status structure
extern volatile struct SMPS_settings gSmps_sets; //!< smps settings structure
extern volatile struct SMPS_ADC_val gSmps_adc_val; //!< smps adc value structure
extern volatile struct SMPS_PID_reg gSmps_pid_reg; //!< smps pid regulator structure

/*
+=============================================================================+
| global functions' declarations
+=============================================================================+
*/

void smps_settings_struct_reset(volatile struct SMPS_settings* s, volatile struct SMPS_PID_reg *smps_pid);
void smps_inrush_protection_off(void);
void smps_overload_current_write(volatile struct SMPS_settings* s, float current);
inline void smps_overload_current_set(const struct SMPS_settings s);
void smps_out_voltage_write(volatile struct SMPS_settings* s, const struct SMPS_PID_reg smps_pid, float voltage);

void smps_ACMC_regulator_init(void);

inline void smps_enable(volatile struct SMPS_status* s);
inline void smps_disable(volatile struct SMPS_status* s);
inline uint8_t smps_start(const struct SMPS_settings smps_sets,volatile struct SMPS_status* smps_stat, volatile struct SMPS_PID_reg* pid_reg);
inline void smps_stop(volatile struct SMPS_status* s, volatile struct SMPS_PID_reg* pid_reg);

void smps_init(volatile struct SMPS_settings* smps_sets, volatile struct SMPS_status* smps_stat, volatile struct SMPS_PID_reg* pid_reg);
void smps_init_and_loop(const struct SMPS_settings smps_set, struct SMPS_status* smps_stat, struct SMPS_PID_reg* pid_reg);

inline float smps_uc_temp_get(float sensor_voltage);
inline float smps_aux_temp_get(float sensor_voltage);
inline void smps_fan_duty_write(volatile struct SMPS_settings* smps_sets, float duty);
inline void smps_temp_regulator(const struct SMPS_ADC_val adc);

inline void smps_overload_flt_enable(void);
inline void smps_overload_reset(volatile struct SMPS_status* s);
inline void smps_overload(volatile struct SMPS_status* s, volatile struct SMPS_PID_reg* pid_reg);
inline void smps_burst_enable(volatile struct SMPS_status* s);
inline void smps_burst_disable(volatile struct SMPS_status* s);
inline void smps_burst_decrease(volatile struct SMPS_status* s);
inline void smps_burst_increase(volatile struct SMPS_status* s);

inline float smps_pid_voltage_f32(arm_pid_instance_f32 * S, float32_t in);
inline float smps_pid_current_f32(arm_pid_instance_f32 * S, float32_t in);

void smps_pid_reg_start(volatile struct SMPS_PID_reg* pid_reg);
void smps_pid_reg_stop(volatile struct SMPS_PID_reg* pid_reg);

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* SMPS_FUNC_H_ */
