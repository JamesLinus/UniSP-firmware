/**
 * @file config.h
 * @brief Basic uc configuration
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#ifdef OUT_MODULE_CFG_
#warning "Including mod/conf/mcu_config_mod.h"
#include "mod/conf/mcu_config_mod.h"
#endif /* OUT_MODULE_CFG */

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

/*
  +====================================+
  | System clocks
  +====================================+
*/

#define OSC_EXTERNAL 1 //!< use external oscilator at default
#define CRYSTAL	8000000ul	//!< quartz crystal resonator which is connected to the chip
                            /// or HSI oscilator frequency
#ifndef OSC_EXTERNAL
#warning "Internal oscilator, core freq = 64 MHz"
#define FREQUENCY 64000000ul	///< desired target frequency of the core (HSI)
#else
#warning "External oscilator, core freq = 72MHz"
#define FREQUENCY 72000000ul	///< desired target frequency of the core (HSE)
#endif

#define APB1_PRESCALER 4 //!<  can be changed in pll_start() function
#define APB2_PRESCALER 1  //!<  changed in pll_start() function
#define AHB_PRESCALER 1 //!<  changed in pll_start() function
#define APB1_FREQUENCY (FREQUENCY/APB1_PRESCALER)  //!< == 18MHz
#define APB2_FREQUENCY (FREQUENCY/APB2_PRESCALER) //!<  == 74MHz
#define AHB_FREQUENCY (FREQUENCY/AHB_PRESCALER) //!<  == 74MHz

#if APB1_PRESCALER == 1
#define TIM_APB1_FREQUENCY APB1_FREQUENCY
#else
#define TIM_APB1_FREQUENCY 2*APB1_FREQUENCY // 37MHz
#endif

#if APB2_PRESCALER == 1
#define TIM_APB2_FREQUENCY APB2_FREQUENCY
#else
#define TIM_APB2_FREQUENCY 2*APB2_FREQUENCY
#endif

#define CORE_CLOCK_PERIOD_ns (1000000000/FREQUENCY)
#define APB2_CLOCK_PERIOD_ns (1000000000/APB2_FREQUENCY)

#define m_CLOCK_CYCLE_DELAY_NS(time_in_ns) (time_in_ns/CORE_CLOCK_PERIOD_ns) // macro for hardware delay

#define SYSTICK_PRESCALER 8 //!< changed  in systick_init
#define SYSTICK_CLOCK_FREQUENCY (AHB_FREQUENCY / SYSTICK_PRESCALER) //!< = 9MHz

/*
  +====================================+
  | Analog
  +====================================+
*/

#define ANALOG_REF_VOLTAGE_F32 ((float) 3.3)
#define ADC12_REF_VOLTAGE_F32 ((float) ANALOG_REF_VOLTAGE_F32)

#define ADC1_RESOLUTION 10
#define ADC1_VALUE_MAX 1023
#define ADC1_STEP_F32 ((float)(ADC12_REF_VOLTAGE_F32/ADC1_VALUE_MAX))
#define ADC_VOLTAGE1 gADC1_CH6 //!< slow channel, define in adc.c
#define ADC_CURRENT1 gADC1_CH8 //!< slow channel, define in adc.c
#define ADC_AUX_TEMP gADC1_REG[0] //!< slow channel, define in adc.c
#define ADC_UC_TEMP gADC1_REG[1] //!< slow channel, define in adc.c

#define DAC12_REF_VOLTAGE_F32 ((float) ANALOG_REF_VOLTAGE_F32)
#define DAC1_RESOLUTION 12
#define DAC1_VALUE_MAX 4095
#define DAC1_VOLTAGE_MAX_F32 ((float) ANALOG_REF_VOLTAGE_F32)
#define DAC1_STEP_F32 ((float) DAC1_VOLTAGE_MAX_F32 / DAC1_VALUE_MAX)

/*
  +====================================+
  | HRTIMER CONFIGs
  +====================================+
*/

#define HRTIM_FREQUENCY (FREQUENCY * 2ull)
#define HRTIM_HI_RES_FREQUENCY (HRTIM_FREQUENCY * 32) //!< 4608000000
#define HRTIM_MASTER_PRESCALER 128
#define HRTIM_TIMER_A_PRESCALER 1
#define HRTIM_TIMER_B_PRESCALER 1
#define HRTIM_TIMER_C_PRESCALER 1
#define HRTIM_TIMER_MASTER_CKPSCK 7
#define HRTIM_TIMER_A_CKPSCK 0
#define HRTIM_TIMER_B_CKPSCK 0
#define HRTIM_TIMER_C_CKPSCK 0
#define HRTIM_MASTER_FREQUENCY  (HRTIM_HI_RES_FREQUENCY / HRTIM_MASTER_PRESCALER) //!< 36 MHz
#define HRTIM_TIMER_A_FREQUENCY (HRTIM_HI_RES_FREQUENCY / HRTIM_TIMER_A_PRESCALER) //!< 658 MHz
#define HRTIM_TIMER_B_FREQUENCY (HRTIM_HI_RES_FREQUENCY / HRTIM_TIMER_B_PRESCALER) //!<
#define HRTIM_TIMER_C_FREQUENCY (HRTIM_HI_RES_FREQUENCY / HRTIM_TIMER_C_PRESCALER) //!<
#define HRTIM_TIMER_A_PERIOD_ns (1e9/HRTIM_TIMER_A_FREQUENCY) //!< TIMER A clock period in ns
#define HRTIM_TIMER_A_ADC_TRIGGER_OFFSET_ns 240 //!< @TODO: describe if still in use?
#define HRTIM_TIMER_A_ADC_TRIGGER_OFFSET ((uint16_t)(HRTIM_TIMER_A_ADC_TRIGGER_OFFSET_ns/HRTIM_TIMER_A_PERIOD_ns))

#define HRTIM_BURST_MODE_INIT_PERIOD ((uint16_t) 100) //!< init valeu for burst mode PER register
#define HRTIM_BURST_MODE_INIT_DUTY_F32 ((float) 0.5) //!< initial burst mode duty. Defined in IDLE states
#define HRTIM_BURST_MODE_INIT_COMPARE ((uint16_t) (HRTIM_BURST_MODE_INIT_DUTY_F32 * HRTIM_BURST_MODE_INIT_PERIOD)) //!<init valeu for burst mode CMP register

/*
  +====================================+
  | TIMERs CONFIGs
  +====================================+
*/

#define TIM3_FREQUENCY 10000ul //!< TIM3 - fan pwm
#define TIM6_FREQUENCY 1000ul //!< TIM6 - simple delays
#define TIM7_FREQUENCY 1000ul //!< TIM7 - button debouncing
#define TIM17_FREQUENCY 72000000ul //!< debug purposes
#define TIM3_PRESCALER ((TIM_APB1_FREQUENCY / TIM3_FREQUENCY) -1)
#define TIM6_PRESCALER ((TIM_APB1_FREQUENCY / TIM6_FREQUENCY) - 1)
#define TIM7_PRESCALER ((TIM_APB1_FREQUENCY / TIM6_FREQUENCY) - 1)
#define TIM17_PRESCALER ((TIM_APB2_FREQUENCY / TIM17_FREQUENCY) - 1)
#define TIM17_PERIOD_ns (1000000000/TIM17_FREQUENCY)
#define ARR_TIM7_VAL 499

/*
  +====================================+
  | NVIC
  +====================================+
*/
#ifndef OUT_MODULE_NVIC_CFG_

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

#else
#warning "NVIC CFG from mod/conf/mcu_cofig_mod.h"
#endif /* OUT_MODULE_NVIC_CFG_ */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* CONFIG_H_ */
