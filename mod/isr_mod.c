/**
 * @file isr_mod.c
 * @brief
 * @author raiden00
 */

/********************************************************************
 * project: UniSP
 * chip: STM32F334X8
 * compiler: arm-none-eabi-gcc
 *
 ********************************************************************/

#ifdef OUT_MODULE_ISR_
#warning "Compile isr_mod.c"

/*
  +===================================================================+
  | includes
  +===================================================================+
*/

#ifdef OUT_MODULE_MAIN_
#include "main_mod.h"
#else
#include "main.h"
#endif

/*
  +===================================================================+
  | ISRs
  +===================================================================+
*/

/**
 *@addtogroup IRQHandlers
 * @{
 */

//!< redefine HRTIM1_FLT_IRQHandler
#ifdef OUT_MODULE_HRTIM_FLT_IRQ_
#warning "Compile isr_mod.c with HRTIM1_FLT_IRQHandler"
/**
 * @brief HRTIM1 faults interrupt routine
 * @details
 **/
void HRTIM1_FLT_IRQHandler(void){

}
#endif /* OUT_MODULE_HRTIM_FLT_IRQ_ */

//!< redefine ADC1_2_IRQHandler
#ifdef OUT_MODULE_ADC1_2_IRQ_
#warning "Compile isr_mod.c with HRTIM1_ADC1_2_IRQHandler"
/**
 * @brief ADC1/2 interrupt.
 * @details Handle ADC1/2 injected sequence
 **/
void ADC1_2_IRQHandler(void){

}
#endif /* OUT_MODULE_ADC1_2_IRQ_ */

//!< redefine HRTIM1_Master_IRQHandler
#ifdef OUT_MODULE_HRTIM_MASTER_IRQ_
#warning "Compile isr_mod.c with HRTIM1_MASTER_IRQHandler"
/**
 * @brief HRTIM1 MASTER interrupt routine
 * @details
 **/
void HRTIM1_Master_IRQHandler(void){

}
#endif /* OUT_MODULE_HRTIM_MASTER_IRQ_ */

/**
 *@} end of IRQHandlers group
 */

/*******************************************************************
 * END OF FILE
 ********************************************************************/
#endif
