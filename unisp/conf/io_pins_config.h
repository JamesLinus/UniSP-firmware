/**
 * @file io_pins_config.h
 * @brief IO pins definitions. For GPIO initialization look at src/gpio_pin_cfg.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef IO_PINS_CONFIG_H_
#define IO_PINS_CONFIG_H_

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

/*
  +=====================================+
  | MISCs pins
  +=====================================+
*/
//!< for available alternate functions form MISCx pins look at STM32F334 datasheet
#define MISC0_GPIO GPIOA
#define MISC0_pin 0
#define MISC1_GPIO GPIOA
#define MISC1_pin 1
#define MISC2_GPIO GPIOA
#define MISC2_pin 2
#define MISC3_GPIO GPIOA
#define MISC3_pin 3
#define MISC4_GPIO GPIOB
#define MISC4_pin 10
#define MISC5_GPIO GPIOA
#define MISC5_pin 12
#define MISC6_GPIO GPIOC
#define MISC6_pin 10
#define MISC7_GPIO GPIOD
#define MISC7_pin 2
#define MISC8_GPIO GPIOB
#define MISC8_pin 8
#define MISC9_GPIO GPIOB
#define MISC9_pin 9

//some ODR definitions
//#define MISC0_ODR MISC0_GPIO->ODR
#define MISC1_ODR MISC1_GPIO->ODR
//#define MISC2_ODR MISC2_GPIO->ODR
//#define MISC3_ODR MISC3_GPIO->ODR
#define MISC4_ODR MISC4_GPIO->ODR
#define MISC5_ODR MISC5_GPIO->ODR
//#define MISC6_ODR MISC6_GPIO->ODR
#define MISC7_ODR MISC7_GPIO->ODR
//#define MISC8_ODR MISC8_GPIO->ODR
//#define MISC9_ODR MISC9_GPIO->ODR

#define MISC1 (1 << MISC1_pin)
#define MISC1_BSRRL MISC1_GPIO->BSRRL
#define MISC1_BSRRH MISC1_GPIO->BSRRH
#define MISC1_SET MISC1_BSRRL = MISC1
#define MISC1_RST MISC1_BSRRH = MISC1

#define MISC4 (1 << MISC4_pin)
#define MISC4_BSRRL MISC4_GPIO->BSRRL
#define MISC4_BSRRH MISC4_GPIO->BSRRH
#define MISC4_SET MISC4_BSRRL = MISC4
#define MISC4_RST MISC4_BSRRH = MISC4

#define MISC5 (1 << MISC5_pin)
#define MISC5_BSRRL MISC5_GPIO->BSRRL
#define MISC5_BSRRH MISC5_GPIO->BSRRH
#define MISC5_SET MISC5_BSRRL = MISC5
#define MISC5_RST MISC5_BSRRH = MISC5

#define MISC6 (1 << MISC6_pin)
#define MISC6_BSRRL MISC6_GPIO->BSRRL
#define MISC6_BSRRH MISC6_GPIO->BSRRH
#define MISC6_SET MISC6_BSRRL = MISC6
#define MISC6_RST MISC6_BSRRH = MISC6

#define MISC7 (1 << MISC7_pin)
#define MISC7_BSRRL MISC7_GPIO->BSRRL
#define MISC7_BSRRH MISC7_GPIO->BSRRH
#define MISC7_SET MISC7_BSRRL = MISC7
#define MISC7_RST MISC7_BSRRH = MISC7

/*
  +=====================================+
  | Fan pins
  +=====================================+
*/

#define TIM3_CH1_GPIO GPIOC
#define TIM3_CH1_pin 6
#define TIM3_CH1 (1<<TIM3_CH1_pin)
#define TIM3_CH1_ODR TIM3_CH1_GPIO->ODR
#define FAN_ODR TIM3_CH1_ODR
#define FAN TIM3_CH1

/*
  +=====================================+
  | ADC pins
  +=====================================+
*/

#define ADC_V1_GPIO GPIOC //!< SMPS OUT VOLTAGE ADC
#define ADC_V1_pin 0
#define ADC_V2_GPIO GPIOC //!<
#define ADC_V2_pin 1
#define ADC_V3_GPIO GPIOC //!< fast ADC
#define ADC_V3_pin 4
#define ADC_I1_GPIO GPIOC //!< SMPS PRIM CURENT ADC
#define ADC_I1_pin 2
#define ADC_I2_GPIO GPIOC //!<
#define ADC_I2_pin 3
#define ADC_I3_GPIO GPIOA //!< fast ADC
#define ADC_I3_pin 6
#define ADC_TEMP_GPIO GPIOB //!< external temperature sensor
#define ADC_TEMP_pin 1

/*
  +=====================================+
  | DAC pins
  +=====================================+
*/

/* #define DAC1_CH1_GPIO GPIOA */
/* #define DAC1_CH1_pin 4 */

/*
  +=====================================+
  | COMP pins
  +=====================================+
*/

#define COMP2_INP_GPIO GPIOA //!< SMPS overcurrent protection
#define COMP2_INP_pin 7
#define COMP4_INP_GPIO GPIOB
#define COMP4_INP_pin 0
#define COMP6_INP_GPIO GPIOB
#define COMP6_INP_pin 11

/*
  +=====================================+
  | OPAMP pins
  +=====================================+
*/

/* #define OPAMP2_VINM_GPIO GPIOC */
/* #define OPAMP2_VINM_pin 5 */
/* #define OPAMP2_VINP_GPIO GPIOB */
/* #define OPAMP2_VINP_pin 0 */

/*
  +=====================================+
  | HRTIM pins
  +=====================================+
*/

#define HRTIM1_CHA1_GPIO GPIOA // SMPS PWM1
#define HRTIM1_CHA1_pin 8
#define HRTIM1_CHA2_GPIO GPIOA // SMPS PWM2
#define HRTIM1_CHA2_pin 9
#define HRTIM1_CHB1_GPIO GPIOA
#define HRTIM1_CHB1_pin 10
#define HRTIM1_CHB2_GPIO GPIOA
#define HRTIM1_CHB2_pin 11
#define HRTIM1_CHC1_GPIO GPIOB
#define HRTIM1_CHC1_pin 12
#define HRTIM1_CHC2_GPIO GPIOB
#define HRTIM1_CHC2_pin 13
#define HRTIM1_CHD1_GPIO GPIOB
#define HRTIM1_CHD1_pin 14
#define HRTIM1_CHD2_GPIO GPIOB
#define HRTIM1_CHD2_pin 15
#define HRTIM1_CHE1_GPIO GPIOC
#define HRTIM1_CHE1_pin 8
#define HRTIM1_CHE2_GPIO GPIOC
#define HRTIM1_CHE2_pin 9
#define HRTIM1_FLT5_GPIO GPIOC
#define HRTIM1_FLT5_pin 7
#define HRTIM1_EEV1_GPIO GPIOC
#define HRTIM1_EEV1_pin 11
#define HRTIM1_EEV2_GPIO GPIOC
#define HRTIM1_EEV2_pin 12

/*
  +=====================================+
  | USART pins
  +=====================================+
*/

#define USART1_TX_GPIO GPIOB
#define USART1_TX_pin 6
#define USART1_RX_GPIO GPIOB
#define USART1_RX_pin 7
/* #define USART3_TX_GPIO MICS7_GPIO */
/* #define USART3_TX_pin MISC7_pin */
/* #define USART3_RX_GPIO MISC8_GPIO */
/* #define USART3_RX_pin MISC8_pin */

/*
  +=====================================+
  | SPI pins
  +=====================================+
*/

#define SPI1_NSS_GPIO GPIOA
#define SPI1_NSS_pin 15
#define SPI1_SCK_GPIO GPIOB
#define SPI1_SCK_pin 3
#define SPI1_MISO_GPIO GPIOB
#define SPI1_MISO_pin 4
#define SPI1_MOSI_GPIO GPIOB
#define SPI1_MOSI_pin 5

/*
  +=====================================+
  | UI pins
  +=====================================+
*/

#define LED0_SET MISC1_SET
#define LED0_RST MISC1_RST
#define LED1_SET MISC5_SET
#define LED1_RST MISC5_RST
#define LED2_SET MISC6_SET
#define LED2_RST MISC6_RST
#define LED3_SET MISC7_SET
#define LED3_RST MISC7_RST

#define BUTTON0_GPIO GPIOC
#define BUTTON0_pin   13
#define BUTTON0 (1 << BUTTON0_pin)
#define BUTTON0_IDR  BUTTON0_GPIO->IDR

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* IO_PINS_CONFIG_H_ */
