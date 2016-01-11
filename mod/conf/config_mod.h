/**
 * @file config_mod.h
 * @brief Output module uC basic configuration
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifdef OUT_MODULE_CFG_
#ifndef CONFIG_MOD_H_
#define CONFIG_MOD_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include "unisp/conf/mcu_config.h"

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

/*
  +====================================+
  | Analog
  +====================================+
*/

#define ADC2_RESOLUTION 10
#define ADC2_VALUE_MAX 1023
#define ADC2_STEP_F32 ((float)(ADC12_REF_VOLTAGE_F32/ADC2_VALUE_MAX))
#define ADC_VOLTAGE2
#define ADC_VOLTAGE3 gADC2_CH5 //!< fast channel, define in adc.c
#define ADC_CURRENT2
#define ADC_CURRENT3 gADC2_REG[0] //!< fast channel, define in adc.c

#define DAC2_RESOLUTION 12
#define DAC2_VALUE_MAX 4095
#define DAC2_VOLTAGE_MAX_F32 ((float) ANALOG_REF_VOLTAGE_F32)
#define DAC2_STEP_F32 ((float) DAC2_VOLTAGE_MAX_F32 / DAC2_VALUE_MAX)

/*
  +====================================+
  | HRTIMER CONFIGs
  +====================================+
*/

#define PRESCALER_HRTIM_TIMER_D 128
#define PRESCALER_HRTIM_TIMER_E 8
#define HRTIM_TIMER_D_CKPSCK 0
#define HRTIM_TIMER_E_CKPSCK 0
#define HRTIM_TIMER_D_FREQUENCY (HRTIM_HI_RES_FREQUENCY / PRESCALER_HRTIM_TIMER_D)
#define HRTIM_TIMER_E_FREQUENCY (HRTIM_HI_RES_FREQUENCY / PRESCALER_HRTIM_TIMER_E)

/*
  +====================================+
  | NVIC
  +====================================+
*/
#ifdef OUT_MODULE_NVIC_CFG_

//in STM32 only 4 bits of interrupt priority are used
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority 0 bits for subpriority */

#define NVIC_PRIORITY_GROUP NVIC_PRIORITYGROUP_3
#define mNVIC_ENCODE(preempt, sub)  NVIC_EncodePriority (NVIC_PRIORITY_GROUP, preempt, sub)

#define HRTIM1_TIME_IRQ_PREEMPT 0
#define HRTIM1_TIME_IRQ_SUB 0
#define HRTIM1_TIME_IRQ_PRIORITY mNVIC_ENCODE(HRTIM1_TIME_IRQ_PREEMPT, HRTIM1_TIME_IRQ_SUB)

#define HRTIM1_FLT_IRQ_PREEMPT 1
#define HRTIM1_FLT_IRQ_SUB 0
#define HRTIM1_FLT_IRQ_PRIORITY mNVIC_ENCODE(HRTIM1_FLT_IRQ_PREEMPT, HRTIM1_FLT_IRQ_SUB)

#define ADC1_2_IRQ_PREEMPT 2
#define ADC1_2_IRQ_SUB 0
#define ADC1_2_IRQ_PRIORITY mNVIC_ENCODE(ADC1_2_IRQ_PREEMPT, ADC1_2_IRQ_SUB)

#define DMA1_Channel2_IRQ_PREEMPT 2
#define DMA1_Channel2_IRQ_SUB 0
#define DMA1_Channel2_IRQ_PRIORITY mNVIC_ENCODE(DMA1_Channel2_IRQ_PREEMPT, DMA1_Channel2_IRQ_SUB)

#define HRTIM1_Master_IRQ_PREEMPT 2
#define HRTIM1_Master_IRQ_SUB 1
#define HRTIM1_Master_IRQ_PRIORITY mNVIC_ENCODE(HRTIM1_Master_IRQ_PREEMPT, HRTIM1_Master_IRQ_SUB)

#define HRTIM1_TIMA_IRQ_PREEMPT 3
#define HRTIM1_TIMA_IRQ_SUB 1
#define HRTIM1_TIMA_IRQ_PRIORITY mNVIC_ENCODE(HRTIM1_TIMA_IRQ_PREEMPT, HRTIM1_TIMA_IRQ_SUB)

#define HRTIM1_TIMD_IRQ_PREEMPT 4
#define HRTIM1_TIMD_IRQ_SUB 0
#define HRTIM1_TIMD_IRQ_PRIORITY mNVIC_ENCODE(HRTIM1_TIMD_IRQ_PREEMPT, HRTIM1_TIMD_IRQ_SUB)

#define DMA1_Channel1_IRQ_PREEMPT 4
#define DMA1_Channel1_IRQ_SUB 1
#define DMA1_Channel1_IRQ_PRIORITY mNVIC_ENCODE(DMA1_Channel1_IRQ_PREEMPT, DMA1_Channel1_IRQ_SUB)

#define SPI1_IRQ_PREEMPT 5
#define SPI1_IRQ_SUB 0
#define SPI1_IRQ_PRIORITY mNVIC_ENCODE(SPI1_IRQ_PREEMPT, SPI1_IRQ_SUB)

#define TIM6_DAC1_IRQ_PREEMPT 5
#define TIM6_DAC1_IRQ_SUB 1
#define TIM6_DAC1_IRQ_PRIORITY mNVIC_ENCODE(TIM6_DAC1_IRQ_PREEMPT, TIM6_DAC1_IRQ_SUB)

#define TIM7_DAC2_IRQ_PREEMPT 5
#define TIM7_DAC2_IRQ_SUB 1
#define TIM7_DAC2_IRQ_PRIORITY mNVIC_ENCODE(TIM7_DAC2_IRQ_PREEMPT, TIM7_DAC2_IRQ_SUB)

#endif /* OUT_MODULE_NVIC_CFG_ */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* CONFIG_MOD_H_ */
#endif /* OUT_MODULE_CFG_ */
