/**
 * @file spi.c
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

#include <stdint.h>
#include <stm32f334x8.h>
#include <core_cmInstr.h>
#include "unisp/inc/hal/spi.h"
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
 * @addtogroup spi
 * @{
 */

/**
 * @brief SPI1 initialization
 * @details SPI1 using in UI communication (salve, half-duplex).
 **/
void SPI1_hd_init(void){

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    __DSB();

    SPI1->CR1 &=~SPI_CR1_SSM; ///SS hardware
    SPI1->CR1 &=~SPI_CR1_MSTR; //slave
    SPI1->CR1 |= SPI_CR1_BIDIMODE; //half- duplex bidirectional
    // default 8-bit data size

    NVIC_EnableIRQ(SPI1_IRQn);
    // NVIC_SetPriority(SPI1_IRQn, SPI1_IRQ_PRIORITY); ///@todo : ustal jak powinno byc??
    SPI1->CR1 &=~SPI_CR1_SPE;//SPI disable

}

/**
 * @brief SPI1 initialization
 * @details SPI1 using in UI communication (salve, full-duplex).
 **/
void SPI1_init(void){

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    __DSB();

    SPI1->CR1 &=~SPI_CR1_SSM; ///SS hardware
    SPI1->CR1 &=~SPI_CR1_MSTR; //slave
    // SPI2->CR2 |= SPI_CR2_TXEIE; //Tx buffer empty interrupt enable
    // SPI2->CR2 |= SPI_CR2_RXNEIE;//Rx buffer not empty interrupt enable
    // default 8-bit data size

    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_SetPriority(SPI1_IRQn, SPI1_IRQ_PRIORITY); ///@todo : ustal jak powinno byc??
    SPI1->CR1 &=~SPI_CR1_SPE;//SPI disable

}

/**
 * @brief Disable SPI and slave
 * @details
 **/
inline void SPI_disable(SPI_TypeDef* SPIx){

    if(SPIx->CR1 & SPI_CR1_SPE){
        if(SPIx->CR1 & SPI_CR1_BIDIMODE){
            if(SPIx->CR1 & SPI_CR1_BIDIOE){
                while(!(SPIx->SR & SPI_SR_TXE) );
                while( (SPIx->SR & SPI_SR_BSY) );
            }
            else{
                if(SPIx->SR & SPI_CR1_MSTR){
                    while(!(SPIx->SR & SPI_SR_RXNE));
                    //tu moze brakowac warunkow. w dok niezrozumiale opisane!
                    asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
                    //while(!(SPIx->SR & SPI_SR_RXNE));
                }
            }
        }
        else{
            while(!(SPIx->SR & SPI_SR_RXNE));
            while(!(SPIx->SR & SPI_SR_TXE) );
            while( (SPIx->SR & SPI_SR_BSY) );
        }

        SPIx->CR1 &=~ SPI_CR1_SPE; //SPI disable
    }

}

/**
 * @brief Enable SPI and slave
 * @details
 **/
inline void SPI_enable(SPI_TypeDef* SPIx){

    if(!(SPIx->CR1 & SPI_CR1_SPE)){
        SPIx->CR1 |= SPI_CR1_SPE; //SPI enable
    }

}

/**
 * @brief
 * @details
 **/
void SPI_data_send(SPI_TypeDef* SPIx, uint16_t data){

    SPIx -> DR = data;
    while(!(SPIx->SR & SPI_SR_TXE) );
    while( (SPIx->SR & SPI_SR_BSY) );

}

/**
 * @brief
 * @details
 **/
uint16_t SPI_data_read(SPI_TypeDef* SPIx){

    while(!(SPIx->SR & SPI_SR_RXNE));
    return SPIx->DR;

}

/**
 * @brief
 * @details
 **/
inline void SPI_out_enable(SPI_TypeDef* SPIx){

    SPI_disable(SPIx);
    SPIx->CR1 |= SPI_CR1_BIDIOE; //output enable

}

/**
 * @brief
 * @details
 **/
inline void SPI_out_disable(SPI_TypeDef* SPIx){

    SPI_disable(SPIx);
    SPIx->CR1 &=~ SPI_CR1_BIDIOE; //output disable

}

/**
 * @brief
 * @details
 **/
void SPI_buffer_send(SPI_TypeDef* SPIx, uint16_t* buffer, uint8_t length){

    uint8_t i = 0;

    for(i=0; i< length; i+=1){
        SPI_data_send(SPIx, buffer[i]);
    }

}

/**
 * @brief
 * @details
 **/
//uint16_t SPI_buffer_read(SPI_TypeDef* SPIx, uint16_t* buffer, uint8_t length){

//}

/**
 * @brief Send string line using SPI_DR
 * @details
 **/
void SPI_line_send(SPI_TypeDef* SPIx, char* buffer){

    uint8_t tmp = 0;

    do{
        SPI_data_send(SPIx, (uint16_t) buffer[tmp]);
        tmp+=1;
    } while(buffer[tmp] != '\n');
    SPI_data_send(SPIx, (uint16_t) '\n');

}

/**
 * @brief Send string using SPI_DR
 * @details
 **/
void SPI_string_send(SPI_TypeDef* SPIx, char* buffer){

    uint8_t tmp = 0;

    do{
        SPI_data_send(SPIx, (uint16_t) buffer[tmp]);
        tmp+=1;
    } while(buffer[tmp] != '\0');
    SPI_data_send(SPIx, (uint16_t) '\0');

}

/**
 * @brief
 * @details
 **/
char* SPI_line_read(SPI_TypeDef* SPIx, char* buffer){

    uint8_t tmp = 0;

    do{
        buffer[tmp] = SPI_data_read(SPIx);
        tmp +=1;
    }while(buffer[tmp-1] != '\n');

    return buffer;

}

/**
 * @brief
 * @details
 **/
char* SPI_string_read(SPI_TypeDef* SPIx, char* buffer){

    //@todo add max string length
    uint8_t tmp = 0;

    do{
        buffer[tmp] = (char)SPI_data_read(SPIx);
        tmp +=1;
    }while(buffer[tmp-1] != '\0');

    return buffer;

}

/**
 * @} end of spi group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
