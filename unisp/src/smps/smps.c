/**
 * @file smps.c
 * @brief SMPS functions
 * @author raiden00
 * @date 2015-09-28
 */

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

#include <math.h>
#include "unisp/inc/smps/smps.h"

/*
  +=============================================================================+
  | local functions' declarations
  +=============================================================================+
*/

static float smps_output_power_get(float output_voltage, float input_current);
//static float smps_get_prim_current_rms(float );
static float smps_prim_current_peak_get(float rms_current);
static float smps_prim_rms_current_get(float out_current, float out_voltage);
//static inline void smps_write_out_voltage(volatile struct SMPS_settings* s, float voltage);
static void smps_bridge_pwm_init(volatile struct SMPS_status* s, uint32_t frequency);
static void smps_current_limit_init(volatile struct SMPS_settings *s);
static inline void smps_out_voltage_set(volatile struct SMPS_PID_reg* pid_reg, float vout);

/*
  +=============================================================================+
  | global variables
  +=============================================================================+
*/

volatile struct SMPS_status gSmps_stat; //!< smps status
volatile struct SMPS_settings gSmps_sets; //!< smps settings
volatile struct SMPS_ADC_val gSmps_adc_val; //!< smps adc val
volatile struct SMPS_PID_reg gSmps_pid_reg;

/*
  +=============================================================================+
  | local functions
  +=============================================================================+
*/


/**
 * @addtogroup smps_function
 * @{
 */

#define SMPS_OUT_POWER_TAB_MAX 6

/**
 * @brief
 * @details
 **/
const float gpSmps_output_power[2][SMPS_OUT_POWER_TAB_MAX] = {
    {0, 25,   40,     60,     100,     150},
    {0, 100,  200,    200,    600,       0}
};


/**
 * @brief N.U
 * @details
 **/
static float smps_output_power_max_get(float out_voltage){

    volatile uint8_t i = 0;

    //!< @TODO ciagle zle
    for(i = 1; i< SMPS_OUT_POWER_TAB_MAX; i+=1){
        if(out_voltage < gpSmps_output_power[0][i]) return gpSmps_output_power[1][i-1];
    }
    return 0;
}

/**
 * @brief N.U
 * @details
 **/
/* static float smps_prim_current_rms_get(float out_current, */
/*                                        float out_voltage){ */

/*     float input_power = SMPS_EFFICIENCY_F32 * out_current * out_voltage; */
/*     float prim_voltage_rms = out_voltage * SMPS_TRANSFORMER_TURNS_RATIO_F32; */
/*     float pirm_current_rms = input_power / prim_voltage_rms; */

/* } */

/**
 * @brief N.U
 * @details
 **/
/* float smps_prim_current_max_get(float voltage){ */
    /* float out_power_max = smps_output_power_max_get(voltage); */
    /* float prim_current_max = ; */
    /* return prim_current_max; */
/* } */

/*
  +=============================================================================+
  | global functions
  +=============================================================================+
*/

/**
 * @brief Write primary overload current value to SMPS_settings instance
 * @details
 **/
void smps_overload_current_write(volatile struct SMPS_settings* s,
                                 float current){

    //!< todo: max power protection - current limit
    if(current > SMPS_PRIM_CURRENT_LIMIT_F32) current = SMPS_PRIM_CURRENT_LIMIT_F32;
    s->max_prim_current_f32 = current;
}

/**
 * @brief Write secondary output voltage value to SMPS_settings instance
 * @details @todo opis jak ustawic napiecie
 **/
inline void smps_out_voltage_write(volatile struct SMPS_settings* smps_sets,
                                   const struct SMPS_PID_reg smps_pid,
                                   float vout){

    if(vout > SMPS_OUT_VOLTAGE_MAX_F32) vout = SMPS_OUT_VOLTAGE_MAX_F32;
    else if(vout < SMPS_OUT_VOLTAGE_MIN_F32) vout = SMPS_OUT_VOLTAGE_MIN_F32;

    float out_power_max = smps_output_power_max_get(vout);
    float input_current_max = SMPS_OVERLOAD_COEFF_F32 * out_power_max * SMPS_TRANSFORMER_TURNS_RATIO_F32 /(vout * SMPS_EFFICIENCY_F32);
    float input_current = smps_sets->max_prim_current_f32;
    if(input_current > input_current_max){
        /* input_current = input_current_max; */
        /* smps_overload_current_write(s, input_current); //!< rewrite max prim current */
    }

    //!< check if soft voltage change is needed
    if((vout - smps_pid.voltage_ref_f32) > SMPS_SOFTSTART_VOLTAGE_DIFF_F32) smps_sets->soft_start = SMPS_SOFTSTART_UP;
    else if((vout - smps_pid.voltage_ref_f32) < -SMPS_SOFTSTART_VOLTAGE_DIFF_F32) smps_sets->soft_start = SMPS_SOFTSTART_DOWN;
    else smps_sets->soft_start = 0;

    smps_sets->out_voltage_f32 = vout;
}

/**
 * @brief Set vout value in SMPS_PID_reg instance
 * @details
 **/
static inline void smps_out_voltage_set(volatile struct SMPS_PID_reg* pid_reg,
                                 float vout){

    pid_reg->voltage_ref_f32 = vout*SMPS_PID_VOLTAGE_CORRECTION_SLOPE + SMPS_PID_VOLTAGE_CORRECTION_INTERCEPT; //!< pid voltage reference including linear correction
}

/**
 * @brief
 * @details Set smps overload input current from SMPS_settings instance. Hardware limit
 **/
inline void smps_overload_current_set(const struct SMPS_settings s){

    //hardware set
    //dac out set
    smps_bridge_max_current_set(s.max_prim_current_f32);
}

/**
 * @brief
 * @details @TODO: move to smps_hal?
 **/
inline void smps_overload_flt_enable(void){

    hrtim_flt1_enable();
}

/**
 * @brief SMSP action initialization
 * @details
 * Initialize SMPS bridge PWM
 * Set control loop frequency
 * Initialize PID regulator instance
 * (optionaly) SMPS delay
 * Set init current limit
 * Enable hardware faults
 **/
void smps_init(volatile struct SMPS_settings* smps_sets,
               volatile struct SMPS_status* smps_stat,
               volatile struct SMPS_PID_reg* pid_reg){

    smps_bridge_pwm_init(smps_stat, SMPS_BRIDGE_SWITCH_FREQUENCY); //!<
    smps_control_loop_freq_set(SMPS_CONTROL_LOOP_FREQUENCY); //!< set smps control loop frequency
    smps_pid_reg_init(pid_reg); //!< initialize SMPS PID regulator (current and voltage)
    smps_current_limit_init(smps_sets);
//    smps_overload_current_set(smps_sets); //!< set hardware current limit
    smps_delay_ms(2); //!< delay to prevent overload fault trigger after next line  @TODO: work around??
    smps_overload_flt_enable(); //!< enable hardware overload limit
}


/**
 * @brief Start SMPS
 * @details Set new output voltage, acording to smps_sets
 * @return uint8_t s->smps_run value.
 **/
inline uint8_t smps_start(const struct SMPS_settings smps_sets,
                          volatile struct SMPS_status* smps_stat,
                          volatile struct SMPS_PID_reg* pid_reg){

    if(smps_stat->smps_enable && !smps_stat->smps_fault){

        smps_overload_current_set(smps_sets); //!< set hardware current limit
        float vout = pid_reg->voltage_ref_f32; //!< store current vout voltage

        if(!smps_stat->smps_run){ //!< if smps not running - adc start, regulator start, bridge pwm enable, softstart

            vout =  SMPS_OUT_VOLTAGE_INIT_F32; //!< start with init out voltage
            smps_out_voltage_set(pid_reg, vout); //!<
            smps_adc_reg_inj_start(); //!<
            smps_pid_reg_start(pid_reg); //!<
            smps_bridge_pwm_enable(); //!< enable bridge pwm
            SMPS_RUN_LED_ON;

            smps_delay_ms(SMPS_START_DELAY_ms); //!<
        }

        //!< @TODO: optimalisation ?
        switch(smps_sets.soft_start){
        case SMPS_SOFTSTART_DISABLE: // (0)do nothing
            break;
        case SMPS_SOFTSTART_UP: // (1)
            while(vout <= (smps_sets.out_voltage_f32 - SMPS_SOFTSTART_VOLTAGE_STEP_F32)){
                smps_out_voltage_set(pid_reg, vout);
                vout += SMPS_SOFTSTART_VOLTAGE_STEP_F32;
                smps_delay_ms(SMPS_SOFTSTART_DELAY_ms); //!< wait
            }
            break;
        case SMPS_SOFTSTART_DOWN: //(2)
            while(vout >= (smps_sets.out_voltage_f32 + SMPS_SOFTSTART_VOLTAGE_STEP_F32)){
                smps_out_voltage_set(pid_reg, vout);
                vout -= SMPS_SOFTSTART_VOLTAGE_STEP_F32;
                smps_delay_ms(SMPS_SOFTSTART_DELAY_ms); //!< wait
            }
            break;
        }

        smps_out_voltage_set(pid_reg, smps_sets.out_voltage_f32); //!< rewrite smps out voltage to pid structure
        smps_stat->smps_run = 1;
    }
    else{
        smps_stop(smps_stat, pid_reg);
    }

    return smps_stat->smps_run;
}

/**
 * @brief Stop SMPS PWM
 * @details
 **/
inline void smps_stop(volatile struct SMPS_status* s,
                      volatile struct SMPS_PID_reg* pid_reg){

    smps_bridge_pwm_disable();
    smps_adc_reg_inj_stop(); //!<
    smps_pid_reg_stop(pid_reg);
    s->smps_run = 0;
    SMPS_RUN_LED_OFF;
}

/**
 * @brief Set smps_enable flag required to start converter (smps_start())
 * @details
 **/
inline void smps_enable(volatile struct SMPS_status* s){

    s->smps_enable = 1;
}

/**
 * @brief Reset smps_enable flag required to start converter (smps_start())
 * @details
 **/
inline void smps_disable(volatile struct SMPS_status* s){

    s->smps_enable = 0;
}

/**
 * @brief
 * @details Write to SMPS_settings struct current=0 and voltage=0
 **/
void smps_settings_struct_reset(volatile struct SMPS_settings* smps_sets, volatile struct SMPS_PID_reg *smps_pid){

    smps_out_voltage_write(smps_sets, *smps_pid, 0);
    smps_overload_current_write(smps_sets, 0);
    smps_out_voltage_set(smps_pid, 0);
}

/* /\** */
/*  * @brief Disable SMPS inrush protection after SMPS_INRUSH_DELAY_ms time. */
/*  * @details */
/*  **\/ */
/* void smps_inrush_protection_off(void){ */

/*     timer6_wait_ms(SMPS_INRUSH_DELAY_ms); */
/*     SMPS_INRUSH_PROTECTION_DISABLE; */
/* } */

/**
 * @brief SMPS bridge PWM init.
 * @details Set PWM frequency and initial duty cycle
 PWM output disable and smps_enable flag clear after function call
**/
static void smps_bridge_pwm_init(volatile struct SMPS_status* s,
                          uint32_t frequency){

    smps_bridge_pwm_frequency_set(frequency);
    smps_bridge_pwm_duty_set(SMPS_BRIDGE_DUTY_CYCLE_MIN_F32);
    smps_bridge_pwm_disable();
    smps_disable(s);
}

/**
 * @brief
 * @details
 **/
/* void smps_init_and_loop(const struct SMPS_settings smps_set, */
/*                         struct SMPS_status* smps_stat, */
/*                         struct SMPS_PID_reg* pid_reg){ */
/* } */

/**
 * @brief
 * @details
 **/
inline float smps_uc_temp_get(float sensor_voltage){

    return (100 * ((SMPS_UC_TEMP_V25_F32 - sensor_voltage) / SMPS_UC_TEMP_AVGS_F32) + 25.0);
}

/**
 * @brief
 * @details
 **/
inline float smps_aux_temp_get(float sensor_voltage){
}

/* void smps_const_current_mode_init(){ */

/* } */

/* void smps_cons_voltage_mode_init(){ */

/* } */

/**
 * @brief
 * @details
 **/
void smps_pid_reg_start(volatile struct SMPS_PID_reg* pid_reg){

    arm_pid_reset_f32(&(pid_reg->voltage_pid));
    arm_pid_reset_f32(&(pid_reg->current_pid));
    smps_control_loop_start();
    pid_reg->run = 1;
}

/**
 * @brief
 * @details
 **/
void smps_pid_reg_stop(volatile struct SMPS_PID_reg* pid_reg){

    smps_control_loop_stop();
    pid_reg->run = 0;
}

/**
 * @brief SMPS Average Current Mode Control regulator init
 * @details
 **/
void smps_ACMC_regulator_init(void){

}

/**
 * @brief
 * @details
 */
inline void smps_fan_duty_write(volatile struct SMPS_settings* smps_sets, float duty){

    if(duty < SMPS_FAN_DUTY_MIN) duty = SMPS_FAN_DUTY_MIN;
    if(duty > SMPS_FAN_DUTY_MAX) duty = SMPS_FAN_DUTY_MAX;

    smps_sets->fan_duty_f32 = duty;
    smps_fan_duty_set(smps_sets->fan_duty_f32);
}

/**
 * @brief
 * @details
 */
inline float smps_fan_duty_get(const struct SMPS_settings smps_sets){

    return smps_sets.fan_duty_f32;
}

/**
 * @brief
 * @details
 */
inline void smps_temp_regulator(const struct SMPS_ADC_val adc){

    /* if(adc.uc_temp_f32> XXX); */
    /* if(adc.aux_temp_32 > XXX); */
}

/**
 * @brief
 * @details
 */
inline void smps_overload_reset(volatile struct SMPS_status* s){

    s->overcurrent = 0;
    SMPS_OVERLOAD_LED_OFF;
}

/**
 * @brief
 * @details
 */
inline void smps_overload(volatile struct SMPS_status* s, volatile struct SMPS_PID_reg* pid_reg){

    s->overcurrent = 1;
    smps_stop(s, pid_reg);
    SMPS_OVERLOAD_LED_ON;
}

/**
 * @brief
 * @details
 */
inline void smps_overvoltage(volatile struct SMPS_status* s){

    s->overvoltage = 1;
}

/**
 * @brief
 * @details
 */
inline void smps_burst_enable(volatile struct SMPS_status* s){

    smps_burst_mode_start();
    s->burst = 1;
}

/**
 * @brief
 * @details
 */
inline void smps_burst_disable(volatile struct SMPS_status* s){

    smps_burst_mode_stop();
    s->burst = 0;
}

/**
 * @brief
 * @details
 */
inline void smps_burst_increase(volatile struct SMPS_status* s){

    float duty = smps_burst_mode_duty_get();
    duty += SMPS_BURST_MODE_DUTY_STEP_F32;

    if(!s->burst){
        smps_burst_enable(s); //!< enable burst if not enabled
    }
    else smps_burst_mode_update(duty);
}

/**
 * @brief
 * @details
 */
inline void smps_burst_decrease(volatile struct SMPS_status* s){

    float duty = smps_burst_mode_duty_get();
    duty -= SMPS_BURST_MODE_DUTY_STEP_F32;

    if(duty < SMPS_BURST_MODE_START_DUTY_F32){
        smps_burst_disable(s); //!<
    }
    else smps_burst_mode_update(duty);
}

/**
 * @brief
 * @details
 */
inline float smps_pid_current_f32(arm_pid_instance_f32 * S, float32_t in){

    float32_t out;

/* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
        (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    if(out > SMPS_PID_CURRENT_OUT_SATURATION_MAX_F32) out = SMPS_PID_CURRENT_OUT_SATURATION_MAX_F32;

/* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    return (out);
}

/**
 * @brief
 * @details
 */
inline float smps_pid_voltage_f32(arm_pid_instance_f32 * S, float32_t in){

    float32_t out;

/* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
        (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    if(out > SMPS_PID_VOLTAGE_OUT_SATURATION_MAX_F32) out = SMPS_PID_VOLTAGE_OUT_SATURATION_MAX_F32;

/* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    return (out);
}

/**
 * @brief
 * @details
 */
void arm_pid_init_f32(arm_pid_instance_f32 * S, int32_t resetStateFlag){

  /* Derived coefficient A0 */
  S->A0 = S->Kp + S->Ki + S->Kd;

  /* Derived coefficient A1 */
  S->A1 = (-S->Kp) - ((float32_t) 2.0 * S->Kd);

  /* Derived coefficient A2 */
  S->A2 = S->Kd;

  /* Check whether state needs reset or not */
  if(resetStateFlag)
  {
    /* Clear the state buffer.  The size will be always 3 samples */
    memset(S->state, 0, 3u * sizeof(float32_t));
  }
}

/**
 * @brief
 * @details
 */
void arm_pid_reset_f32(arm_pid_instance_f32 * S){

  /* Clear the state buffer.  The size will be always 3 samples */
  memset(S->state, 0, 3u * sizeof(float32_t));
}

/**
 * @brief
 * @details
 */
static void smps_current_limit_init(volatile struct SMPS_settings *s){

    smps_overload_current_write(s, SMPS_OVERLOAD_CURRENT_INIT);
    smps_overload_current_set(*s);
}


/**
 * @} end of smps_function group
 */

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
