/**
 * @file ui_common.c
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "unisp/inc/hal/spi.h"
#include "unisp/inc/ui_slave/ui_common.h"
#include "unisp/inc/ui_slave/ui_hal.h"
#include "unisp/inc/misc.h"
#include "unisp/conf/io_pins_config.h"
#include "unisp/conf/ui_config.h"

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
 * @addtogroup ui_common
 * @{
 **/

/**
 * @brief
 * @details @todo calosc
 **/
void ui_sendCommand(char* type, char* param){

    char cmd[UI_CMD_BUFFER_MAX];
    memset(cmd, 0, UI_CMD_BUFFER_MAX * (sizeof cmd[0]));

    strcat(cmd, UI_FRAME_START);
    strcat(cmd, UI_FRAME_SEPARATOR);
    strcat(cmd, type);
    strcat(cmd, UI_FRAME_SEPARATOR);
    strcat(cmd, param);
    strcat(cmd, UI_FRAME_END);

    ui_s_string(cmd);

}

/**
 * @brief
 * @details Skip zeros at begining
 **/
char* ui_readString(char* buffer){

    volatile uint8_t i = 0;

    do{
        ui_r_string(buffer);
        i+=1;
    }while(buffer[0] == '\0');

    return buffer;

}

/**
 * @brief
 * @details return ui cmd without start frame and end frame markers
 * @return
 * @todo obsluga interfejsu, czytanie z niego
 **/
char* ui_readCommand(char* buff){

    //char temp[UI_CMD_BUFFER_MAX];
    char i = 0;
    char* ptmp;

    do{
//    ui_r_string(temp);
        SPI_readString(UI_INTERFACE, buff);
        i+=1;
    } while(buff[0] != UI_FRAME_START[0] && i < 5 );

    //strcpy(buff, "S:W:EDM:EV:15:1:C:E");

    buff[strlen(buff) - 2] = '\0';   // ommit ":E"
    ptmp = &buff[2];// ommit "S:"
    strcpy(buff, ptmp);

    return buff;

}

/**
 * @} end of ui_common group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
