/**
 * @file gpio_pin_cfg.c
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

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include "unisp/inc/hal/gpio.h"
#include "unisp/inc/gpio_pin_cfg.h"
#include "unisp/conf/mcu_config.h"
#include "unisp/conf/io_pins_config.h"

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
void gpio_pin_cfg_init(void){

// initial HRTIM to prevent unexpected state before ....
    gpio_pin_cfg(HRTIM1_CHA1_GPIO, HRTIM1_CHA1_pin, GPIO_OUT_PP_HS_PULL_DOWN);
    gpio_pin_cfg(HRTIM1_CHA2_GPIO, HRTIM1_CHA2_pin, GPIO_OUT_PP_HS_PULL_DOWN);
    /* gpio_pin_cfg(HRTIM1_CHB1_GPIO, HRTIM1_CHB1_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHB2_GPIO, HRTIM1_CHB2_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHC1_GPIO, HRTIM1_CHC1_pin, GPIO_OUT_PP_HS_PULL_DOWN); */
    /* gpio_pin_cfg(HRTIM1_CHC2_GPIO, HRTIM1_CHC2_pin, GPIO_OUT_PP_HS_PULL_DOWN); */

    gpio_pin_cfg(BUTTON0_GPIO, BUTTON0_pin, GPIO_IN_PULL_UP); ///
    gpio_pin_cfg(MISC0_GPIO, MISC0_pin, GPIO_OUT_PP_LS_PULL_DOWN); ///
    gpio_pin_cfg(MISC1_GPIO, MISC1_pin, GPIO_OUT_PP_LS_PULL_DOWN); /// LED0
    gpio_pin_cfg(MISC5_GPIO, MISC5_pin, GPIO_OUT_PP_LS_PULL_DOWN); /// LED1
    gpio_pin_cfg(MISC6_GPIO, MISC6_pin, GPIO_OUT_PP_LS_PULL_DOWN); /// LED2
    gpio_pin_cfg(MISC7_GPIO, MISC7_pin, GPIO_OUT_PP_LS_PULL_DOWN); /// LED3

    //ADC
    gpio_pin_cfg(ADC_V1_GPIO, ADC_V1_pin, GPIO_ANALOG); //ADC12_IN6
    gpio_pin_cfg(ADC_I1_GPIO, ADC_I1_pin, GPIO_ANALOG); //ADC12_IN8
    gpio_pin_cfg(ADC_TEMP_GPIO, ADC_TEMP_pin, GPIO_ANALOG); //ADC1_IN12

    //COMP
    gpio_pin_cfg(COMP2_INP_GPIO, COMP2_INP_pin, GPIO_ANALOG);

    //SPI - UI
    gpio_pin_cfg(SPI1_MISO_GPIO, SPI1_MISO_pin, GPIO_AF5_PP_HS_PULL_DOWN);
    gpio_pin_cfg(SPI1_MOSI_GPIO, SPI1_MOSI_pin, GPIO_AF5_PP_HS_PULL_DOWN);
    gpio_pin_cfg(SPI1_SCK_GPIO, SPI1_SCK_pin, GPIO_AF5_PP_HS_PULL_DOWN);
    gpio_pin_cfg(SPI1_NSS_GPIO, SPI1_NSS_pin, GPIO_AF5_PP_HS_PULL_DOWN);

    gpio_pin_cfg(TIM3_CH1_GPIO, TIM3_CH1_pin, GPIO_AF2_PP_MS_PULL_DOWN); /// TIM3 - PWM FAN

#ifdef OUT_MODULE_GPIO_PIN_CFG_
    gpio_pin_cfg_mod_init();
#endif

}

/**
 * @brief HRTIM IN GPIO initialization
 * @details Must be done before HRTIM OUT initialization. Called in hrtim_init()
 **/
void gpio_hrtim_in_cfg_init(void){

#ifdef OUT_MODULE_GPIO_PIN_CFG_
    gpio_hrtim_in_cfg_mod_init();
#endif
}

/**
 * @brief HRTIM OUT GPIO initialization
 * @details Must be done AFTER HRTIM control register programming,
 * and once the counters are enebled. Called in hrtim_init()
 **/
void gpio_hrtim_out_cfg_init(void){

    gpio_pin_cfg(HRTIM1_CHA1_GPIO, HRTIM1_CHA1_pin, GPIO_AF13_PP_HS_PULL_DOWN);
    gpio_pin_cfg(HRTIM1_CHA2_GPIO, HRTIM1_CHA2_pin, GPIO_AF13_PP_HS_PULL_DOWN);
    /* gpio_pin_cfg(HRTIM1_CHB1_GPIO, HRTIM1_CHB1_pin, GPIO_AF13_PP_HS); */
    /* gpio_pin_cfg(HRTIM1_CHB2_GPIO, HRTIM1_CHB2_pin, GPIO_AF13_PP_HS); */
    /* gpio_pin_cfg(HRTIM1_CHC1_GPIO, HRTIM1_CHC1_pin, GPIO_AF13_PP_HS); */
    /* gpio_pin_cfg(HRTIM1_CHC2_GPIO, HRTIM1_CHC2_pin, GPIO_AF13_PP_HS); */

#ifdef OUT_MODULE_GPIO_PIN_CFG_
    gpio_hrtim_out_cfg_mod_init();
#endif
}

/**
 * @} end of edm_function group
 **/

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
