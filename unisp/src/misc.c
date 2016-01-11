/**
 * @file misc.c
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

#include <stm32f334x8.h>
#include "unisp/inc/misc.h"
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
 * @addtogroup misc
 * @{
 */

/**
 * @brief Delay in ns
 * @details saturation sets at 100000 ns. Shitty accurate. Low limit depends on core freq.
 **/
inline void delay_ns(uint32_t time){

    if(time>100000) time = 100000; //saturation
    volatile uint32_t counter = 0;
    for(counter=0; counter<m_CLOCK_CYCLE_DELAY_NS(time); counter+=1) asm("NOP");

}

/**
 * @brief Debug break
 * @details Only for debug purposes
 **/
void debug_break(void){

    asm("NOP");asm("NOP");asm("NOP");

}

/**
 * @brief Reset Button_buffer structure.
 * @details If you need more button add new cases here, in Button_buffer structure and in TIMER IRQ handler (TIM7). Reset after each button usage!!
 * @param [in,out] *S Button_buffer struct
 * @param [in] button button to reset. Reset all if button = 255
 * @return none
 **/
void reset_button_buff(volatile struct Button_buffer *S, uint8_t button){

    switch(button){
    case 0:
        S->button0 = 0;
        break;
    case 1:
        S->button1 = 0;
        break;
    case 2:
        S->button2 = 0;
        break;
    case 3:
        S->button3 = 0;
        break;
    case 4:
        S->button4 = 0;
        break;
    case 5:
        S->button5 = 0;
        break;
    case 6:
        S->button6 = 0;
        break;
    case 7:
        S->button7 = 0;
        break;
    case 8:
        S->button8 = 0;
        break;
    case 9:
        S->button9 = 0;
        break;

    case 255:
        S->button0 = 0;
        S->button1 = 0;
        S->button2 = 0;
        S->button3 = 0;
        S->button4 = 0;
        S->button5 = 0;
        S->button6 = 0;
        S->button7 = 0;
        S->button8 = 0;
        S->button9 = 0;
        break;

    }

}

/**
 * @} end of misc group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
