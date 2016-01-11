/**
 * @file smps_struct.h
 * @brief
 * @author raiden00
 * @date
 */

/******************************************************************************
* project: edm_gen
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc
*
******************************************************************************/
#ifndef SMPS_STRUCT_H_
#define SMPS_STRUCT_H_

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include <stdint.h>
#include <arm_math.h>
#include "unisp/conf/smps_reg_config.h"
#include "unisp/conf/smps_config.h"
#include "unisp/inc/hal/adc.h"

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

/**
 * @brief
 *
 **/
typedef enum{

    SMPS_FAULT_ID_NO_FAULT = 0,
    SMPS_FAULT_ID_WRONG_PARAM = 1,

}SMPS_FAULT_ID_t;

typedef enum{

    SMPS_MODE_CONST_VOLTAGE = 0,
    SMPS_MODE_CONST_CURRENT = 1,

}SMPS_MODE_t;

typedef enum{

    SMPS_SOFTSTART_DISABLE = 0,
    SMPS_SOFTSTART_UP = 1,
    SMPS_SOFTSTART_DOWN = 2,

}SMPS_SOFTSTART_t;


/**
 * @brief
 *
 **/
struct SMPS_status{

    uint8_t overcurrent:1;
    uint8_t overvoltage:1;
    uint8_t burst:1;
    uint8_t smps_fault:1;
    uint8_t smps_enable:1;
    uint8_t smps_run:1;
    uint8_t tmp1:1;
    uint8_t tmp2:1;
    SMPS_FAULT_ID_t smps_fault_id:8;
    uint8_t _RES3;
    uint8_t _RES4;

    //!< 32 bits all
};


/**
 * @brief
 *
 **/
struct SMPS_settings{
    float out_voltage_f32;
    float out_current_f32;
    float max_prim_current_f32;
    SMPS_MODE_t mode;
    float fan_duty_f32;
    uint8_t soft_start;
};


/**
 * @brief
 *
 **/
struct SMPS_ADC_val{

    uint16_t* prim_current_adc; //!<ADC value
    uint16_t* out_voltage_adc;
    uint16_t* uc_temp_adc;
    uint16_t* aux_temp_adc;

    float out_voltage_f32;  //!< out_voltage in f32 [V]
    float prim_current_f32; //!< prim_current in f32 [A]
    float uc_temp_f32; //!< uc_temp in f32 [*C]
    float aux_temp_f32; //!< uc_temp in f32 [*C]

    float out_voltage_avg_f32; //!< average out_voltage in f32 [V]
    uint32_t out_voltage_sum; //!< temp value to calc average
    uint16_t out_voltage_cntr;

};


/**
 * @brief
 *
 **/
struct SMPS_PID_reg{

    arm_pid_instance_f32 voltage_pid;
    arm_pid_instance_f32 current_pid;
    uint8_t run;
    float current_ref_f32;
    float current_error_f32;
    float current_pid_out_f32;
    float voltage_ref_f32;
    float voltage_error_f32;
    float voltage_pid_out_f32;
    float new_duty_f32;

};


/**
 * @brief @TODO: pack to 1 struct
 *
 **/
struct SMPS_struct{

    struct SMPS_status stat;
    struct SMPS_settings set;
    struct SMPS_ADC_val adc;
    struct SMPS_PID_reg reg;

};


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

void smps_struct_init(volatile struct SMPS_status* stat, volatile struct SMPS_settings* set, volatile struct SMPS_ADC_val* adc);
void smps_pid_reg_init(volatile struct SMPS_PID_reg* reg);

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* SMPS_STRUCT_H_ */
