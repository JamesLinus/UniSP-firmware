/**
 * @file ui_cmd.h
 * @brief
 * @author raiden00
 */

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifndef UI_CMD_H_
#define UI_CMD_H_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdint.h>
#include "unisp/inc/smps/smps.h"
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

/**
 *@brief UI master command data
 **/
struct UI_cmd{

    char rw; //1
    char sep1;
    char reg[UI_CMD_REG_LEN]; //2
    char sep2;
    char param[UI_CMD_PARAM_LEN]; //3
    char sep3;
    char mantisa[UI_CMD_MANTISA_LEN]; //4
    char sep4;
    char exp[UI_CMD_EXP_LEN]; //5
    char sep5;
    uint8_t crc; //6

};

/**
 *@brief UI master command frame
 **/
struct UI_cmd_frame{

    char start;
    char sep0;
    struct UI_cmd cmd;
    char sep6;
    char end;

};

/**
 *@brief UI slave response data
 **/
struct UI_resp{

    char mantysa[UI_CMD_MANTISA_LEN];
    char sep1;
    char exp[UI_CMD_EXP_LEN];
    char sep2;
    uint8_t crc;

};

/**
 *@brief UI slave response frame
 **/
struct UI_resp_frame{

    char start;
    char sep0;
    struct UI_resp resp;
    char sep3;
    char end;

};

/**
 *@brief UI ack/nack data with optional fault id
 **/
struct UI_ack{

    char ack;
    char sep1;
    char id[UI_CMD_ACK_ID_LEN];

};

/**
 *@brief UI ack/nack frame
 **/
struct UI_ack_frame{

    char start;
    char sep0;
    struct UI_ack ack;
    char sep2;
    char end;

};

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

/******************************************************************************
 * END OF FILE
 ******************************************************************************/

#endif /* UI_SLAVE_STRUCT_H_ */
