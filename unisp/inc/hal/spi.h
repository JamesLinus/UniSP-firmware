/**
 * @file spi.h
 * @brief Header for spi.c
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 *****************************************************************************/

#ifndef SPI_H_
#define SPI_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include <stm32f334x8.h>

/*
  +=============================================================================+
  | global functions' declarations
  +=============================================================================+
*/

void SPI1_hd_init(void);
void SPI1_init(void);
inline void SPI_disable(SPI_TypeDef* SPIx);
inline void SPI_enable(SPI_TypeDef* SPIx);
void SPI_data_send(SPI_TypeDef* SPIx, uint16_t data);
uint16_t SPI_data_read(SPI_TypeDef* SPIx);
inline void SPI_out_enable(SPI_TypeDef* SPIx);
inline void SPI_out_disable(SPI_TypeDef* SPIx);
void SPI_buffer_send(SPI_TypeDef* SPIx, uint16_t* buffer, uint8_t length);
uint16_t* SPI_buffer_read(SPI_TypeDef* SPIx, uint16_t* buffer, uint8_t length);
void SPI_line_send(SPI_TypeDef* SPIx, char* buffer);
void SPI_string_send(SPI_TypeDef* SPIx, char* buffer);
char* SPI_line_read(SPI_TypeDef* SPIx, char* buffer);
char* SPI_string_read(SPI_TypeDef* SPIx, char* buffer);

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* SPI_H_ */
