/**
 * @file gpio_pin_cfg_mod.h
 * @brief Headers for gpio_pin_cfg_mod.c
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
#ifndef GPIO_PIN_CFG_MOD_H_
#define GPIO_PIN_CFG_MOD_H_

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include <stdint.h>

/*
+=============================================================================+
| global functions' declarations
+=============================================================================+
*/

void gpio_pin_cfg_mod_init(void);
void gpio_hrtim_in_cfg_mod_init(void);
void gpio_hrtim_out_cfg_mod_init(void);

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* GPIO_PIN_CFG_MOD_H_ */
#endif
