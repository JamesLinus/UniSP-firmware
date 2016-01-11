/**
 * @file main.c
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

#ifndef OUT_MODULE_MAIN_

/*
  +===================================================================+
  | includes
  +===================================================================+
*/

#include "unisp/main.h"

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

//char** cmd_tab = {"x", "x" };

int main(void){

    uint8_t uc_state = 1;

    system_init(); //!< system initialize, hal, etc

    smps_struct_init(&gSmps_stat, &gSmps_sets, &gSmps_adc_val); //!<
    ui_struct_init(&gUi_stat); //!<

    smps_disable(&gSmps_stat); //!<
    smps_settings_struct_reset(&gSmps_sets, &gSmps_pid_reg); //!<
//    smps_inrush_protection_off(); //!< obsolete
//    smps_const_current_mode(); //!< @TODO
//    smps_const_voltage_mode(); //!< @TODO

    smps_delay_ms(SMPS_INRUSH_DELAY_ms);
    smps_init(&gSmps_sets, &gSmps_stat, &gSmps_pid_reg);

    smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg, 40.0);
    smps_overload_current_write(&gSmps_sets, SMPS_PRIM_CURRENT_MAX_F32 * SMPS_OVERLOAD_COEFF_F32); // for hardware limit

    smps_enable(&gSmps_stat);
    smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg); // wywalic tu i wlaczac dopiero po przycisku ?

    smps_fan_duty_write(&gSmps_sets, 0.9);


/// Ui CODE \/
 /*     SPI1->CR2 |= SPI_CR2_RXNEIE; //!< Rx buffer not empty interrupt enable */
/*     SPI_enable(SPI1); */


    while(1){

        //!< simple output voltage test
        if(gButton_buff.button0){
            switch(uc_state){
            case 1:
//                smps_bridge_pwm_duty_set(0.1); //!<
                smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg,  50.0);
                smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
                break;
            case 2:
                smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg, 80.0);
                smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
                break;
            case 3:
                smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg, 100.0);
                smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
                break;
            default:
                smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg, 120.0);
                smps_start(gSmps_sets, &gSmps_stat, &gSmps_pid_reg);
                uc_state = 0;
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

        while(1){
// infinity loop after reset. Waiting for UI call

        if(gSmps_stat.smps_fault){
            //do som fault exceptions
            smps_disable(&gSmps_stat);
        }


        if(gUi_stat.ui_call){
            smps_stop(&gSmps_stat, &gSmps_pid_reg);

            //if ui_call send ACK
            /* SPI_sendString(SPI1, UI_ACK); */
           /* SPI_enable(SPI1); */

            //do some UI shits
            //UI_interface();

            while(gUi_stat.ui_call){

                ui_cmd_buffer = ui_readCommand(ui_cmd_buffer); //!< read cmd from UI inerface as str
                ui_handler(&ui_cmd_temp, ui_cmd_buffer); //!<
            }

            //after ui call - enable RXNEIE
            /* SPI1->CR2 |= SPI_CR2_RXNEIE;//Rx buffer not empty interrupt enable */
            /* SPI_enable(SPI1); */
            gUi_stat.ui_call = 0;
        }

        /* if(gSmps_stat.smps_enable){ */
        /* smps_assert(); */

        /*     smps_init_and_loop(gSmps_sets); */

        /* } */

    }

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
 * @brief SMPS overload routine
 * @details
 **/
inline void smps_overload_routine(const struct SMPS_settings smps_sets,
                                  volatile struct SMPS_status* smps_stat,
                                  volatile struct SMPS_PID_reg* smps_pid_reg){

    /* smps_overload_reset(smps_stat); //!< reset smps overload flag */
    /* timer6_wait_ms(SMPS_OVERLOAD_RESTART_DELAY_ms); //!< wait @TODO: define in config */
    /* smps_out_voltage_write(&gSmps_sets, gSmps_pid_reg, SMPS_OVERLOAD_RESTART_VOLTAGE_F32); */
    /* smps_start(smps_sets, smps_stat, smps_pid_reg); //!< re-enable converter */
    /* timer6_wait_ms(SMPS_OVERLOAD_RESTART_DELAY_ms); //!< wait @TODO: define in config */
    /* if(smps_stat->overcurrent){ //!< if overcurrent still exist */
    /*     SMPS_OVERLOAD_LED_ON; //!< */
    /*     DISABLE_ALL_PWR_OUT; */
    /*     while(1); //!< hard reset needed. Check what is wrong. */
    /* } */
}

/**
 * @brief Disable all power outputs
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
