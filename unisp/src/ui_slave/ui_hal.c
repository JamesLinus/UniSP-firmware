/**
 * @file ui_hal.c
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
#include <string.h>
#include "unisp/inc/ui_slave/ui_hal.h"
#include "unisp/inc/ui_slave/ui_slave_struct.h"
#include "unisp/inc/hal/spi.h"
#include "unisp/conf/ui_config.h"

/*
  +=============================================================================+
  | local definitions
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global definitions
  +=============================================================================+
*/

/*
  +=============================================================================+
  | module variables
  +=============================================================================+
*/

/*
  +=============================================================================+
  | global variables
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
 * @addtogroup ui_hal
 * @{
 **/

/**
 * @brief
 * @details @todo calosc
 **/


/**
 * @brief
 * @details @todo calosc
 **/
void ui_string_send(char* buffer){

    SPI_string_send(UI_INTERFACE, buffer);

}

/**
 * @brief
 * @details @todo calosc
 **/
void ui_char_send(char ch){

    SPI_data_send(UI_INTERFACE, (uint16_t)ch);

}

/**
 * @brief
 * @details @todo calosc
 **/
void ui_uint8_send(uint8_t d){

    SPI_data_send(UI_INTERFACE, (uint16_t)d);

}

/**
 * @brief
 * @details @todo calosc
 **/
char* ui_string_read(char* buffer){

    SPI_string_read(UI_INTERFACE, buffer);

    return buffer;

}

/**
 * @brief
 * @details @todo calosc
 **/
char ui_char_read(void){

    return SPI_data_read(UI_INTERFACE);

}

/**
 * @brief
 * @details @todo calosc
 **/
uint8_t ui_uint8_read(void){


}

/**
 * @} end of ui_hal group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
