/**
 * @file dac_mod.h
 * @brief Header for dac_mod.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifdef OUT_MODULE_DAC_
#ifndef DAC_MOD_H_
#define DAC_MOD_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global functions' declarations
  +=============================================================================+
*/

void dac2_init(void);
void dac1_ch1_set(uint16_t val);
void dac2_ch1_set(uint16_t val);
uint16_t dac1_ch1_get(void);
uint16_t dac2_ch1_get(void);
void dac1_ch1_set_voltage(float voltage);
void dac2_ch1_set_voltage(float voltage);
float dac1_ch1_get_voltage(void);
float dac2_ch1_get_voltage(void);

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* DAC_MOD_H_ */
#endif /* OUT_MODULE_DAC_ */
