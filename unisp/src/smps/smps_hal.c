/**
 * @file smps.c
 * @brief SMPS functions
 * @author raiden00
 * @date 2015-09-28
 */

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

#include "unisp/inc/smps/smps_hal.h"

/*
  +=============================================================================+
  | local functions' declarations
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global variables
  +=============================================================================+
*/

/*
  +=============================================================================+
  | local functions
  +=============================================================================+
*/

/**
 * @addtogroup smps_function
 * @{
 */

/**
 * @brief
 * @details SMPS bridge frequency can be change only witch smps_bridge_pwm_init() function.
 **/
inline void smps_bridge_pwm_frequency_set(uint32_t frequency){

    uint16_t period = HRTIM_TIMER_A_FREQUENCY/frequency;
    period /= 2;

    hrtim_TIMER_A_per_update(period);
}

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @brief
 * @details
 **/
inline void smps_bridge_pwm_enable(void){

    hrtim_TIMER_A_out_enable();
}

/**
 * @brief
 * @details
 **/
inline void smps_bridge_pwm_disable(void){

    hrtim_TIMER_A_out_disable();
}

/**
 * @brief
 * @details Include transistors delay (SMPS_BRIDGE_DUTY_CYCLE_CORRECTION)
 *
 **/
inline void smps_bridge_pwm_duty_set(float duty){

    if(duty > SMPS_BRIDGE_DUTY_CYCLE_MAX_F32) duty = SMPS_BRIDGE_DUTY_CYCLE_MAX_F32; // saturation
    else if(duty < SMPS_BRIDGE_DUTY_CYCLE_MIN_F32) duty = SMPS_BRIDGE_DUTY_CYCLE_MIN_F32;
    duty -= SMPS_BRIDGE_DUTY_CYCLE_CORRECTION_F32;

    uint16_t period = HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].PERxR;
    uint16_t compare1 = (uint16_t) (period * (1.0 - duty));

    hrtim_TIMER_A_cmp1_update(compare1);
}

/**
 * @brief
 * @details
 **/
inline float smps_bridge_pwm_duty_get(void){

    uint16_t period = HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].PERxR;
    uint16_t compare1 = HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].CMP1xR;
    float duty = 1.0 - ((float)compare1 / (float)period);

    return duty;
}

/**
 * @brief
 * @details Simple, just for debug purposes. Dont use this.
 **/
inline void smps_bridge_pwm_out_voltage_set(float voltage){

    smps_bridge_pwm_duty_set(voltage * SMPS_OUT_VOLTAGE_TO_DUTY_RATIO_F32);
}

/**
 * @brief
 * @details Simple, just for test
 **/
inline float smps_bridge_pwm_out_voltage_get(void){

    return smps_bridge_pwm_duty_get() / SMPS_OUT_VOLTAGE_TO_DUTY_RATIO_F32;
}

/**
 * @brief
 * @details
 **/
inline void smps_bridge_max_current_set(float current){

    dac1_ch2_voltage_set(current * SMPS_DAC_VOLTAGE_TO_PRIM_CURRENT_RATIO_F32);
}

/**
 * @brief
 * @details
 **/
inline float smps_bridge_max_current_get(void){

    return (float)dac1_ch2_voltage_get()/SMPS_DAC_VOLTAGE_TO_PRIM_CURRENT_RATIO_F32;
}

/**
 * @brief Enable HRTIM1 fault
 * @details
 **/
inline void smps_fault_enable(void){

    hrtim_flt1_enable();
}

/**
 * @brief
 * @details
 **/
inline void smps_adc_reg_inj_start(void){

    adc1_reg_start();
    adc1_inj_start();
}

/**
 * @brief
 * @details  Set ADSTART and JADSTART bits, required by external triggers.
 **/
inline void smps_adc_reg_inj_stop(void){

    adc1_reg_stop();
    adc1_inj_stop();
}

/**
 * @brief Set SMPS control  loop frequency
 * @details @TODO: wywalic do hal
 **/
void smps_control_loop_freq_set(uint32_t frequency){

    uint16_t temp = HRTIM_MASTER_FREQUENCY/frequency;

    //!< @todo: dodac saturacje ??
    hrtim_MASTER_per_update(temp);
    hrtim_MASTER_cmp1_update(temp); //!< smps loop control
    hrtim_MASTER_cmp2_update(temp); //!< temp adc trigger @TODO: set in new function ??
}

/**
 * @brief
 * @details
 **/
inline void smps_control_loop_stop(void){

    hrtim_MASTER_cmp1_irq_disable();
}

/**
 * @brief
 * @details
 **/
inline void smps_control_loop_start(void){

    hrtim_MASTER_cmp1_irq_enable(); //!< restart control loop interrupt
}

/**
 * @brief
 * @details
 **/
inline void smps_burst_mode_start(void){

    hrtim_burst_mode_start();
}

/**
 * @brief
 * @details
 **/
inline void smps_burst_mode_stop(void){

    hrtim_burst_mode_stop();
}

/**
 * @brief
 * @details
 **/
inline void smps_burst_mode_update(float duty){

    if(duty > SMPS_BURST_MODE_DUTY_MAX_F32) duty = SMPS_BURST_MODE_DUTY_MAX_F32;
    else if(duty < SMPS_BURST_MODE_DUTY_MIN_F32) duty = SMPS_BURST_MODE_DUTY_MIN_F32;

    uint16_t cmp = (uint16_t)(duty * hrtim_burst_mode_per_get());
    hrtim_burst_mode_cmp_update(cmp);
}

/**
 * @brief
 * @details
 **/
inline float smps_burst_mode_duty_get(void){

    return (float)hrtim_burst_mode_cmp_get()/(float)hrtim_burst_mode_per_get();
}

/**
 * @brief
 * @details min 2 ms, max uin16 - 1
 **/
inline void smps_delay_ms(uint32_t delay_ms){

    timer6_wait_ms(delay_ms);
}

/**
 * @brief
 * @details
 */
inline void smps_fan_duty_set(float duty){

    float ccr = timer3_arr_get()*duty;

    timer3_ccr1_update(ccr);
}

/**
 * @} end of smps_function group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
