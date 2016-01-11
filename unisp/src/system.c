/**
 * @file system.c
 * @brief System functions. Based on Freddie Chopin, http://www.freddiechopin.info/
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334X8
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
#include "unisp/inc/bb/hdr_rcc.h"
#include "unisp/inc/system.h"
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
  | global functions' declarations
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @addtogroup system_function
 * @{
 */

/**
 * @brief Configures Flash latency.
 * @details
 * @param [in] frequency defines the target frequency of the core
 **/
void flash_latency(uint32_t frequency){

    uint32_t latency;

    if (frequency < 24000000ul) latency = 0;
    else if (frequency < 48000000ul) latency = 1;
    else latency = 2;

//    FLASH->ACR |= latency;				// set latency
    FLASH->ACR = FLASH_ACR_PRFTBE | latency; //prefetch buffer enable

}

/**
 * @brief Enables FPU
 * @details Enables FPU in Cortex-M4 for both privileged and user mode. This is
 * done by enabling CP10 and CP11 coprocessors in CPACR register (possible only
 * when in privileged mode).
 **/
void fpu_enable(void){

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));	// set CP10 and CP11 Full Access
#endif

}

/**
 * @brief Starts the PLL
 * @details Configure and enable PLL to achieve some frequency with some crystal.
 * Before the speed change Flash latency is configured via flash_latency(). PLL
 * parameters are based on both function parameters. The PLL is set up,
 * started and connected. AHB clock ratio is set to 1:1 with core clock, APB1 -
 * 1:2 (max 36MHz), APB2 - 1:1 (max 72MHz).
 *
 * @param [in] crystal is the frequency of the crystal resonator connected to the
 * STM32F334X8
 * @param [in] frequency is the desired target frequency after enabling the PLL (max 72MHz)
 *
 * @return real frequency that was set
 **/
uint32_t pll_start(uint32_t crystal, uint32_t frequency){

    volatile uint32_t mul, pll_in, pll_out;
    volatile uint32_t best_mul=0, pll_out_best=0;

#ifdef OSC_EXTERNAL
    volatile uint32_t div;
    volatile uint32_t best_div=0;

    RCC->CR |= RCC_CR_HSEON; // enable HSE

    flash_latency(frequency);				// configure Flash latency for desired frequency

    for(div =1; div<=16; div+=1) { //PREDIV [0:16]
        pll_in = crystal/div;

        for(mul=2; mul<=16; mul+=1){ //PLLMUL[2:16]
            pll_out = pll_in * mul;

            if((pll_out > 72000000ul) || (pll_out < 16000000ul)) // skip invalid value
                continue;

            if(pll_out > frequency) // skip value over desired frequnecy
                continue;

            if(pll_out > pll_out_best){
                pll_out_best = pll_out;
                best_mul = mul;
                best_div = div;
            }
        }
    }

    // configure PLL factors
    RCC->CFGR |=  ((best_mul-2) << RCC_CFGR_PLLMUL_bit); // set PLL multification factor
    RCC->CFGR2 |= ((best_div-1) << RCC_CFGR2_PREDIV_bit); // set HSE divider to PLL
    RCC->CFGR |= RCC_CFGR_PLLSRC;           // HSE/PRESCALER clk source
    while(!(RCC->CR & RCC_CR_HSERDY));      // wait for stable clock

    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_HPRE_DIV1;	/// AHB - no prescaler, APB1 - divide by 4, APB2 - divide by 1
    RCC->CR |= RCC_CR_PLLON;				// enable PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));   	// wait for PLL lock

    RCC->CFGR |= RCC_CFGR_SW_PLL;			// change SYSCLK to PLL
    while (((RCC->CFGR) & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	// wait for switch

    return pll_out_best;

#else
    RCC->CR |= RCC_CR_HSION; // enable HSI

    flash_latency(frequency);				// configure Flash latency for desired frequency

    pll_in = crystal/2;

    for(mul=2; mul<=16; mul+=1){ //PLLMUL[2:16]
        pll_out = pll_in * mul;

        if((pll_out > 72000000ul) || (pll_out < 16000000ul)) // skip invalid value
            continue;

        if(pll_out > frequency) // skip value over desired frequnecy
            continue;

        if(pll_out > pll_out_best){
            pll_out_best = pll_out;
            best_mul = mul;
        }
    }

// configure PLL factors
    RCC->CFGR |=  ((best_mul-2) << RCC_CFGR_PLLMUL_bit); // set PLL multification factor

    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_HPRE_DIV1;	/// AHB - no prescaler, APB1 - divide by 4, APB2 - divide by 1
    RCC->CR |= RCC_CR_PLLON;				// enable PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));   	// wait for PLL lock

    RCC->CFGR |= RCC_CFGR_SW_PLL;			// change SYSCLK to PLL
    while (((RCC->CFGR) & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	// wait for switch

    return pll_out_best;

#endif

}

/**
 *@} end of system_function group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
