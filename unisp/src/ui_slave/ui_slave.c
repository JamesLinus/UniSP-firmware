/**
 * @file ui_slave.c
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
#include <math.h>
#include "unisp/inc/ui_slave/ui_slave.h"
#include "unisp/inc/ui_slave/ui_cmd.h"
#include "unisp/conf/ui_config.h"
#include "unisp/main.h"

#define SMPS_CMD_ENABLE_ 1

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

/** from inc/main.h **/
volatile struct SMPS_status gSmps_stat; //!< smps status
volatile struct SMPS_settings gSmps_sets; //!< smps settings
volatile struct UI_slave_status gUi_stat; //!< ui status

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
 * @brief
 * @details
 **/
inline void ui_call(volatile struct UI_slave_status* s){

    s->ui_call = 1;

}

/**
 * @brief
 * @details
 **/
void ui_parse_cmd(struct UI_cmd* scmd, char* cmd){

    char* tok;
    char* run;
    run = strdup(cmd);

    tok = strsep(&run, UI_FRAME_SEPARATOR);
    scmd->rw = tok[0];
    tok = strsep(&run, UI_FRAME_SEPARATOR);
    strcpy(scmd->reg, tok);
    tok = strsep(&run, UI_FRAME_SEPARATOR);
    strcpy(scmd->param, tok);
    tok = strsep(&run, UI_FRAME_SEPARATOR);
    strcpy(scmd->mantisa, tok);
    tok = strsep(&run, UI_FRAME_SEPARATOR);
    strcpy(scmd->exp, tok);
    tok = strsep(&run, UI_FRAME_SEPARATOR);
    scmd->crc = (uint8_t)tok[0];

}

/**
 * @brief Check if string is numeric
 * @details @todo wywalic do innego pliku
 **/
uint8_t is_numeric(const char *p) {

    if (*p) {
        char c;
        while ((c=*p++)) {
            if (!isdigit(c)) return 0;
        }
        return 1;
    }
    return 0;
}

/**
 * @brief
 * @details
 **/
float ui_get_f32_value_from_cmd(char* s_mantisa, char* s_exp){

    float f_tmp = 0.0;
    uint32_t mantisa = 0;
    int8_t exp = 0;

    //!< @todo check if string are numeric
    if((s_mantisa[0] != '\0') && (s_exp[0] != '\0')){

        mantisa = atoi(s_mantisa);

        if(s_exp[0] == '-'){ //!< if negative exp
            exp = atoi(&(s_exp[1]));
            exp = -exp;
        }
        else{
            exp = atoi(s_exp);
        }

        f_tmp = ((float)mantisa * (float) pow(10, (float)exp));
    }

    return f_tmp;
}

/**
 * @brief
 * @details cmd string without start and end markers
 * @return 0 - OK >0 - fault, return fault id
 * @todo uladnic to, pomyslec itp, jak zrobic calos elegancko ? pierw wyodrebnienie komend, pozniej ich wykonianie itp
 **/
uint8_t ui_execute_cmd(struct UI_cmd* scmd, char* cmd){

    ui_parse_cmd(scmd, cmd);

    //!< @TODO: co jeszce uproscic ?
    //!< @TODO: skoczyc reszte

    //!< @TODO: check CRC
    //!< moze na swichach to zrobic? znaczy co sie da na sliczach

    /*
      +=====================================+
      | WRITE to uC
      +=====================================+
    */
    if(scmd->rw == UI_WRITE[0]){

        if(strcmp(scmd->reg, UI_REG_SYS) == 0){ //!< if system register

            if(strcmp(scmd->param, UI_SYS_UI_ABORT) == 0){

                gUi_stat.ui_call = 0;

            }

#ifdef SMPS_CMD_ENABLE_

            else if(strcmp(scmd->param, UI_SYS_SMPS_ENABLE) == 0){

                gSmps_stat.smps_enable = 1;

            }


            else if(strcmp(scmd->param, UI_SYS_SMPS_HALT) == 0){

                gSmps_stat.smps_enable = 0;

            }

#endif

            else {

                return 1; //!< return fault if not knowing system param

            }


        }


#ifdef SMPS_CMD_ENABLE_

        else if(strcmp(scmd->reg, UI_REG_SMPS) == 0){ //!< if SMPS register

            if(strcmp(scmd->param, UI_SMPS_V) == 0){

                gSmps_sets.out_voltage_f32 = ui_get_f32_value_from_cmd(scmd->mantisa, scmd->exp);

            }

            else if(strcmp(scmd->param, UI_SMPS_C) == 0){

                gSmps_sets.max_prim_current_f32 = ui_get_f32_value_from_cmd(scmd->mantisa, scmd->exp);

            }

        }

#endif

        else{

            return 1; //!< return fault if not knowning register

        }

    }


/*
  +=====================================+
  | READ from uC
  +=====================================+
*/
    else if (scmd->rw == UI_READ[0]){

        if(strcmp(scmd->param, UI_SYS_UI_STATE) == 0){

        }

#ifdef SMPS_CMD_ENABLE_

            else if(strcmp(scmd->param, UI_SYS_SMPS_STATE) == 0){

            }

#endif

            else {

                return 1; //!< return fault if not knowing system param

            }


        }


#ifdef SMPS_CMD_ENABLE_

        else if(strcmp(scmd->reg, UI_REG_SMPS) == 0){ //!< if SMPS register

            if(strcmp(scmd->param, UI_SMPS_V) == 0){


            }

            else if(strcmp(scmd->param, UI_SMPS_C) == 0){


            }

        }

#endif

    else{

        return 1; //!< return fault if not knotwning operation

    }

    return 0; // if not fault, return 0

}

/**
 * @brief
 * @details
 **/
void ui_send_ACK(void){


}

/**
 * @brief
 * @details
 **/
void ui_send_NACK(uint8_t fault_id){


}

/**
 * @brief
 * @details
 **/
void ui_handler(struct UI_cmd* scmd, char* cmd){

    uint8_t fault_id = 0;

    fault_id = ui_execute_cmd(scmd, cmd);

    if(fault_id == 0)
        ui_send_ACK();
    else
        ui_send_NACK(fault_id);

}

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
