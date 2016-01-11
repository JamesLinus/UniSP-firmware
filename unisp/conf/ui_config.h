/**
 * @file ui_config.h
 * @brief not finished yet
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
* project: UniSP
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc
*
******************************************************************************/

#ifndef UI_CONFIG_H_
#define UI_CONFIG_H_


/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

#define UI_INTERFACE SPI1
#define UI_CMD_BUFFER_MAX 36
#define UI_DATA_BUFFER_MAX 64 //nie wiem czy bede uzywal tego
#define UI_CMD_START_LEN 1
#define UI_CMD_RW_LEN 1
#define UI_CMD_CRC_LEN 1
#define UI_CMD_END_LEN 1
#define UI_CMD_REG_LEN 6
#define UI_CMD_PARAM_LEN 6
#define UI_CMD_MANTISA_LEN 11
#define UI_CMD_EXP_LEN 3
#define UI_CMD_ACK_ID_LEN 3

/*
  +====================================+
  | SPI communication
  +====================================+
*/

//Strings v
#define UI_COMM_INIT "I"
#define UI_ACK "A"
#define UI_NACK "N"
#define UI_FRAME_START "S"
#define UI_FRAME_END "E"
#define UI_FRAME_SEPARATOR ":"
#define UI_READ "R"
#define UI_WRITE "W"
#define UI_REG_SYS "SYS"
#define UI_REG_SMPS "SMPS"
#define UI_SYS_SMPS_ENABLE "SMPSE"
#define UI_SYS_SMPS_HALT "SMPSH"
#define UI_SYS_UI_ABORT "UIA"
#define UI_SYS_SMPS_STATE "SMPSS"
#define UI_SYS_UI_STATE "UIS"
#define UI_SMPS_V "V" // output voltage
#define UI_SMPS_C "C" // max input current

// FRAME FORMAT
// S:{R/W}:{SYS/EDM/SMPS/oth}:{parameters}:{mantysa as str}:{exp as str}:E


/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* UI_CONFIG_H_ */
