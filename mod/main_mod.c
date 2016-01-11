/**
 * @file main_mod.c
 * @brief
 * @author raiden00
 * @date 2015-10-08
 **/

/********************************************************************
 * project: UniSP
 * chip: STM32F334X8
 * compiler: arm-none-eabi-gcc
 *
 ********************************************************************/

#ifdef OUT_MODULE_MAIN_
#warning "Compile main_mod.c"

/*
  +===================================================================+
  | includes
  +===================================================================+
*/

#include "mod/main_mod.h"

/*
  +=============================================================================+
  | local functions' declarations
  +=============================================================================+
*/

static void system_init(void);
static void NVIC_init(void);

/*
  +===================================================================+
  | global variables
  +===================================================================+
*/

volatile struct Button_buffer gButton_buff; //!< global button_buff
volatile struct UI_slave_status gUi_stat; //!< ui status @TODO wywalic do ui

int main(void){

    system_init(); //!< system initialize, hal, etc

    smps_struct_init(&gSmps_stat, &gSmps_sets, &gSmps_adc_val); //!<
    ui_struct_init(&gUi_stat); //!<

    smps_disable(&gSmps_stat); //!<
    smps_settings_struct_reset(&gSmps_sets); //!<
//    smps_inrush_protection_off(); //!< obsolete
//    smps_const_current_mode(); //!< @TODO
//    smps_const_voltage_mode(); //!< @TODO

/////// temporary sets for debug purpose
    /// ustalic jakies defaultowe limity na init i walnac w smps_init
    smps_write_overload_current(&gSmps_sets, SMPS_PRIM_CURRENT_MAX_F32 * SMPS_OVERLOAD_COEFF_F32); // for hardware limit
    smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 35.0);

    smps_init(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
    smps_enable(&gSmps_stat);
    smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
    smps_set_fan_duty(0.9);

    uint8_t uc_state = 1;

/// Ui CODE \/
 /*     SPI1->CR2 |= SPI_CR2_RXNEIE; //!< Rx buffer not empty interrupt enable */
/*     SPI_enable(SPI1); */

    while(1){

        if(gButton_buff.button0){
            switch(uc_state){
            case 1:
//                smps_bridge_pwm_set_duty(0.1); //!<
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 40.0);
                LED3_ODR &=~ LED3;
                break;
            case 2:
//                smps_bridge_pwm_set_duty(0.2); //!<
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 50.0);
                break;
            case 3:
//                smps_bridge_pwm_set_duty(0.3); //!<
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 60.0);
                break;
            case 4:
//                smps_bridge_pwm_set_duty(0.4); //!<
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 70.0);
                break;
            case 5:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 80.0);
              break;
            case 6:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 90.0);
                break;
            case 7:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 100.0);
                break;
            case 8:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 110.0);
                break;
            case 9:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 112.0);
                break;
            case 10:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 115.0);
                break;
            case 11:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 117.0);
                break;
            case 12:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 120.0);
                break;
            case 13:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 125.0);
                break;
            case 14:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 130.0);
                break;
            case 15:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 135.0);
                break;
            case 16:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 140.0);
                break;
            case 17:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 145.0);
                break;
            default:
                smps_set_out_voltage(&gSmps_sets, &gSmps_stat, 150.0);
                uc_state = 0;
                LED3_ODR |= LED3;
                break;
            }

            uc_state+=1;
            reset_button_buff(&gButton_buff, 255);

        }

        if(gSmps_stat.overcurrent){

            smps_overload_routine(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);

        }

        smps_temp_regulator(gSmps_adc_val); //!< temperature control


#define _TODO 1
#ifndef _TODO
        if(gUi_stat.ui_call){

            //if ui_call send ACK
            /* SPI_sendString(SPI1, UI_ACK); */
            /* SPI_enable(SPI1); */

            //stop edm and smps actions
            smps_stop(&gSmps_stat, &gSmps_pid_reg);

            while(gUi_stat.ui_call){

                ui_cmd_buffer = ui_readCommand(ui_cmd_buffer); //!< read cmd from UI inerface as str
                ui_handler(&ui_cmd_temp, ui_cmd_buffer); //!<

            }

            //after ui call - enable RXNEIE
            /* SPI1->CR2 |= SPI_CR2_RXNEIE;//Rx buffer not empty interrupt enable */
            /* SPI_enable(SPI1); */

        }

        /* if(gSmps_stat.enable){ */
        /* smps_assert(); */
        /*     smps_init_and_loop(); */
        /* } */
#endif


    }

    while(1);

}//end of main()

/*
  +===================================================================+
  | local functions
  +===================================================================+
*/

/**
 * @brief
 * @details
 **/
static void NVIC_init(void){

    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP);

}

/**
 * @brief System initialization.
 * @details Call some functions.
 **/
static void system_init(void){

    pll_start(CRYSTAL, FREQUENCY);//!<
    fpu_enable();
    NVIC_init();
//  systick_init(8000000ul); //!<
    gpio_init();
    gpio_pin_cfg_init();
    hrtim_init(); //!<
    timer6_wait_ms_init();
    timer3_pwm_fan_init();
    timer7_debouncing_init();
    timer17_debug_time_ns_init();
//    SPI1_init();
    dma_init(); //!<
    dac1_init(); //!<
//    dac2_init(); //!<
    comp2_init(); //!< -DAC1_CH2, +PA7, SMPS overload protection
//    comp4_init(); //!<
//    comp6_init(); //!<
    adc1_init(); //!<
//    adc2_init(); //!<
}


/**
 * @brief
 * @details
 **/
inline void smps_overload_routine(const struct SMPS_settings smps_sets,
                                  volatile struct SMPS_status* smps_stat,
                                  volatile struct SMPS_PID_reg* smps_pid_reg){

    smps_overload_reset(smps_stat);
    timer6_wait_ms(400); //!< wait @TODO: define in config
    smps_start(smps_sets, smps_stat, smps_pid_reg); //!< re-enable converter
    timer6_wait_ms(200); //!< wait @TODO: define in config
    if(smps_stat->overcurrent){ //!< if overcurrent still exist
        SMPS_OVERLOAD_LED_ON; //!<
        DISABLE_ALL_PWR_OUT;
        while(1); //!< hard reset needed. Check what is wrong.
    }
}

/**
 * @brief
 * @details
 **/
void disable_all_pwr_out(volatile struct SMPS_status* smps_stat,
                         volatile struct SMPS_PID_reg* smps_pid_reg){

    smps_stop(smps_stat, smps_pid_reg);
    smps_disable(smps_stat);

}

/*******************************************************************
 * END OF FILE
 ********************************************************************/
#endif /* OUT_MODULE_MAIN_ */
