/**
 * @file smps_config.h
 * @brief SMPS config
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef SMPS_CONFIG_H_
#define SMPS_CONFIG_H_

#include "unisp/conf/mcu_config.h"
#include "unisp/conf/io_pins_config.h"


/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

#define SMPS_CONTROL_LOOP_FREQUENCY 20000ul //!< f=20kHz => T=50000 ns

/*
  +====================================+
  | SMPS GPIO
  +====================================+
*/
/* #define SMPS_INRUSH_GPIO MISC7_GPIO */
/* #define SMPS_INRUSH_pin MISC7_pin */
/* #define SMPS_INRUSH_ODR SMPS_INRUSH_GPIO->ODR */
/* #define SMPS_INRUSH_PROTECTION_ENABLE SMPS_INRUSH_ODR &=~ (1<<SMPS_INRUSH_pin) //enable if pin reset */
/* #define SMPS_INRUSH_PROTECTION_DISABLE SMPS_INRUSH_ODR |= (1<<SMPS_INRUSH_pin) //disable if pin set */
#define SMPS_RUN_LED_ON LED0_SET
#define SMPS_RUN_LED_OFF LED0_RST
#define SMPS_OVERLOAD_LED_ON LED2_SET
#define SMPS_OVERLOAD_LED_OFF LED2_RST

#define SMPS_FAN_DUTY_MIN ((float) 0.2)
#define SMPS_FAN_DUTY_MAX ((float) 0.99)

/*
  +====================================+
  | SMPS PARAMETERS
  +====================================+
*/

#define SMPS_INRUSH_DELAY_ms 2500 //!< in rush delay in ms. @TODO: obsolute?

#define SMPS_BRIDGE_SWITCH_FREQUENCY  100000ul//150000ul//200000ul
#define SMPS_BRIDGE_DUTY_CYCLE_MIN_F32 ((float) 0.04) //!< 0.03 absolute minimum !
#define SMPS_BRIDGE_DEAT_TIME_MIN_F32 ((float) 0.1) //!<
#define SMPS_BRIDGE_DUTY_CYCLE_MAX_F32 (1.00 - SMPS_BRIDGE_DEAT_TIME_MIN_F32)  //!<
#define SMPS_BRIDGE_DUTY_CYCLE_CORRECTION_F32 ((float) 0.02) //!< include transistors delay.

#define SMPS_OUT_VOLTAGE_TO_DUTY_RATIO_F32 ((float)SMPS_TRANSFORMER_TURNS_RATIO_F32 * SMPS_BRIDGE_VOLTAGE_MIN_F32) //!<
#define SMPS_OUT_VOLTAGE_MAX_F32 ((float)(SMPS_BRIDGE_DUTY_CYCLE_MAX_F32 * SMPS_OUT_VOLTAGE_TO_DUTY_RATIO_F32)) //!<
#define SMPS_OUT_VOLTAGE_MIN_F32 ((float) 40 ) //!<
#define SMPS_START_DELAY_ms 500 //!< time on init voltage after start
#define SMPS_OUT_VOLTAGE_INIT_F32 ((float) 10.0)
#define SMPS_OVERVOLTAGE_COEFF_F32 ((float) 1.1) //!<
#define SMPS_OVERLOAD_RESTART_DELAY_ms 200

/*
  +====================================+
  | BURST MODE CONFIG
  +====================================+
*/

// burst duty defined in IDLE state
#define SMPS_BRIDGE_DUTY_BURST_ENABLE_F32 SMPS_BRIDGE_DUTY_CYCLE_MIN_F32 //((float) 0.1 )
#define SMPS_BRIDGE_DUTY_BURST_DISABLE_F32 ((float) 0.15 )
#define SMPS_BURST_MODE_DUTY_STEP_F32 ((float) 0.01) //!<
#define SMPS_BURST_MODE_START_DUTY_F32 HRTIM_BURST_MODE_INIT_DUTY_F32
#define SMPS_BURST_MODE_DUTY_MIN_F32 HRTIM_BURST_MODE_INIT_DUTY_F32
#define SMPS_BURST_MODE_DUTY_MAX_F32 ((float) 0.95)

/*
  +====================================+
  | SOFT START CONFIG
  +====================================+
*/

#define SMPS_SOFTSTART_VOLTAGE_DIFF_F32 ((float) 5.0) //!<
#define SMPS_SOFTSTART_VOLTAGE_STEP_F32 ((float) 5.0) //!<
#define SMPS_SOFTSTART_DELAY_ms 300 //!<

/*
  +====================================+
  | CONVERTER PARAMETERs
  +====================================+
*/

#define SMPS_EFFICIENCY_F32 ((float) 0.8) //!< worst case
#define SMPS_SECONDARY_TURNS_F32 ((float) 4.0 ) //!<
#define SMPS_PRIMARY_TURNS_F32 ((float) 10.0 ) //!<
#define SMPS_BRIDGE_VOLTAGE_MAX_F32 ((float) 420.0) //!<
#define SMPS_BRIDGE_VOLTAGE_MIN_F32 ((float) 380.0) //!<
#define SMPS_TRANSFORMER_TURNS_RATIO_F32 ((float) SMPS_SECONDARY_TURNS_F32/SMPS_PRIMARY_TURNS_F32) //!< input to output transformer turns ratio
#define SMPS_PRIM_CURRENT_LIMIT_F32 ((float) 5.4) //!< ABSOLUTE CURRENT LIMIT !
#define SMPS_PRIM_CURRENT_MAX_F32 ((float) 5.0) //!< @todo: uniezaleznic od SMPS_INPUT_MAX_CURRENT
#define SMPS_OVERLOAD_CURRENT_INIT ((float) 2.0) //!< @TODO: ustaw to jak nalezy
#define SMPS_OVERLOAD_COEFF_F32 ((float) 1.2)
#define SMPS_OVERLOAD_RESTART_VOLTAGE_F32 ((float) 40.0)

#define SMPS_PRIM_PEAK_CURRENT_MAX_F32 ((float) SMPS_PRIM_CURRENT_MAX_F32)
#define SMPS_SEC_DIODE_VOLT_DROP_F32 ((float) 0.0))
#define SMPS_SEC_CAP_F32 ((float) 4400*1e-6))
#define SMPS_SEC_INDUCTOR_F32
#define SMPS_PRIM_CURRENT_SENSE_DIVIDER_F32 ((float) 100) //!< current sense prim to sec current ratio
#define SMPS_PRIM_CURRENT_SENSE_RESISTOR_F32 ((float) 60.2) //!< current sense resistor
#define SMPS_PRIM_CURRENT_SENSE_CORRECTION_F32 ((float)1.0)
#define SMPS_PRIM_CURRENT_TO_VOLTAGE_RATIO_F32 ((float)(SMPS_PRIM_CURRENT_SENSE_CORRECTION_F32 * SMPS_PRIM_CURRENT_SENSE_DIVIDER_F32 / SMPS_PRIM_CURRENT_SENSE_RESISTOR_F32)) //!< Primary current to ADC voltage scalling factor
#define SMPS_OUT_VOLTAGE_SENSE_DIVIDER_F32 ((float) 50.0)
#define SMPS_OUT_VOLTAGE_SENSE_CORRECTION_F32 ((float) 1.0)
#define SMPS_OUT_VOLTAGE_TO_VOLTAGE_RATIO_F32 ((float)SMPS_OUT_VOLTAGE_SENSE_CORRECTION_F32 * SMPS_OUT_VOLTAGE_SENSE_DIVIDER_F32) //!< Output voltage to ADC voltage scalling factor

#define SMPS_OUT_BRIDGE_CURRENT_MAX ((float))
#define SMPS_BRIDGE_CURRENT_MAX ((float))

/*
  +====================================+
  | ADCs PARAMETERS
  +====================================+
*/

#define SMPS_UC_TEMP_V25_F32 ((float)(1.43)) //!< uC temp sensor const V
#define SMPS_UC_TEMP_AVGS_F32 ((float)(4.3)) //!< uC temp sensor const mV/*C
#define SMPS_ADC_STEP_F32 ((float)ADC1_STEP_F32)
#define SMPS_ADC_PRIM_CURRENT_SCALE_F32 ((float)SMPS_PRIM_CURRENT_SENSE_TO_VOLTAGE_RATIO_F32)
#define SMPS_ADC_OUT_VOLTAGE_SCALE_F32 ((float)SMPS_OUT_VOLTAGE_SENSE_TO_VOLTAGE_RATIO_F32)
#define SMPS_ADC_AUX_TEMP ADC_AUX_TEMP
#define SMPS_ADC_UC_TEMP ADC_UC_TEMP
#define SMPS_ADC_PRIM_CURRENT ADC_CURRENT1
#define SMPS_ADC_OUT_VOLTAGE ADC_VOLTAGE1
#define SMPS_ADC_RESOLUTION
#define SMPS_ADC_CH_PRIM_CURRENT
#define SMPS_ADC_CH_SEC_VOLTAGE
#define SMPS_ADC_NUM_OF_SAMPLES

/*
  +====================================+
  | DACs PARAMETERS
  +====================================+
*/

#define SMPS_DAC_VOLTAGE_TO_PRIM_CURRENT_RATIO_F32 ((float) (1/ SMPS_PRIM_CURRENT_TO_VOLTAGE_RATIO_F32)) //!<

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* SMPS_CONFIG_H_ */
