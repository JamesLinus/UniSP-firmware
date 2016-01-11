/**
 * @file gpio_pin_cfg_mod.c
 * @brief GPIO pins initialization
 * @author raiden00
 * @date 2015-10-07
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifdef OUT_MODULE_GPIO_PIN_CFG_
#warning "Compile gpio_pin_cfg_mod.c"

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include "unisp/inc/hal/gpio.h"
#include "unisp/conf/io_pins_config.h"
#include "mod/inc/gpio_pin_cfg_mod.h"

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @addtogroup gpio_pin_cfg
 * @{
 **/

/**
 * @brief GPIO initialization
 * @details HRTIM I/O initialization in hrtim_init()
 **/
void gpio_pin_cfg_mod_init(void){

// initial HRTIM to prevent unexpected state before ....
    /* gpio_pin_cfg(HRTIM1_CHD1_GPIO, HRTIM1_CHD1_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHD2_GPIO, HRTIM1_CHD2_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHE1_GPIO, HRTIM1_CHE1_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHE2_GPIO, HRTIM1_CHE2_pin,  GPIO_OUT_PP_HS_PULL_DOWN); */

//    gpio_pin_cfg(MISC2_GPIO, MISC2_pin, GPIO_OUT_PP_LS); ///
//    gpio_pin_cfg(MISC3_GPIO, MISC3_pin, GPIO_OUT_PP_LS); ///
//    gpio_pin_cfg(MISC4_GPIO, MISC4_pin, GPIO_OUT_PP_HS); ///
//    gpio_pin_cfg(MISC5_GPIO, MISC5_pin, GPIO_OUT_PP_HS); /// LED1
//    gpio_pin_cfg(MISC8_GPIO, MISC8_pin, GPIO_OUT_PP_LS); ///
//    gpio_pin_cfg(MISC9_GPIO, MISC9_pin, GPIO_OUT_PP_LS); ///

    //ADC
    /* gpio_pin_cfg(ADC_V2_GPIO, ADC_V2_pin, GPIO_ANALOG); //ADC12_IN7 */
    /* gpio_pin_cfg(ADC_V3_GPIO, ADC_V3_pin, GPIO_ANALOG); //ADC2_IN5 */
    /* gpio_pin_cfg(ADC_I2_GPIO, ADC_I2_pin, GPIO_ANALOG); //ADC12_IN9 */
    /* gpio_pin_cfg(ADC_I3_GPIO, ADC_I3_pin, GPIO_ANALOG); //ADC2_IN3 */

    //COMP
//    gpio_pin_cfg(COMP4_INP_GPIO, COMP4_INP_pin, GPIO_ANALOG);
//    gpio_pin_cfg(COMP6_INP_GPIO, COMP6_INP_pin, GPIO_ANALOG);
}

/**
 * @brief HRTIM IN GPIO initialization
 * @details Must be done before HRTIM OUT initialization. Called in hrtim_init()
 **/
void gpio_hrtim_in_cfg_mod_init(void){

    /* gpio_pin_cfg(HRTIM1_FLT5_GPIO, HRTIM1_FLT5_pin, GPIO_AF3_PP_HS); */
    /* gpio_pin_cfg(HRTIM1_EEV1_GPIO, HRTIM1_EEV1_pin, GPIO_AF3_PP_HS); */
    /* gpio_pin_cfg(HRTIM1_EEV2_GPIO, HRTIM1_EEV2_pin, GPIO_AF3_PP_HS); */
}

/**
 * @brief HRTIM OUT GPIO initialization
 * @details Must be done AFTER HRTIM control register programming,
 * and once the counters are enebled. Called in hrtim_init()
 **/
void gpio_hrtim_out_cfg_mod_init(void){

    /* gpio_pin_cfg(HRTIM1_CHD1_GPIO, HRTIM1_CHD1_pin, GPIO_AF13_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHD2_GPIO, HRTIM1_CHD2_pin, GPIO_AF13_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHE1_GPIO, HRTIM1_CHE1_pin, GPIO_AF3_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHE2_GPIO, HRTIM1_CHE2_pin, GPIO_AF3_PP_HS_PULL_DOWN); */
}

/**
 * @} end of gpio_pin_cfg
 **/

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif
