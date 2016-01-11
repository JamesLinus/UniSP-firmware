/**
 * @file dac.c
 * @brief
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

#include <stdint.h>
#include <stm32f334x8.h>
#include "unisp/inc/hal/dac.h"
#include "unisp/conf/mcu_config.h"

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @addtogroup dac
 * @{
 */

/**
 * @brief DAC1 init
 * @details
 **/
void dac1_init(void){

    RCC->APB1ENR |= RCC_APB1ENR_DAC1EN;
    // cant disconnect channel from GPIO :( :( :(
    DAC1->CR |= DAC_CR_EN1; // ch1 enable
    DAC1->CR |= DAC_CR_EN2; // ch2 enable

}

/**
 * @brief Set DAC1 DHR12R2 (CH2) register
 * @details Saturation on 0x0fff
 **/
void dac1_ch2_set(uint16_t val){

    if(val>0x0fff) val = 0x0fff; //saturation
    DAC1->DHR12R2 = val;

}

/**
 * @brief Get DAC1 DHR12R2 (CH2) register
 * @details
 **/
uint16_t dac1_ch2_get(void){

    return DAC1->DHR12R2;

}

/**
 * @brief Set DAC1 CH2 output voltage
 * @details
 **/
void dac1_ch2_voltage_set(float voltage){

    dac1_ch2_set(voltage/DAC1_STEP_F32);

}

/**
 * @brief Get DAC2 CH2 output voltage
 * @details
 **/
float dac1_ch2_voltage_get(void){

    return dac1_ch2_get() * DAC1_STEP_F32;

}

/**
 * @} end of dac group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
