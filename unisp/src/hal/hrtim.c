/**
 * @file hrtim.c
 * @brief HRTIM driver
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
#include <stm32f334x8.h>
#include "unisp/inc/hal/hrtim.h"
#include "unisp/inc/gpio_pin_cfg.h"
#include "unisp/inc/bb/hdr_hrtim.h"
#include "unisp/conf/mcu_config.h"
#include "unisp/conf/smps_config.h"

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

static void hrtim_MASTER_init(void);
static void hrtim_TIMER_A_init(void); //!< SMPS POWER BRIDGE PWM
/* static void hrtim_TIMER_B_init(void); //!< SMPS SYNCH RECT */
/* static void hrtim_TIMER_C_init(void); //!< SMPS SYNCH RECT*/
static void hrtim_adc_trg_cfg(void);
static void hrtim_fault_cfg(void);
static void hrtim_burst_mode_cfg(void);

/**
 * @addtogroup hrtim
 * @{
 **/

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @brief Update HRTIM MASTER PER
 * @details
 **/
void hrtim_MASTER_per_update(uint16_t period){

    HRTIM1->sMasterRegs.MPER = period;

}

/**
 * @brief Get HRTIM MASTER PER
 * @details
 **/
uint16_t hrtim_MASTER_per_get(void){

    return HRTIM1->sMasterRegs.MPER;

}

/**
 * @brief Update HRTIM MASTER REP (repetition register)
 * @details
 **/
void hrtim_MASTER_rep_update(uint16_t repetition){

    HRTIM1->sMasterRegs.MREP = repetition;

}

/**
 * @brief Update HRTIM MASTER CMP1
 * @details
 **/
void hrtim_MASTER_cmp1_update(uint16_t compare1){

    HRTIM1->sMasterRegs.MCMP1R = compare1;

}

/**
 * @brief  Update HRTIM MASTER CMP1
 * @details
 **/
void hrtim_MASTER_cmp2_update(uint16_t compare2){

    HRTIM1->sMasterRegs.MCMP2R = compare2;

}

/**
 * @brief Update HRTIM TIMERA CMP1
 * @details change also CMP2 @TODO: divide into 2 funciton
 **/
void hrtim_TIMER_A_cmp1_update(uint16_t compare1){

    uint16_t compare2 = compare1 - HRTIM_TIMER_A_ADC_TRIGGER_OFFSET; //!< triger to ADC
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].CMP1xR = compare1;
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].CMP2xR = compare2;

}

/**
 * @brief Update HRTIM TIMERA PER
 * @details
 **/
void hrtim_TIMER_A_per_update(uint16_t period){

    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].PERxR = period;

}

/**
 * @brief Disable HRTIM TIMER A outputs (IDLE state)
 * @details
 **/
void hrtim_TIMER_A_out_disable(void){

    HRTIM1->sCommonRegs.ODISR |= HRTIM_ODISR_TA1ODIS;
    HRTIM1->sCommonRegs.ODISR |= HRTIM_ODISR_TA2ODIS;

}

/**
 * @brief Enable HRTIM TIMER A outputs (RUN state)
 * @details
 **/
void hrtim_TIMER_A_out_enable(void){

    HRTIM1->sCommonRegs.OENR |= HRTIM_OENR_TA1OEN;
    HRTIM1->sCommonRegs.OENR |= HRTIM_OENR_TA2OEN;

}

/**
 * @brief Enable HRTIM FAULT1
 * @details
 **/
void hrtim_flt1_enable(void){

    HRTIM1->sCommonRegs.FLTINR1 |= HRTIM_FLTINR1_FLT1E; //!< enable FAULT1
    HRTIM1->sCommonRegs.FLTINR1 |= HRTIM_FLTINR1_FLT1LCK; //!< lock FAULT1

}


/**
 * @brief Start burst mode action
 * @details
 **/
inline void hrtim_burst_mode_start(void){

    HRTIM1->sCommonRegs.BMTRGR |= HRTIM_BMTRGR_SW;
}

/**
 * @brief Stop burst mode action
 * @details
 **/
inline void hrtim_burst_mode_stop(void){

    HRTIM1->sCommonRegs.BMCR &=~ HRTIM_BMCR_BMSTAT;
}

/**
 * @brief Update HRTIM burst mode CMP
 * @details
 **/
inline void hrtim_burst_mode_cmp_update(uint16_t cmp){

    /* if(cmp > HRTIM_BURST_MODE_CMP_MAX) cmp = HRTIM_BURST_MODE_CMP_MAX; */
    /* else if(cmp < HRTIM_BURST_MODE_CMP_MIN) cmp = HRTIM_BURST_MODE_CMP_MIN; */
    HRTIM1->sCommonRegs.BMCMPR = cmp;
}

/**
 * @brief Update HRTIM burst mode PER
 * @details After PER update it is necessary to re-write CMP!
 **/
inline void hrtim_burst_mode_per_update(uint16_t per){

    /* if(per > HRTIM_BURST_MODE_PER_MAX) per = HRTIM_BURST_MODE_PER_MAX; */
    /* else if(per < HRTIM_BURST_MODE_PER_MIN) per = HRTIM_BURST_MODE_PER_MIN; */
    HRTIM1->sCommonRegs.BMPER = per;
}

/**
 * @brief Get HRTIM burst mode PER
 * @details
 **/
inline uint16_t hrtim_burst_mode_per_get(void){

    return HRTIM1->sCommonRegs.BMPER;
}

/**
 * @brief Get HRTIM burst mode CMP
 * @details
 **/
inline uint16_t hrtim_burst_mode_cmp_get(void){

    return HRTIM1->sCommonRegs.BMCMPR;
}

/**
 * @brief Init HRTIM
 * @details
 **/
void hrtim_init(void){

    RCC->CFGR3 |= RCC_CFGR3_HRTIMSW; //!< clock from pll
    RCC->APB2ENR |= RCC_APB2ENR_HRTIM1EN; //!< HRTIM clock enable

    gpio_hrtim_in_cfg_init(); //before hrtim out, before hrtim reg

// DLL initialization
//    HRTIM1->sMasterRegs.DLLCR |= HRTIM_DLLCR_CALRTE_0 | HRTIM_DLLCR_CALRTE_1; //14us calibration
//    HRTIM1->sMasterRegs.DLLCR |= HRTIM_DLLCR_CALEN; //periodic calibration enable
    HRTIM1->sCommonRegs.DLLCR |= HRTIM_DLLCR_CAL; //!< single-shot calibration start
    while(!(HRTIM1->sCommonRegs.ISR & HRTIM_ISR_DLLRDY)); //!< wait until DLL calibration done

    hrtim_adc_trg_cfg();
    hrtim_fault_cfg();
    hrtim_burst_mode_cfg();

    hrtim_MASTER_init(); //!< MASTER - SMPS VOLTAGE AND CURRENT CONTROL LOOP
    hrtim_TIMER_A_init(); //!< TIMER_A - SMPS PWM
//    hrtim_TIMER_B_init(); //!<
//    hrtim_TIMER_C_init(); //!<
#ifdef OUT_MODULE_HRTIM_TIMER_D_USE_
    hrtim_TIMER_D_init(); //!<
#endif
#ifdef OUT_MODULE_HRTIM_TIMER_E_USE_
    hrtim_TIMER_E_init(); //!<
#endif

    uint32_t tmp = 0;
    tmp |= HRTIM_MCR_MCEN; //master counter eneable
    tmp |= HRTIM_MCR_TACEN; //!< TIMER_A counter enable
//    tmp |= HRTIM_MCR_TBCEN; //!< TIMER_B counter enable
//    tmp |= HRTIM_MCR_TCCEN; //!< TIMER_C counter enable
#ifdef OUT_MODULE_HRTIM_TIMER_D_USE_
    tmp |= HRTIM_MCR_TDCEN; //!< TIMER_D counter enable
#endif
#ifdef OUT_MODULE_HRTIM_TIMER_E_USE_
    tmp |= HRTIM_MCR_TECEN; //!< TIMER_E counter enable
#endif
    HRTIM1->sMasterRegs.MCR |= tmp; //!< enable at once

    gpio_hrtim_out_cfg_init(); // after hrtim in, once the counters are enabled

}

/**
 * @brief Enable HRTIM MASTER CMP1 interrupt
 * @details
 **/
void hrtim_MASTER_cmp1_irq_enable(void){

    HRTIM1->sMasterRegs.MDIER |= HRTIM_MDIER_MCMP1IE; //master compare1 interrupt enable

}

/**
 * @brief Disable HRTIM MASTER CMP1 interrupt
 * @details
 **/
void hrtim_MASTER_cmp1_irq_disable(void){

    HRTIM1->sMasterRegs.MDIER &=~ HRTIM_MDIER_MCMP1IE; //master compare1 interrupt disable

}

/*
  +=============================================================================+
  | local functions
  +=============================================================================+
*/

/**
 * @brief Init HRTIM MASTER
 * @details
 **/
static void hrtim_MASTER_init(void){

    HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_CONT; // continuous mode
    HRTIM1->sMasterRegs.MCR |= (HRTIM_MCR_CK_PSC <<  HRTIM_TIMCR_CK_PSC_bit); //prescaler
//    HRTIM1->sMasterRegs.MDIER |= HRTIM_MDIER_MUPDIE; //master period interrupt enable
//    HRTIM1->sMasterRegs.MDIER |= HRTIM_MDIER_MCMP1IE; //master compare1 interrupt enable
//    HRTIM1->sMasterRegs.MDIER |= HRTIM_MDIER_MREPIE; //master repetition interrupt enable
//    HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_MREPU; // master timer repetition update

    NVIC_EnableIRQ(HRTIM1_Master_IRQn);
    NVIC_SetPriority(HRTIM1_Master_IRQn, HRTIM1_Master_IRQ_PRIORITY);
}

/**
 * @brief Init HRTIM TIMER A
 * @details Configure HRTIM TIMER A as complementary push-pull PWM (50% duty). Outputs disable after init.
 **/
static void hrtim_TIMER_A_init(void){

    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].TIMxCR = HRTIM_TIMCR_CONT; //!< continuous mode
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].TIMxCR |= (HRTIM_TIMER_A_CKPSCK <<  HRTIM_TIMCR_CK_PSC_bit); //prescaler
    //!< in push-pull mode it is necessary to have SETx1R == SETx2R and RSTx1R == RSRx2R
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].SETx1R = HRTIM_SET1R_CMP1;
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].RSTx1R = HRTIM_RST1R_PER;
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].SETx2R = HRTIM_SET2R_CMP1;
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].RSTx2R = HRTIM_RST2R_PER;
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].TIMxCR |= HRTIM_TIMCR_PSHPLL; //!< push-pull mode
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].OUTxR  = HRTIM_OUTR_IDLM1; //!< OUT1 IDLE state during burst
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].OUTxR |= HRTIM_OUTR_IDLM2; //!< OUT1 IDLE state during burst

    hrtim_TIMER_A_out_disable(); //!< disable outputs

    /* NVIC_EnableIRQ(HRTIM1_TIMA_IRQn); */
    /* NVIC_SetPriority(HRTIM1_TIMA_IRQn, HRTIM1_TIMA_IRQ_PRIORITY); */
}


/**
 * @brief Configure ADC triggers from HRTIM
 * @details
 **/
static void hrtim_adc_trg_cfg(void){

    HRTIM1->sCommonRegs.ADC1R |= HRTIM_ADC1R_AD1MC2; //!< ADC Trigger 1 on MASTER compare 2  ; ADC1 regular  ; temp + smps volt
    HRTIM1->sCommonRegs.ADC2R |= HRTIM_ADC2R_AD2TAC2; //!< ADC Trigger 2 on TIMER A compare 2 ; ADC1 injected ; smps curr

#ifdef OUT_MODULE_HRTIM_
    hrtim_mod_adc_trg_cfg();
#endif /* OUT_MODULE_HRTIM_ */
}

/**
 * @brief Configure HRTIM FAULTs
 * @details Timers FAULT disabled by default.
 **/
static void hrtim_fault_cfg(void){

// FAULTs CFG
    HRTIM1->sCommonRegs.FLTINR2 |= HRTIM_FLTINR2_FLTSD_0; // f_FLTS = f_HRTIM/2
    HRTIM1->sCommonRegs.FLTINR1 |= HRTIM_FLTINR1_FLT1SRC; //!< FAULT1 internal source - COMP2
    HRTIM1->sCommonRegs.FLTINR1 |= HRTIM_FLTINR1_FLT1P; //!< FAULT1 active high
    HRTIM1->sCommonRegs.FLTINR1 |= HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_1; // f1_SAMPLE = f_FLTS/16 = f_HRTIM/32 N = 5
// TIMERs FAULTs CFG
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].FLTxR |= HRTIM_FLTR_FLT1EN; //!< TIMER_A enable FAULT1
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].FLTxR |= HRTIM_FLTR_FLTLCK; //!< TIMER_A FAULT lock
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].OUTxR |= HRTIM_OUTR_FAULT1_1;//!< TIMER_A output1 fault inactive state
    HRTIM1->sTimerxRegs[HRTIM_TIMER_A_INDEX].OUTxR |= HRTIM_OUTR_FAULT2_1;//!< TIMER_A output2 fault inactive state
// INTERRUPTS CFG
    HRTIM1->sCommonRegs.IER |= HRTIM_IER_FLT1; //!< enable FAULT1 IR
    /* HRTIM1->sCommonRegs.IER |= HRTIM_IER_SYSFLT; //!< enable SYSFLT IR */

#ifdef OUT_MODULE_HRTIM_
    hrtim_mod_fault_cfg();
#endif /* OUT_MODULE_HRTIM_ */

    NVIC_EnableIRQ(HRTIM1_FLT_IRQn);
    NVIC_SetPriority(HRTIM1_FLT_IRQn, HRTIM1_FLT_IRQ_PRIORITY);
}

/**
 * @brief Configure HRTIM burst mode
 * @details Burst mode is enable after function call
 **/
static void hrtim_burst_mode_cfg(void){

//    HRTIM1->sCommonRegs.BMCR |= HRTIM_BMCR_TABM; //!< TA counter clock is stopped and the counter is reset
        HRTIM1->sCommonRegs.BMCR |= HRTIM_BMCR_BMCLK_0; //!< TA counter reset/roll-over as burst mode clock source
        HRTIM1->sCommonRegs.BMCR |= HRTIM_BMCR_BMOM; //!< continuous mode
        HRTIM1->sCommonRegs.BMCR |= HRTIM_BMCR_BMPREN; //!< preload enable

        hrtim_burst_mode_per_update(HRTIM_BURST_MODE_INIT_PERIOD);
        hrtim_burst_mode_cmp_update(HRTIM_BURST_MODE_INIT_COMPARE);

        HRTIM1->sCommonRegs.BMCR |= HRTIM_BMCR_BME; //!< burst mode enable
}


/**
 * @} end of hrtim group
 **/

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
