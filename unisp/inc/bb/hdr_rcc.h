/** \file hdr_rcc.h
 * \brief Header with definition of bits in RCC control registers

 */

/******************************************************************************
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 4.6.2
* 	20110921 (release) [ARM/embedded-4_6-branch revision 182083]
******************************************************************************/

#ifndef HDR_RCC_H_
#define HDR_RCC_H_

#include "unisp/inc/bb/hdr_bitband.h"

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

/*
+-----------------------------------------------------------------------------+
| RCC_CR - Clock Control Register
+-----------------------------------------------------------------------------+
*/

#define RCC_CR_PLLRDY_bit					25
#define RCC_CR_PLLON_bit					24
#define RCC_CR_CSSON_bit					19
#define RCC_CR_HSEBYP_bit					18
#define RCC_CR_HSERDY_bit					17
#define RCC_CR_HSEON_bit					16
#define RCC_CR_HSICAL_bit					8
#define RCC_CR_HSICAL_0_bit					8
#define RCC_CR_HSICAL_1_bit					9
#define RCC_CR_HSICAL_2_bit					10
#define RCC_CR_HSICAL_3_bit					11
#define RCC_CR_HSICAL_4_bit					12
#define RCC_CR_HSICAL_5_bit					13
#define RCC_CR_HSICAL_6_bit					14
#define RCC_CR_HSICAL_7_bit					15
#define RCC_CR_HSITRIM_bit					3
#define RCC_CR_HSITRIM_0_bit				3
#define RCC_CR_HSITRIM_1_bit				4
#define RCC_CR_HSITRIM_2_bit				5
#define RCC_CR_HSITRIM_3_bit				6
#define RCC_CR_HSITRIM_4_bit				7
#define RCC_CR_HSIRDY_bit					1
#define RCC_CR_HSION_bit					0


#define RCC_CR_PLLRDY_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_PLLRDY_bit)
#define RCC_CR_PLLON_bb						bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_PLLON_bit)
#define RCC_CR_CSSON_bb						bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_CSSON_bit)
#define RCC_CR_HSEBYP_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSEBYP_bit)
#define RCC_CR_HSERDY_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSERDY_bit)
#define RCC_CR_HSEON_bb						bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSEON_bit)
#define RCC_CR_HSICAL_0_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_0_bit)
#define RCC_CR_HSICAL_1_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_1_bit)
#define RCC_CR_HSICAL_2_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_2_bit)
#define RCC_CR_HSICAL_3_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_3_bit)
#define RCC_CR_HSICAL_4_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_4_bit)
#define RCC_CR_HSICAL_5_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_5_bit)
#define RCC_CR_HSICAL_6_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_6_bit)
#define RCC_CR_HSICAL_7_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSICAL_7_bit)
#define RCC_CR_HSITRIM_0_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSITRIM_0_bit)
#define RCC_CR_HSITRIM_1_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSITRIM_1_bit)
#define RCC_CR_HSITRIM_2_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSITRIM_2_bit)
#define RCC_CR_HSITRIM_3_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSITRIM_3_bit)
#define RCC_CR_HSITRIM_4_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSITRIM_4_bit)
#define RCC_CR_HSIRDY_bb					bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSIRDY_bit)
#define RCC_CR_HSION_bb						bitband_t m_BITBAND_PERIPH(&RCC->CR, RCC_CR_HSION_bit)

/*
+-----------------------------------------------------------------------------+
| RCC_CFGR - Clock Configuration Register
+-----------------------------------------------------------------------------+
*/

#define RCC_CFGR_PLLNODIV_bit		31
#define RCC_CFGR_MCOPRE_bit		28
#define RCC_CFGR_MCOPRE_0_bit		28
#define RCC_CFGR_MCOPRE_1_bit		29
#define RCC_CFGR_MCOPRE_2_bit		30
#define RCC_CFGR_MCO_bit		24
#define RCC_CFGR_MCO_0_bit		24
#define RCC_CFGR_MCO_1_bit		25
#define RCC_CFGR_MCO_2_bit		26
#define RCC_CFGR_PLLMUL_bit		18
#define RCC_CFGR_PLLMUL_O_bit		18
#define RCC_CFGR_PLLMUL_1_bit		19
#define RCC_CFGR_PLLMUL_2_bit		20
#define RCC_CFGR_PLLMUL_3_bit		21
#define RCC_CFGR_PLLXTPRE_bit		17
#define RCC_CFGR_PLLSRC_bit		16
#define RCC_CFGR_PRE2_bit		11
#define RCC_CFGR_PRE2_0_bit		11
#define RCC_CFGR_PRE2_1_bit		11
#define RCC_CFGR_PRE1_bit		8
#define RCC_CFGR_PRE1_0_bit		8
#define RCC_CFGR_PRE1_1_bit		9
#define RCC_CFGR_PRE1_2_bit		10
#define RCC_CFGR_HPRE_bit		4
#define RCC_CFGR_HPRE_0_bit		4
#define RCC_CFGR_HPRE_1_bit		5
#define RCC_CFGR_HPRE_2_bit		6
#define RCC_CFGR_HPRE_3_bit		7
#define RCC_CFGR_SWS_bit		2
#define RCC_CFGR_SWS_0_bit		2
#define RCC_CFGR_SWS_1_bit		3
#define RCC_CFGR_SW_bit		0
#define RCC_CFGR_SW_0_bit		0
#define RCC_CFGR_SW_1_bit		1



#define RCC_CFGR_PLLNODIV_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLNODIV_bit)
#define RCC_CFGR_MCOPRE_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCOPRE_0_bit)
#define RCC_CFGR_MCOPRE_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCOPRE_1_bit)
#define RCC_CFGR_MCOPRE_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCOPRE_2_bit)
#define RCC_CFGR_MCO_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCO_0_bit)
#define RCC_CFGR_MCO_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCO_1_bit)
#define RCC_CFGR_MCO_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_MCO_2_bit)
#define RCC_CFGR_PLLMUL_O_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLMUL_O_bit)
#define RCC_CFGR_PLLMUL_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLMUL_1_bit)
#define RCC_CFGR_PLLMUL_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLMUL_2_bit)
#define RCC_CFGR_PLLMUL_3_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLMUL_3_bit)
#define RCC_CFGR_PLLXTPRE_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLXTPRE_bit)
#define RCC_CFGR_PLLSRC_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PLLSRC_bit)
#define RCC_CFGR_PRE2_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PRE2_0_bit)
#define RCC_CFGR_PRE2_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PRE2_1_bit)
#define RCC_CFGR_PRE1_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PRE1_0_bit)
#define RCC_CFGR_PRE1_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PRE1_1_bit)
#define RCC_CFGR_PRE1_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_PRE1_2_bit)
#define RCC_CFGR_HPRE_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_HPRE_0_bit)
#define RCC_CFGR_HPRE_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_HPRE_1_bit)
#define RCC_CFGR_HPRE_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_HPRE_2_bit)
#define RCC_CFGR_HPRE_3_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_HPRE_3_bit)
#define RCC_CFGR_SWS_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_SWS_0_bit)
#define RCC_CFGR_SWS_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_SWS_1_bit)
#define RCC_CFGR_SW_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_SW_0_bit)
#define RCC_CFGR_SW_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR , RCC_CFGR_SW_1_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_CIR - Clock interrupt register
+-----------------------------------------------------------------------------+
*/

#define RCC_CIR_CSSC_bit					23
#define RCC_CIR_PLLRDYC_bit					20
#define RCC_CIR_HSERDYC_bit					19
#define RCC_CIR_HSIRDYC_bit					18
#define RCC_CIR_LSERDYC_bit					17
#define RCC_CIR_LSIRDYC_bit					16
#define RCC_CIR_PLLRDYIE_bit				12
#define RCC_CIR_HSERDYIE_bit				11
#define RCC_CIR_HSIRDYIE_bit				10
#define RCC_CIR_LSERDYIE_bit				9
#define RCC_CIR_LSIRDYIE_bit				8
#define RCC_CIR_CSSF_bit					7
#define RCC_CIR_PLLRDYF_bit					4
#define RCC_CIR_HSERDYF_bit					3
#define RCC_CIR_HSIRDYF_bit					2
#define RCC_CIR_LSERDYF_bit					1
#define RCC_CIR_LSIRDYF_bit					0


#define RCC_CIR_CSSC_bb						bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_CSSC_bit)
#define RCC_CIR_PLLRDYC_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_PLLRDYC_bit)
#define RCC_CIR_HSERDYC_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSERDYC_bit)
#define RCC_CIR_HSIRDYC_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSIRDYC_bit)
#define RCC_CIR_LSERDYC_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSERDYC_bit)
#define RCC_CIR_LSIRDYC_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSIRDYC_bit)
#define RCC_CIR_PLLRDYIE_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_PLLRDYIE_bit)
#define RCC_CIR_HSERDYIE_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSERDYIE_bit)
#define RCC_CIR_HSIRDYIE_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSIRDYIE_bit)
#define RCC_CIR_LSERDYIE_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSERDYIE_bit)
#define RCC_CIR_LSIRDYIE_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSIRDYIE_bit)
#define RCC_CIR_CSSF_bb						bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_CSSF_bit)
#define RCC_CIR_PLLRDYF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_PLLRDYF_bit)
#define RCC_CIR_HSERDYF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSERDYF_bit)
#define RCC_CIR_HSIRDYF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_HSIRDYF_bit)
#define RCC_CIR_LSERDYF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSERDYF_bit)
#define RCC_CIR_LSIRDYF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CIR, RCC_CIR_LSIRDYF_bit)



/*
+-----------------------------------------------------------------------------+
| RCC_APB2RSTR - APB2 peripheral reset register
+-----------------------------------------------------------------------------+
*/

#define RCC_APB2RSTR_HRTIM1EN_bit			29
#define RCC_APB2RSTR_TIM16RST_bit			17
#define RCC_APB2RSTR_TIM15RST_bit			16
#define RCC_APB2RSTR_USART1RST_bit			14
#define RCC_APB2RSTR_SPI1RST_bit			12
#define RCC_APB2RSTR_TIM1RST_bit		   11
#define RCC_APB2RSTR_SYSCFGRST_bit			0


#define RCC_APB2RSTR_HRTIM1EN_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_HRTIM1EN_bit)
#define RCC_APB2RSTR_TIM16RST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_TIM16RST_bit)
#define RCC_APB2RSTR_TIM15RST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_TIM15RST_bit)
#define RCC_APB2RSTR_SPI1RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_SPI1RST_bit)
#define RCC_APB2RSTR_USART1RST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_USART1RST_bit)
#define RCC_APB2RSTR_TIM1RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST_bit)
#define RCC_APB2RSTR_SYSCFGRST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB2RSTR, RCC_APB2RSTR_SYSCFGRST_bit)



/*
+-----------------------------------------------------------------------------+
| RCC_APB1RSTR - APB1 peripheral reset register
+-----------------------------------------------------------------------------+
*/

#define RCC_APB1RSTR_DAC1RST_bit				29
#define RCC_APB1RSTR_PWRRST_bit				28
#define RCC_APB1RSTR_DAC2RST_bit				26
#define RCC_APB1RSTR_CANRST_bit			25
#define RCC_APB1RSTR_I2CRST_bit			21
#define RCC_APB1RSTR_USART3RST_bit			18
#define RCC_APB1RSTR_USART2RST_bit			17
#define RCC_APB1RSTR_SPI3RST_bit			15
#define RCC_APB1RSTR_SPI2RST_bit			14
#define RCC_APB1RSTR_WWDGRST_bit			11
#define RCC_APB1RSTR_TIM7RST_bit			5
#define RCC_APB1RSTR_TIM6RST_bit			4
#define RCC_APB1RSTR_TIM3RST_bit			1
#define RCC_APB1RSTR_TIM2RST_bit			0


#define RCC_APB1RSTR_DAC1RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_DAC1RST_bit)
#define RCC_APB1RSTR_PWRRST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_PWRRST_bit)
#define RCC_APB1RSTR_DAC2RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_DAC2RST_bit)
#define RCC_APB1RSTR_CANRST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_CANRST_bit)
#define RCC_APB1RSTR_I2CRST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_I2CRST_bit)
#define RCC_APB1RSTR_USART3RST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_USART3RST_bit)
#define RCC_APB1RSTR_USART2RST_bb			bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_USART2RST_bit)
#define RCC_APB1RSTR_SPI3RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_SPI3RST_bit)
#define RCC_APB1RSTR_SPI2RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_SPI2RST_bit)
#define RCC_APB1RSTR_WWDGRST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_WWDGRST_bit)
#define RCC_APB1RSTR_TIM7RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_TIM7RST_bit)
#define RCC_APB1RSTR_TIM6RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_TIM6RST_bit)
#define RCC_APB1RSTR_TIM3RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_TIM3RST_bit)
#define RCC_APB1RSTR_TIM2RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->APB1RSTR, RCC_APB1RSTR_TIM2RST_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_AHBENR - RCC AHB peripheral clock register
+-----------------------------------------------------------------------------+
*/


#define RCC_AHBENR_ADC12EN_bit		28
#define RCC_AHBENR_TSCEN_bit		24
#define RCC_AHBENR_GPIOFEN_bit		22
#define RCC_AHBENR_GPIODEN_bit		20
#define RCC_AHBENR_GPIOCEN_bit		19
#define RCC_AHBENR_GPIOBEN_bit		18
#define RCC_AHBENR_GPIOAEN_bit		17
#define RCC_AHBENR_CRCEN_bit		6
#define RCC_AHBENR_FLITFEN_bit		4
#define RCC_AHBENR_SRAMEN_bit		2
#define RCC_AHBENR_DMA1EN_bit		0


#define RCC_AHBENR_ADC12EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_ADC12EN_bit)
#define RCC_AHBENR_TSCEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_TSCEN_bit)
#define RCC_AHBENR_GPIOFEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_GPIOFEN_bit)
#define RCC_AHBENR_GPIODEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_GPIODEN_bit)
#define RCC_AHBENR_GPIOCEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_GPIOCEN_bit)
#define RCC_AHBENR_GPIOBEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_GPIOBEN_bit)
#define RCC_AHBENR_GPIOAEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_GPIOAEN_bit)
#define RCC_AHBENR_CRCEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_CRCEN_bit)
#define RCC_AHBENR_FLITFEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_FLITFEN_bit)
#define RCC_AHBENR_SRAMEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_SRAMEN_bit)
#define RCC_AHBENR_DMA1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->AHBENR , RCC_AHBENR_DMA1EN_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_APB2ENR - RCC APB2 peripheral clock enable register
+-----------------------------------------------------------------------------+
*/


#define RCC_APB2ENR_HRTIM1EN_bit		29
#define RCC_APB2ENR_TIM17EN_bit		18
#define RCC_APB2ENR_TIM16EN_bit		17
#define RCC_APB2ENR_TIM15EN_bit		16
#define RCC_APB2ENR_USART1EN_bit		14
#define RCC_APB2ENR_SPI1EN_bit		12
#define RCC_APB2ENR_TIM1EN_bit		11
#define RCC_APB2ENR_SYSCFGEN_bit		0


#define RCC_APB2ENR_HRTIM1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_HRTIM1EN_bit)
#define RCC_APB2ENR_TIM17EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_TIM17EN_bit)
#define RCC_APB2ENR_TIM16EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_TIM16EN_bit)
#define RCC_APB2ENR_TIM15EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_TIM15EN_bit)
#define RCC_APB2ENR_USART1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_USART1EN_bit)
#define RCC_APB2ENR_SPI1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_SPI1EN_bit)
#define RCC_APB2ENR_TIM1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_TIM1EN_bit)
#define RCC_APB2ENR_SYSCFGEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB2ENR , RCC_APB2ENR_SYSCFGEN_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_APB1ENR - RCC APB1 peripheral clock enable register
+-----------------------------------------------------------------------------+
*/


#define RCC_APB1ENR_DAC1EN_bit		29
#define RCC_APB1ENR_PWREN_bit		28
#define RCC_APB1ENR_DAC2EN_bit		26
#define RCC_APB1ENR_CANEN_bit		25
#define RCC_APB1ENR_I2C1EN_bit		21
#define RCC_APB1ENR_USART3EN_bit		18
#define RCC_APB1ENR_USART2EN_bit		17
#define RCC_APB1ENR_WWDGEN_bit		11
#define RCC_APB1ENR_TIM7EN_bit		5
#define RCC_APB1ENR_TIM6EN_bit		4
#define RCC_APB1ENR_TIM3EN_bit		1
#define RCC_APB1ENR_TIM2EN_bit		0


#define RCC_APB1ENR_DAC1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_DAC1EN_bit)
#define RCC_APB1ENR_PWREN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_PWREN_bit)
#define RCC_APB1ENR_DAC2EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_DAC2EN_bit)
#define RCC_APB1ENR_CANEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_CANEN_bit)
#define RCC_APB1ENR_I2C1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_I2C1EN_bit)
#define RCC_APB1ENR_USART3EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_USART3EN_bit)
#define RCC_APB1ENR_USART2EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_USART2EN_bit)
#define RCC_APB1ENR_WWDGEN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_WWDGEN_bit)
#define RCC_APB1ENR_TIM7EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_TIM7EN_bit)
#define RCC_APB1ENR_TIM6EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_TIM6EN_bit)
#define RCC_APB1ENR_TIM3EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_TIM3EN_bit)
#define RCC_APB1ENR_TIM2EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->APB1ENR , RCC_APB1ENR_TIM2EN_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_BDCR - Backup domain control register
+-----------------------------------------------------------------------------+
*/

#define RCC_BDCR_BDRST_bit					16
#define RCC_BDCR_RTCEN_bit					15
#define RCC_BDCR_RTCSEL_bit					8
#define RCC_BDCR_RTCSEL_0_bit				8
#define RCC_BDCR_RTCSEL_1_bit				9
#define RCC_BDCR_LSEDRV_bit					3
#define RCC_BDCR_LSEDRV_0_bit				3
#define RCC_BDCR_LSEDRV_1_bit				4
#define RCC_BDCR_LSEBYP_bit					2
#define RCC_BDCR_LSERDY_bit					1
#define RCC_BDCR_LSEON_bit					0


#define RCC_BDCR_BDRST_bb					bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_BDRST_bit)
#define RCC_BDCR_RTCEN_bb					bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_RTCEN_bit)
#define RCC_BDCR_RTCSEL_0_bb				bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_RTCSEL_0_bit)
#define RCC_BDCR_RTCSEL_1_bb				bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_RTCSEL_1_bit)
#define RCC_BDCR_LSEBYP_bb					bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_LSEBYP_bit)
#define RCC_BDCR_LSERDY_bb					bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_LSERDY_bit)
#define RCC_BDCR_LSEON_bb					bitband_t m_BITBAND_PERIPH(&RCC->BDCR, RCC_BDCR_LSEON_bit)

/*
+-----------------------------------------------------------------------------+
| RCC_CSR - Control/status register
+-----------------------------------------------------------------------------+
*/

#define RCC_CSR_LPWRRSTF_bit				31
#define RCC_CSR_WWDGRSTF_bit				30
#define RCC_CSR_IWDGRSTF_bit				29
#define RCC_CSR_SFTRSTF_bit					28
#define RCC_CSR_PORRSTF_bit					27
#define RCC_CSR_PINRSTF_bit					26
#define RCC_CSR_OBLRSTF_bit					25
#define RCC_CSR_RMVF_bit					24
#define RCC_CSR_LSIRDY_bit					1
#define RCC_CSR_LSION_bit					0

#define RCC_CSR_LPWRRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_LPWRRSTF_bit)
#define RCC_CSR_WWDGRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_WWDGRSTF_bit)
#define RCC_CSR_IWDGRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_IWDGRSTF_bit)
#define RCC_CSR_SFTRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_SFTRSTF_bit)
#define RCC_CSR_PORRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_PORRSTF_bit)
#define RCC_CSR_PINRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_PINRSTF_bit)
#define RCC_CSR_OBLRSTF_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_OBLRSTF_bit)
#define RCC_CSR_RMVF_bb						bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_RMVF_bit)
#define RCC_CSR_LSIRDY_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_LSIRDY_bit)
#define RCC_CSR_LSION_bb					bitband_t m_BITBAND_PERIPH(&RCC->CSR, RCC_CSR_LSION_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_AHBRSTR - RCC AHB peripheral reset register
+-----------------------------------------------------------------------------+
*/


#define RCC_AHBRSTR_TSCRST_bit			24
#define RCC_AHBRSTR_ADC12RST_bit		28
#define RCC_AHBRSTR_GPIOFRST_bit			22
#define RCC_AHBRSTR_GPIODRST_bit			20
#define RCC_AHBRSTR_GPIOCRST_bit			19
#define RCC_AHBRSTR_GPIOBRST_bit			18
#define RCC_AHBRSTR_GPIOARST_bit			17


#define RCC_AHBRSTR_TSCRST_bb				bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_TSCRST_bit)
#define RCC_AHB1RSTR_ADC12RST_bb				bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_ADC12RST_bit)
#define RCC_AHBRSTR_GPIOFRST_bb			bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_GPIOFRST_bit)
#define RCC_AHBRSTR_GPIODRST_bb			bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_GPIODRST_bit)
#define RCC_AHBRSTR_GPIOCRST_bb			bitband_t m_BITBAND_PERIPH(&RCC->AHB1RSTR, RCC_AHBRSTR_GPIOCRST_bit)
#define RCC_AHBRSTR_GPIOBRST_bb			bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_GPIOBRST_bit)
#define RCC_AHBRSTR_GPIOARST_bb			bitband_t m_BITBAND_PERIPH(&RCC->AHBRSTR, RCC_AHBRSTR_GPIOARST_bit)

/*
+-----------------------------------------------------------------------------+
| RCC_CFGR2
+-----------------------------------------------------------------------------+
*/

#define RCC_CFGR2_PREDIV_bit        0
#define RCC_CFGR2_PREDIV_0_bit		0
#define RCC_CFGR2_PREDIV_1_bit		1
#define RCC_CFGR2_PREDIV_2_bit		2
#define RCC_CFGR2_PREDIV_3_bit		3
#define RCC_CFGR2_ADC12PRES_0_bit		4
#define RCC_CFGR2_ADC12PRES_1_bit		5
#define RCC_CFGR2_ADC12PRES_2_bit		6
#define RCC_CFGR2_ADC12PRES_3_bit		7
#define RCC_CFGR2_ADC12PRES_4_bit		8

#define RCC_CFGR2_PREDIV_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_PREDIV_0_bit)
#define RCC_CFGR2_PREDIV_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_PREDIV_1_bit)
#define RCC_CFGR2_PREDIV_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_PREDIV_2_bit)
#define RCC_CFGR2_PREDIV_3_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_PREDIV_3_bit)
#define RCC_CFGR2_ADC12PRES_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_ADC12PRES_0_bit)
#define RCC_CFGR2_ADC12PRES_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_ADC12PRES_1_bit)
#define RCC_CFGR2_ADC12PRES_2_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_ADC12PRES_2_bit)
#define RCC_CFGR2_ADC12PRES_3_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_ADC12PRES_3_bit)
#define RCC_CFGR2_ADC12PRES_4_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR2 , RCC_CFGR2_ADC12PRES_4_bit)


/*
+-----------------------------------------------------------------------------+
| RCC_CFGR3
+-----------------------------------------------------------------------------+
*/

#define RCC_CFGR3_USART1SW_0_bit		0
#define RCC_CFGR3_USART1SW_1_bit		1
#define RCC_CFGR3_I2C1SW_bit		4
#define RCC_CFGR3_TIM1SW_bit		8
#define RCC_CFGR3_HRTIM1EN_bit		12
#define RCC_CFGR3_USART2SW_0_bit		16
#define RCC_CFGR3_USART2SW_1_bit		17
#define RCC_CFGR3_USART3SW_0_bit		18
#define RCC_CFGR3_USART3SW_1_bit		19


#define RCC_CFGR3_USART1SW_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART1SW_0_bit)
#define RCC_CFGR3_USART1SW_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART1SW_1_bit)
#define RCC_CFGR3_I2C1SW_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_I2C1SW_bit)
#define RCC_CFGR3_TIM1SW_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_TIM1SW_bit)
#define RCC_CFGR3_HRTIM1EN_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_HRTIM1EN_bit)
#define RCC_CFGR3_USART2SW_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART2SW_0_bit)
#define RCC_CFGR3_USART2SW_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART2SW_1_bit)
#define RCC_CFGR3_USART3SW_0_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART3SW_0_bit)
#define RCC_CFGR3_USART3SW_1_bb 	bitband_t m_BITBAND_PERIPH(&RCC->CFGR3 , RCC_CFGR3_USART3SW_1_bit)


/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* HDR_RCC_H_ */
