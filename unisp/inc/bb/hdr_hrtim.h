/** \file hdr_hrtim.h
 * \brief Header with definition of bits in HRTIM control registers

 */

/******************************************************************************
* chip: STM32F334x8
* compiler: arm-none-eabi-gcc
*
******************************************************************************/

#ifndef HDR_HRTIM_H_
#define HDR_HRTIM_H_

#include "unisp/inc/bb/hdr_bitband.h"

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/


#define HRTIM_TIMCR_CK_PSC_bit 0

#define HRTIM_CHPR_CARFRQ_bit 0
#define HRTIM_CHPR_CARDTY_bit 4
#define HRTIM_CHPR_STRPW_bit 7

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* HDR_HRTIM_H_ */
