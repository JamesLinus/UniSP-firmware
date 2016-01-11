/**
 * @file timer.c
 * @brief timers function
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
#include <core_cmInstr.h>
#include "unisp/inc/hal/timer.h"
#include "unisp/conf/mcu_config.h"

/*
  +=============================================================================+
  | local definitions
  +=============================================================================+
*/

/*
  +=============================================================================+
  | module variables
  +=============================================================================+
*/

volatile uint8_t gTIM6_UIF;

/*
  +=============================================================================+
  | local functions' declarations
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @addtogroup timers
 * @{
 */


/**
 * @brief Initialize TIMER3 CH1 as PWM output
 * @details
 **/
void timer3_pwm_fan_init(void){

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    __DSB();

    TIM3->PSC = (uint16_t)(TIM3_PRESCALER);
    TIM3->ARR = (uint16_t)(1000);
    TIM3->CCR1 = 0;

    TIM3->CR1 |= TIM_CR1_ARPE;

    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //!< PWM Mode1
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCER |= TIM_CCER_CC1E;

    TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Get TIMER3 ARR
 * @details
 **/
uint16_t timer3_arr_get(void){

    return TIM3->ARR;
}

/**
 * @brief Get TIMER3 ARR
 * @details
 **/
void timer3_ccr1_update(uint16_t ccr1){

    TIM3->CCR1 = ccr1;

}

/**
 * @brief Initialize TIMER17 for debug purpose.
 * @details
 **/
void timer17_debug_time_ns_init(void){

    RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
    __DSB();

    //upcounter

    TIM17->PSC = (uint16_t)(TIM17_PRESCALER); //freq = 72MHz
    TIM17->ARR = (uint16_t)(0xffff);

}

/**
 * @brief Initialize TIMER7 for button debouncing.
 * @details @todo ustawić regulowany czas zczytywania z przyciskow, bo aktualnie jest na twardo ustawione.
 **/
void timer7_debouncing_init(void){

    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    __DSB();

    TIM7->CR1|=TIM_CR1_ARPE;
    TIM7->PSC = (uint16_t)(TIM7_PRESCALER); //freq timer = 1k Hz
    TIM7->ARR = (uint16_t)ARR_TIM7_VAL;
    TIM7->EGR|=TIM_EGR_UG; //re initialize
    TIM7->DIER|=TIM_DIER_UIE;//update event interrupt

    NVIC_EnableIRQ(TIM7_DAC2_IRQn);
    NVIC_SetPriority(TIM7_DAC2_IRQn, TIM7_DAC2_IRQ_PRIORITY);

    TIM7->CR1|=TIM_CR1_CEN; //enable counter

}

/**
 * @brief
 * @details one pulse mode. Disable counter after pulse
 **/
void timer6_wait_ms_init(void){

    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    __DSB();

    //upcounter
    TIM6->CR1|= TIM_CR1_URS; // only counter overflow generates UEV
    TIM6->CR1|= TIM_CR1_OPM; //one pulse mode

    TIM6->PSC = (uint16_t)(TIM6_PRESCALER); //freq = 1kHz
    TIM6->ARR = (uint16_t)(1);

    TIM6->DIER |= TIM_DIER_UIE; //update event interrupt

    NVIC_EnableIRQ(TIM6_DAC1_IRQn); //enable IRQ
    NVIC_SetPriority(TIM6_DAC1_IRQn, TIM6_DAC1_IRQ_PRIORITY);
    TIM6->CR1 |= TIM_CR1_CEN;  //initial enable counter

}

/**
 * @brief Count time in ms using TIMER6 (min 2ms, max uint16 - 1)
 * @details gTIM6_UIF sets in TIM6_DAC_IRQHandler
 * @param [in] time_in_ms
 **/
void timer6_wait_ms(uint16_t time_in_ms){

    if(time_in_ms<2) time_in_ms = 2;
    extern volatile uint8_t gTIM6_UIF;

    TIM6->ARR = (uint16_t)(time_in_ms-1);
    TIM6->CNT = (uint16_t)0; //reset counter

    gTIM6_UIF = 0; // reset flag
    TIM6->CR1 |= TIM_CR1_CEN;  //enable counter
    while(!gTIM6_UIF); //wait until flag

}

/**
 * @} end of timers group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
