/**
 * @file adc.h
 * @brief Header for adc.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include "unisp/conf/mcu_config.h"
#ifdef OUT_MODULE_ADC_
#include "mod/inc/hal/adc_mod.h"
#endif

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

#define ADC_1_REG_SEQ_LEN 2

/*
  +=============================================================================+
  | global variables
  +=============================================================================+
*/

extern volatile uint16_t gADC1_CH6;
extern volatile uint16_t gADC1_CH8;
extern volatile uint16_t gADC1_CH12;
extern volatile uint16_t gADC1_CH16;
extern volatile uint16_t gADC1_REG[ADC_1_REG_SEQ_LEN];

/*
  +=============================================================================+
  | global functions' declarations
  +=============================================================================+
*/

void adc1_init(void);
void adc1_reg_start(void);
void adc1_inj_start(void);
void adc1_reg_stop(void);
void adc1_inj_stop(void);

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* ADC_H_ */
