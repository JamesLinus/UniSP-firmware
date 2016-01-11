/**
 * @file adc.c
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
#include "unisp/inc/hal/adc.h"

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

/** from inc/hal/adc.h **/
volatile uint16_t gADC1_CH6 = 0;
volatile uint16_t gADC1_CH8 = 0;
volatile uint16_t gADC1_CH12 = 0;
volatile uint16_t gADC1_CH16 = 0;
volatile uint16_t gADC1_REG[ADC_1_REG_SEQ_LEN] = {0, 0}; //{ aux_temp, uc_temp}

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
 * @addtogroup adc
 * @{
 */

/**
 * @brief Initialize ADC1
 * @details Details in doc/uc.md
 **/
void adc1_init(void){

    uint32_t jsqr_tmp = 0;

    //clock cfg
    //ADC12 use AHB clock, no prescaler,
    RCC->AHBENR |= RCC_AHBENR_ADC12EN; //!< enable ADC12 clock
    ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE_0; //!< synch clock mode, HCLK/1

    //calibration
    /* ADC1->CR |= ADC_CR_ADCAL; // run calibration */
    /* while(ADC1->CR & ADC_CR_ADCAL); // wait until done */

    //triggers
    ADC1->CFGR |= ADC_CFGR_EXTEN_0; //!< regular channel hardware trigger detection on the rising edge
    ADC1->CFGR |= ADC_CFGR_EXTSEL_0 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_2; //!< regular channel external trigger on event 7 (TRIGGER1)
    jsqr_tmp += ADC_JSQR_JEXTEN_0; //!< injected channel hardware trigger detection on the rising edge
    jsqr_tmp += ADC_JSQR_JEXTSEL_0 | ADC_JSQR_JEXTSEL_3; //!< injected channel external trigger on event 9 (TRIGGER2)

    //resolution
    ADC1->CFGR |= ADC_CFGR_RES_0; //!< 10 bit resolution

    //dma1 - channel1
    DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; //!< 16-bits memory size
    DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0; //!< 16-bits peripheral size
    DMA1_Channel1->CCR |= DMA_CCR_MINC; //!< memory increment mode ???
    DMA1_Channel1->CCR |= DMA_CCR_CIRC; //!< circular mode ??
    DMA1_Channel1->CCR |= DMA_CCR_TCIE; //!< transfer complete interrupt enable
    DMA1_Channel1->CNDTR = 2; //!< 2 data to transfer
    DMA1_Channel1->CPAR = (uint32_t) &(ADC1->DR); //!< channel 1 peripheral adress ADC1->DR
    DMA1_Channel1->CMAR = (uint32_t) gADC1_REG; //!< channel 1 memory adress
    DMA1_Channel1->CCR |= DMA_CCR_EN; //!< dma channel 1 enable
    ADC1->CFGR |= ADC_CFGR_DMACFG; //!< DMA circular mode ???
    ADC1->CFGR |= ADC_CFGR_DMAEN; //!< DMA enable

    //ADC regular sequence
    ADC1->SQR1 |= ADC_SQR1_L_0; //!< regular channel 2 converstion
//    ADC1->SQR1 |= ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_1; //!< 1sr conversion - 6ch
    ADC1->SQR1 |= ADC_SQR1_SQ1_3 | ADC_SQR1_SQ1_2;//!< 1st conversion - 12ch
    ADC1->SQR1 |= ADC_SQR1_SQ2_4;  //!< 2nd conversion - 16ch

    //ADC injected sequence
    jsqr_tmp += ADC_JSQR_JL_0;  //!< injected channel 2 conversions
    jsqr_tmp += ADC_JSQR_JSQ1_3;  //!< 1st conversion - 8
    jsqr_tmp += ADC_JSQR_JSQ2_2 | ADC_JSQR_JSQ2_1;  //!< 2nd conversion - 6

    ADC1->JSQR = jsqr_tmp; //!< write jsqr_tmp to JSQR

    //ADC sample time
//    ADC1->SMPR1 |= ADC_SMPR1_SMP6_0; //!< channel 6 sample time 2.5 ADC cycles
//    ADC1->SMPR1 |= ADC_SMPR1_SMP6_2; //!< channel 6 sample time 18.5 ADC cycles
    ADC1->SMPR1 |= ADC_SMPR1_SMP6_2 | ADC_SMPR1_SMP6_0; //!< channel 6 sample time 91.5 ADC cycles
    ADC1->SMPR1 |= ADC_SMPR1_SMP8_0; //!< channel 8 sample time 2.5 ADC cycles
    ADC1->SMPR2 |= ADC_SMPR2_SMP12_1 | ADC_SMPR2_SMP12_2; //!< channel 12 sample time 181.5 ADC cycles
    ADC1->SMPR2 |= ADC_SMPR2_SMP16_1 | ADC_SMPR2_SMP16_2; //!< channel 16 sample time 181.5 ADC cycles

    ADC1_2_COMMON->CCR |= ADC12_CCR_TSEN; //!< temperature sensor enable

    //interrupts
    ADC1->IER |= ADC_IER_JEOS; //!< end of injected sequence interrupt enable
    NVIC_EnableIRQ(ADC1_2_IRQn); //!< enable ADC1 interrupt
    NVIC_EnableIRQ(DMA1_Channel1_IRQn); //!< enable DMA ch1 interrupt
    NVIC_SetPriority(ADC1_2_IRQn, ADC1_2_IRQ_PRIORITY);
    NVIC_SetPriority(DMA1_Channel1_IRQn, DMA1_Channel1_IRQ_PRIORITY);

    ADC1->CR |= ADC_CR_ADEN; //!< enable ADC1
    while(ADC1->ISR & ADC_ISR_ADRD); //!< until ADC1 ready

}

/**
 * @brief ADC1 regular conversion start
 * @details
 **/
void adc1_reg_start(void){

    ADC1->CR |= ADC_CR_ADSTART; //!<

}

/**
 * @brief ADC1 injected converstion start
 * @details
 **/
void adc1_inj_start(void){

    ADC1->CR |= ADC_CR_JADSTART; //!<

}

/**
 * @brief ADC1 regular conversion stop
 * @details
 **/
void adc1_reg_stop(void){

    ADC1->CR |= ADC_CR_ADSTP; //!<
    while(ADC1->CR & ADC_CR_ADSTP);

}

/**
 * @brief ADC1 injected conversion stop
 * @details
 **/
void adc1_inj_stop(void){

    ADC1->CR |= ADC_CR_JADSTP; //!<
    while(ADC1->CR & ADC_CR_JADSTP);

}

/**
 * @} end of adc group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
