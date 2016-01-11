/**
 * @file main.h
 * @brief Headers for main.c file
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * project: UniSP
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

#ifdef OUT_MODULE_MAIN_

/*
  +=============================================================================+
  | includes
  +=============================================================================+
*/

#include <stdlib.h>
#include <stdint.h>
#include <arm_math.h>
#include <stm32f334x8.h>
#include "unisp/inc/gpio_pin_cfg.h"
#include "unisp/inc/misc.h"
#include "unisp/inc/hal/gpio.h"
#include "unisp/inc/hal/hrtim.h"
#include "unisp/inc/hal/timer.h"
#include "unisp/inc/hal/spi.h"
#include "unisp/inc/hal/dma.h"
#include "unisp/inc/hal/adc.h"
#include "unisp/inc/hal/comp.h"
#include "unisp/inc/hal/systick.h"
#include "unisp/inc/hal/wachdog.h"
#include "unisp/inc/system.h"
#include "unisp/inc/smps/smps.h"
#include "unisp/inc/ui_slave/ui_common.h"
#include "unisp/inc/ui_slave/ui_slave.h"
#include "unisp/inc/ui_slave/ui_slave_struct.h"
#include "unisp/conf/mcu_config.h"
#include "unisp/conf/io_pins_config.h"
#include "unisp/conf/smps_config.h"
#include "unisp/conf/ui_config.h"

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

#define DISABLE_ALL_PWR_OUT disable_all_pwr_out(&gSmps_stat, &gSmps_pid_reg)

/*
+=============================================================================+
| global functions' declarations
+=============================================================================+
*/

void disable_all_pwr_out(volatile struct SMPS_status* smps_stat, volatile struct SMPS_PID_reg* smps_pid_reg);
inline void smps_overload_routine(const struct SMPS_settings smps_sets, volatile struct SMPS_status* smps_stat, volatile struct SMPS_PID_reg* smps_pid_reg);

/*
  +=============================================================================+
  | global variables
  +=============================================================================+
*/

extern volatile struct UI_slave_status gUi_stat; //!< ui status
extern volatile struct Button_buffer gButton_buff; //!< global button_buff


/******************************************************************************
 * END OF FILE
 ******************************************************************************/
#endif /* OUT_MODULE_MAIN_ */
