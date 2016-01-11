/**
 * @file smps_struct.c
 * @brief SMPS struct function
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include "unisp/inc/smps/smps_struct.h"

/*
  +=============================================================================+
  | local definitions
  +=============================================================================+
*/

/*
  +=============================================================================+
  | module variables
  +=============================================================================+
*/

/*
  +=============================================================================+
  | local functions' declarations
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @addtogroup smps_struct
 * @{
 */

/**
 * @brief
 * @details
 **/
void smps_pid_reg_init(volatile struct SMPS_PID_reg* reg){

    reg->current_pid.Ki = SMPS_CURRENT_KI_F32;
    reg->current_pid.Kp = SMPS_CURRENT_KP_F32;
    reg->current_pid.Kd = SMPS_CURRENT_KD_F32;
    reg->voltage_pid.Ki = SMPS_VOLTAGE_KI_F32;
    reg->voltage_pid.Kp = SMPS_VOLTAGE_KP_F32;
    reg->voltage_pid.Kd = SMPS_VOLTAGE_KD_F32;
    reg->run = 0;
    reg->current_ref_f32 = 0.0;
    reg->current_error_f32 = 0.0;
    reg->current_pid_out_f32 = 0.0;
    reg->voltage_ref_f32 = 0.0;
    reg->voltage_error_f32 = 0.0;
    reg->voltage_pid_out_f32 = 0.0;
    reg->new_duty_f32 = 0.0;

    arm_pid_init_f32( &(reg->voltage_pid), 1);
    arm_pid_init_f32( &(reg->current_pid), 1);
}

/**
 * @brief
 * @details
 **/
void smps_struct_init(volatile struct SMPS_status* stat,
                      volatile struct SMPS_settings* set,
                      volatile struct SMPS_ADC_val* adc){

    stat->smps_enable = 0;
    stat->smps_run = 0;
    stat->overvoltage = 0;
    stat->overcurrent = 0;
    stat->burst = 0;
    stat->smps_fault = 0;
    stat->smps_fault_id = SMPS_FAULT_ID_NO_FAULT;
    set->out_voltage_f32 = 0.0;
    set->out_current_f32 = 0.0;
    set->max_prim_current_f32 = 0.0;
    set->mode = SMPS_MODE_CONST_VOLTAGE;
    set->fan_duty_f32 = 0.0;
    set->soft_start = SMPS_SOFTSTART_DISABLE;
    adc->prim_current_adc = &SMPS_ADC_PRIM_CURRENT;
    adc->out_voltage_adc = &SMPS_ADC_OUT_VOLTAGE;
    adc->uc_temp_adc = &SMPS_ADC_UC_TEMP;
    adc->aux_temp_adc = &SMPS_ADC_AUX_TEMP;
    adc->out_voltage_f32 = 0.0;
    adc->prim_current_f32 = 0.0;
    adc->uc_temp_f32 = 0.0;
    adc->aux_temp_f32 = 0.0;
    adc->out_voltage_avg_f32 = 0.0;
    adc->out_voltage_sum = 0;
    adc->out_voltage_cntr = 0;
}

/**
 * @} end of smps_struct group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
