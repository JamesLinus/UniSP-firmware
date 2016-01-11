/**
 * @file isr.c
 * @brief
 * @author raiden00
 */

/********************************************************************
 * project: UniSP
 * chip: STM32F334X8
 * compiler: arm-none-eabi-gcc
 *
 ********************************************************************/

/*
  +===================================================================+
  | includes
  +===================================================================+
*/

#ifndef OUT_MODULE_MAIN_
#include "unisp/main.h"
#else
#include "mod/main_mod.h"
#endif /* OUT_MODULE_MAIN_ */

/*
  +===================================================================+
  | ISRs
  +===================================================================+
*/

/**
 *@addtogroup IRQHandlers
 * @{
 */

#ifndef OUT_MODULE_HRTIM_FLT_IRQ_
/**
 * @brief HRTIM1 faults interrupt routine
 * @details Only SMPS overcurrent FAULT
 * @param [in,out] gSmps_stat
 **/
void HRTIM1_FLT_IRQHandler(void){

    if(HRTIM1->sCommonRegs.ISR & HRTIM_ISR_FLT1){ //!< from COMP2, TIMA, SMPS overcurrent
        //set HRTIM1_TIMER_A outputs in FAULT state
        smps_overload(&gSmps_stat, &gSmps_pid_reg);
    }

    HRTIM1->sCommonRegs.ICR = (HRTIM_ICR_FLT1C | HRTIM_ICR_FLT2C | HRTIM_ICR_FLT3C); //!< clear FAULT1, FAULT2, FAULT3
}
#endif /* OUT_MODULE_HRTIM_FLT_IRQ_ */

#ifndef OUT_MODULE_HRTIM_MASTER_IRQ_
/**
 * @brief HRTIM1 MASTER interrupt routine
 * @details SMPS output voltage PI regulator action.
 * @param [in,out] gSmps_adc_val
 * @param [in,out] gSmps_pid_reg
 **/
void HRTIM1_Master_IRQHandler(void){

    // if master update - smps control loop
    if(HRTIM1->sMasterRegs.MISR & HRTIM_MISR_MCMP1){

        if(gSmps_adc_val.out_voltage_cntr == 0){
            gSmps_adc_val.out_voltage_avg_f32 = 0;
        }
        else { //!< cntr is not zero
            gSmps_adc_val.out_voltage_avg_f32 = ((gSmps_adc_val.out_voltage_sum/gSmps_adc_val.out_voltage_cntr) * SMPS_ADC_STEP_F32) * SMPS_OUT_VOLTAGE_TO_VOLTAGE_RATIO_F32 ; //!< calc average value and convert to f32

            gSmps_adc_val.out_voltage_sum = 0; //!< reset sum
            gSmps_adc_val.out_voltage_cntr = 0; //!< reset cntr
//        if(gSmps_adc_val.out_voltage_avg_f32 > gSmps_sets.out_voltage_f32*SMPS_OVERVOLTAGE_COEFF_F32 ) smps_overvoltage(&gSmps_stat);

            //--- voltage regulator ---
            gSmps_pid_reg.voltage_error_f32 = gSmps_pid_reg.voltage_ref_f32 - gSmps_adc_val.out_voltage_avg_f32; //!< calc output voltage error
            if((gSmps_pid_reg.voltage_error_f32 > SMPS_PID_REG_DEADBAND_F32) || (gSmps_pid_reg.voltage_error_f32 < -SMPS_PID_REG_DEADBAND_F32)) { //!< regulator deadband

                gSmps_pid_reg.voltage_pid_out_f32 =  smps_pid_voltage_f32(&(gSmps_pid_reg.voltage_pid), gSmps_pid_reg.voltage_error_f32);
                gSmps_pid_reg.new_duty_f32 = gSmps_pid_reg.voltage_pid_out_f32 / SMPS_PID_VOLTAGE_SCALING_F32;

                //!< @TODO: wrap to single funtion ?
                if(gSmps_pid_reg.new_duty_f32 < SMPS_BRIDGE_DUTY_BURST_ENABLE_F32){ //!< increase burst if low duty
                    smps_burst_increase(&gSmps_stat);
                    smps_bridge_pwm_duty_set(gSmps_pid_reg.new_duty_f32);
                }
                else if(gSmps_stat.burst && (gSmps_pid_reg.new_duty_f32 > SMPS_BRIDGE_DUTY_BURST_DISABLE_F32)) //!< decrease burst if duty increase
                    smps_burst_decrease(&gSmps_stat);
                else smps_bridge_pwm_duty_set(gSmps_pid_reg.new_duty_f32); //!< else - just set new duty
            }
        }

//        gSmps_pid_reg.current_ref_f32 =  arm_pid_f32(&(gSmps_pid_reg.voltage_pid), voltage_error); //!< I_REF = PID(V_ERR)
        //       if(gSmps_pid_reg.current_ref_f32 > SMPS_CURRENT_REG_SATURATION_F32) gSmps_pid_reg.current_ref_f32 = SMPS_CURRENT_REG_SATURATION_F32;
        // ------------------------

        HRTIM1->sMasterRegs.MICR |= HRTIM_MICR_MCMP1; //!< clear master CMP1 interrupt flag
    }

    /* if(HRTIM1->sMasterRegs.MISR & HRTIM_MISR_MREP){ */
    /*     HRTIM1->sMasterRegs.MICR |= HRTIM_MICR_MREP; //!< clear master rep interrupt flag */
    /* } */

}
#endif /* OUT_MODULE_HRTIM_MASTER_IRQ_ */

#ifndef OUT_MODULE_ADC1_2_IRQ_
/**
 * @brief ADC1/2 interrupt.
 * @details Handle ADC1/2 injected sequence.
 * @param [in,out] gSmps_adc_val
 * @param [in,out] ....
 **/
void ADC1_2_IRQHandler(void){

    if(ADC1->ISR & ADC_ISR_JEOS){
        SMPS_ADC_PRIM_CURRENT = ADC1->JDR1; //!< copy ADC 1 JDR1
        SMPS_ADC_OUT_VOLTAGE = ADC1->JDR2; //!< copy ADC 1 JDR2

        gSmps_adc_val.prim_current_f32 = SMPS_ADC_PRIM_CURRENT * SMPS_ADC_STEP_F32 * SMPS_PRIM_CURRENT_TO_VOLTAGE_RATIO_F32; //!<

        gSmps_adc_val.out_voltage_sum += SMPS_ADC_OUT_VOLTAGE; //!< calc average value in regulator MASTER_IRQ
        gSmps_adc_val.out_voltage_cntr += 1;

        //--- current regulator ---
//        float current_error = gSmps_pid_reg.current_ref_f32 - gSmps_adc_val.prim_current_adc_f32;
//        float new_duty = arm_pid_f32(&(gSmps_pid_reg.current_pid), current_error);
        //set new duty
        //-------------------------

        ADC1->ISR |= ADC_ISR_JEOS; //!< clear JEOS flag (by writing 1!)
    }
}
#endif /* OUT_MODULE_ADC1_2_IRQ_ */

#ifndef OUT_MODULE_SYSTICK_IRQ_
/**
 * @brief Not use
 * @details
 **/
void SysTick_Handler(void){

}
#endif /* OUT_MODULE_SYSTICK_IRQ_ */

#ifdef OUT_MODULE_HARDFAULT_IRQ_
/**
 * @brief
 * @details Disable all power outputs.
 * @todo some safety mechanism
 * @todo error flag and feedback about fault
 **/
void HardFault_Handler(void){

    DISABLE_ALL_PWR_OUT;

}
#endif /* OUT_MODULE_HARDFAULT_IRQ_ */

/**
 * @brief SPI1 interrupt routine
 * @details Initialize UI communication and disable RXNE interrupt.
 * @param [in,out] gUi_stat
 **/
void SPI1_IRQHandler(void){

    if(SPI1->SR & SPI_SR_RXNE){
        char tmp = SPI1->DR;
        if((!gUi_stat.ui_call)){
            if(tmp == UI_COMM_INIT[0]){ // only one char
                ui_call(&gUi_stat);
                DISABLE_ALL_PWR_OUT;
                SPI1->CR2 &=~ SPI_CR2_RXNEIE;//Rx buffer not empty interrupt disable
            }
        }
    }
}

/**
 * @brief DMA1 Channel1 interrupt.
 * @details Handle ADC1 regular sequence.
 * @param [in,out] gSmps_adc_val
 **/
void DMA1_Channel1_IRQHandler(void){

    if(DMA1->ISR & DMA_ISR_TCIF1){

        //!< TODO move ADC_STEP multiplication to temp_get function
        gSmps_adc_val.uc_temp_f32 =  smps_uc_temp_get(SMPS_ADC_UC_TEMP * SMPS_ADC_STEP_F32); //!<
        gSmps_adc_val.aux_temp_f32 =  smps_aux_temp_get(SMPS_ADC_AUX_TEMP * SMPS_ADC_STEP_F32); //!<

        DMA1->IFCR |= DMA_IFCR_CTCIF1; //!< clear TCIF1 flag
    }

}

/**
 * @brief TIM6 interrupts handler.
 * @details Simple time delay.
 * Change global flags in smps_flag instance.
 * @param [in,out] gTIM6_UIF
 **/
void TIM6_DAC1_IRQHandler(void){

    extern volatile uint8_t gTIM6_UIF;

    if ( (TIM6->SR & TIM_SR_UIF) && !gTIM6_UIF){
        gTIM6_UIF = 1;
        TIM6->SR &=~ TIM_SR_UIF;
    }
}

/**
 * @brief TIM7 interrupts handler
 * @details TIM7 IRQ uses as button debouncing. Set apropriate bits in<code>BUTTON_buf</code> global variable.
 *
 * <b> Remember: reset BUTTON_buf after use !</b>
 * @param [in,out] gButton_buff struct global
 **/
void TIM7_DAC2_IRQHandler(void){

    if (TIM7->SR & TIM_SR_UIF){
        if(!(BUTTON0_IDR & BUTTON0)){
            gButton_buff.button0 = 1;
        }
        TIM7->SR &=~ TIM_SR_UIF;
    }
}

/**
 *@} end of IRQHandlers group
 */

/*******************************************************************
 * END OF FILE
 ********************************************************************/
