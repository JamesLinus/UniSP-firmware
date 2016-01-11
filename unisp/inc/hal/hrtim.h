/**
 * @file hrtim.h
 * @brief Header for hrtim.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef HRTIM_H_
#define HRTIM_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#ifdef OUT_MODULE_HRTIM_
#include "mod/inc/hal/hrtim_mod.h"
#endif

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

#define HRTIM_TIMER_A_INDEX 0
#define HRTIM1_TIMER_A_O12EN HRTIM1->sCommonRegs.OENR = (HRTIM_OENR_TA1OEN | HRTIM_OENR_TA2OEN);

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

void hrtim_init(void);
void hrtim_MASTER_per_update(uint16_t period);
uint16_t hrtim_MASTER_per_get(void);
void hrtim_MASTER_rep_update(uint16_t repetition);
void hrtim_MASTER_cmp1_update(uint16_t compare1);
void hrtim_MASTER_cmp2_update(uint16_t compare2);
void hrtim_MASTER_cmp1_irq_enable(void);
void hrtim_MASTER_cmp1_irq_disable(void);

void hrtim_TIMER_A_out_disable(void);
void hrtim_TIMER_A_out_enable(void);
void hrtim_TIMER_A_per_update(uint16_t period);
void hrtim_TIMER_A_cmp1_update(uint16_t period);

void hrtim_flt1_enable(void);
inline void hrtim_burst_mode_per_update(uint16_t per);
inline void hrtim_burst_mode_cmp_update(uint16_t cmp);
inline uint16_t hrtim_burst_mode_per_get(void);
inline uint16_t hrtim_burst_mode_cmp_get(void);
inline void hrtim_burst_mode_start(void);
inline void hrtim_burst_mode_stop(void);

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* HRTIM_H_ */
