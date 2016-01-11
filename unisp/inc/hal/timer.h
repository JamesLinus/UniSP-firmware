/**
 *  @file timer.h
 * @brief Headers for timer.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#ifdef OUT_MODULE_TIMER_
#include "mod/inc/hal/timer_mod.h"
#endif /* OUT_MODULE_TIMER_ */

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

#define TIM17_CNT_RST_ENABLE  TIM17->CNT = 0; TIM17->CR1 |= TIM_CR1_CEN;
#define TIM17_CNT_DISABLE  TIM17->CR1 &=~ TIM_CR1_CEN;

/*
  +=============================================================================+
  | strange variables
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global variables
  +=============================================================================+
*/

extern volatile uint8_t gTIM6_UIF;

/*
  +=============================================================================+
  | global functions' declarations
  +=============================================================================+
*/

void timer7_debouncing_init(void);
void timer6_wait_ms_init(void);
void timer6_wait_ms(uint16_t time_in_ms);
void timer17_debug_time_ns_init(void);
void timer3_pwm_fan_init(void);
uint16_t timer3_arr_get(void);
void timer3_ccr1_update(uint16_t ccr1);

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* TIMER_H_ */
