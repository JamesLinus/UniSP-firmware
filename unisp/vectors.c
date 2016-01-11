/**
 * @file vectors.c
 * @brief STM32F334x8 vector table and __Default_Handler()
 * @details STM32334x8 vector table and __Default_Handler()
 * @author raiden00
 * @date 2015-09-28
 **/

/******************************************************************************
 * chip: STM32F334x8
 * compiler: arm-none-eabi-gcc
 *
 ******************************************************************************/

/**
 * @brief Default interrupt handler.
 * @details Default interrupt handler, used for interrupts that don't have their
 * own handler defined.
 **/
static void __Default_Handler(void) __attribute__ ((interrupt));
static void __Default_Handler(void)
{
	while (1);
}

/*
  +=============================================================================+
  | assign all unhandled interrupts to the default handler
  +=============================================================================+
*/

// Non-maskable interrupt (RCC clock security system)
void NMI_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// All class of fault
void HardFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Memory management
void MemManage_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pre-fetch fault, memory access fault
void BusFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Undefined instruction or illegal state
void UsageFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x1C
void __Reserved_0x1C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x20
void __Reserved_0x20_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x24
void __Reserved_0x24_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x28
void __Reserved_0x28_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System service call via SWI instruction
void SVC_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Debug monitor
void DebugMon_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x34
void __Reserved_0x34_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pendable request for system service
void PendSV_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System tick timer
void SysTick_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Window WatchDog
void WWDG_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// PVD through EXTI Line detection
void PVD_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Tamper and TimeStamps through the EXTI line
void TAMP_STAMP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RTC Wakeup through the EXTI line
void RTC_WKUP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// FLASH
void FLASH_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RCC
void RCC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line0
void EXTI0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line1
void EXTI1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line2
void EXTI2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line3
void EXTI3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line4
void EXTI4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 1
void DMA1_Channel1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 2
void DMA1_Channel2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 3
void DMA1_Channel3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 4
void DMA1_Channel4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 5
void DMA1_Channel5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 6
void DMA1_Channel6_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Channel 7
void DMA1_Channel7_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// ADC1, ADC2
void ADC1_2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN TX
void CAN_TX_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN RX0
void CAN_RX0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN RX1
void CAN_RX1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN SCE
void CAN_SCE_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// External Line[9:5]s
void EXTI9_5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 Break and TIM15
void TIM1_BRK_TIM15_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 Update and TIM16
void TIM1_UP_TIM16_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 Trigger and Commutation and TIM17
void TIM1_TRG_COM_TIM17_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 Capture Compare
void TIM1_CC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM2
void TIM2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM3
void TIM3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xB8
void __Reserved_0xB8_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C1 Event
void I2C1_EV_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C1 Error
void I2C1_ER_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xC4
void __Reserved_0xC4_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xC8
void __Reserved_0xC8_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI1
void SPI1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xD0
void __Reserved_0xD0_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART1
void USART1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART2
void USART2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART3
void USART3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// External Line[15:10]s
void EXTI15_10_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RTC Alarm (A and B) through EXTI Line
void RTC_Alarm_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xE8
void __Reserved_0xE8_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xEC
void __Reserved_0xEC_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xF0
void __Reserved_0xF0_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xF4
void __Reserved_0xF4_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xF8
void __Reserved_0xF8_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0xFC
void __Reserved_0xFC_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x100
void __Reserved_0x100_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x104
void __Reserved_0x104_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x108
void __Reserved_0x108_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x10C
void __Reserved_0x10C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x110
void __Reserved_0x110_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x114
void __Reserved_0x114_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM6 and DAC1
void TIM6_DAC1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM7 and DAC2
void TIM7_DAC2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x120
void __Reserved_0x120_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x124
void __Reserved_0x124_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x128
void __Reserved_0x128_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x12C
void __Reserved_0x12C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x130
void __Reserved_0x130_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x134
void __Reserved_0x134_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x138
void __Reserved_0x138_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x13C
void __Reserved_0x13C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// COMP2
void COMP2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// COMP4_6
void COMP4_6_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x148
void __Reserved_0x148_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_Master
void HRTIM1_Master_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_TIMA
void HRTIM1_TIMA_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_TIMB
void HRTIM1_TIMB_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_TIMC
void HRTIM1_TIMC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_TIMD
void HRTIM1_TIMD_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_TIME
void HRTIM1_TIME_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// HRTIM1_FLT
void HRTIM1_FLT_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x168
void __Reserved_0x168_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x16C
void __Reserved_0x16C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x170
void __Reserved_0x170_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x174
void __Reserved_0x174_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x178
void __Reserved_0x178_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x17C
void __Reserved_0x17C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x180
void __Reserved_0x180_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// FPU
void FPU_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));


/*
  +=============================================================================+
  | Vector table
  +=============================================================================+
*/

extern const char __main_stack_end;			// imported main stack end (from linker script)

void Reset_Handler(void);					// import the address of Reset_Handler()

void (* const vectors[])(void) __attribute__ ((section(".vectors"))) = {
    (void (*)(void))&__main_stack_end,	// Main stack end address
    Reset_Handler,						// Reset
    NMI_Handler,						// Non-maskable interrupt (RCC clock security system)
    HardFault_Handler,					// All class of fault
    MemManage_Handler,					// Memory management
    BusFault_Handler,					// Pre-fetch fault, memory access fault
    UsageFault_Handler,					// Undefined instruction or illegal state
    __Reserved_0x1C_Handler,			// Reserved 0x1C
    __Reserved_0x20_Handler,			// Reserved 0x20
    __Reserved_0x24_Handler,			// Reserved 0x24
    __Reserved_0x28_Handler,			// Reserved 0x28
    SVC_Handler,						// System service call via SWI instruction
    DebugMon_Handler,					// Debug monitor
    __Reserved_0x34_Handler,			// Reserved 0x34
    PendSV_Handler,						// Pendable request for system service
    SysTick_Handler,					// System tick timer
    WWDG_IRQHandler,					// Window WatchDog
    PVD_IRQHandler,						// PVD through EXTI Line detection
    TAMP_STAMP_IRQHandler,				// Tamper and TimeStamps through the EXTI line
    RTC_WKUP_IRQHandler,				// RTC Wakeup through the EXTI line
    FLASH_IRQHandler,					// FLASH
    RCC_IRQHandler,						// RCC
    EXTI0_IRQHandler,					// EXTI Line0
    EXTI1_IRQHandler,					// EXTI Line1
    EXTI2_IRQHandler,					// EXTI Line2
    EXTI3_IRQHandler,					// EXTI Line3
    EXTI4_IRQHandler,					// EXTI Line4
    DMA1_Channel1_IRQHandler,			// DMA1 Channel 1
    DMA1_Channel2_IRQHandler,			// DMA1 Channel 2
    DMA1_Channel3_IRQHandler,			// DMA1 Channel 3
    DMA1_Channel4_IRQHandler,			// DMA1 Channel 4
    DMA1_Channel5_IRQHandler,			// DMA1 Channel 5
    DMA1_Channel6_IRQHandler,			// DMA1 Channel 6
    DMA1_Channel7_IRQHandler,			// DMA1 Channel 7
    ADC1_2_IRQHandler,					// ADC1, ADC2
    CAN_TX_IRQHandler,					// CAN1 TX
    CAN_RX0_IRQHandler,				// CAN1 RX0
    CAN_RX1_IRQHandler,				// CAN1 RX1
    CAN_SCE_IRQHandler,				// CAN1 SCE
    EXTI9_5_IRQHandler,					// External Line[9:5]s
    TIM1_BRK_TIM15_IRQHandler,			// TIM1 Break and TIM15
    TIM1_UP_TIM16_IRQHandler,			// TIM1 Update and TIM16
    TIM1_TRG_COM_TIM17_IRQHandler,		// TIM1 Trigger and Commutation and TIM17
    TIM1_CC_IRQHandler,					// TIM1 Capture Compare
    TIM2_IRQHandler,					// TIM2
    TIM3_IRQHandler,					// TIM3
    __Reserved_0xB8_Handler,            // Reserved 0xB8
    I2C1_EV_IRQHandler,					// I2C1 Event
    I2C1_ER_IRQHandler,					// I2C1 Error
    __Reserved_0xC4_Handler,            // Reserved 0xC4
    __Reserved_0xC8_Handler,            // Reserved 0xC8
    SPI1_IRQHandler,					// SPI1
    __Reserved_0xD0_Handler,            // Reserved 0xD0
    USART1_IRQHandler,					// USART1
    USART2_IRQHandler,					// USART2
    USART3_IRQHandler,					// USART3
    EXTI15_10_IRQHandler,				// External Line[15:10]s
    RTC_Alarm_IRQHandler,				// RTC Alarm (A and B) through EXTI Line
    __Reserved_0xE8_Handler,            // Reserved 0xE8
    __Reserved_0xEC_Handler,            // Reserved 0xEC
    __Reserved_0xF0_Handler,            // Reserved 0xF0
    __Reserved_0xF4_Handler,            // Reserved 0xF4
    __Reserved_0xF8_Handler,            // Reserved 0xF8
    __Reserved_0xFC_Handler,            // Reserved 0xFC
    __Reserved_0x100_Handler,            // Reserved 0x100
    __Reserved_0x104_Handler,            // Reserved 0x104
    __Reserved_0x108_Handler,            // Reserved 0x108
    __Reserved_0x10C_Handler,            // Reserved 0x10C
    __Reserved_0x110_Handler,            // Reserved 0x110
    __Reserved_0x114_Handler,            // Reserved 0x114
    TIM6_DAC1_IRQHandler,				// TIM6 and DAC1
    TIM7_DAC2_IRQHandler,				// TIM7 and DAC2
    __Reserved_0x120_Handler,            // Reserved 0x120
    __Reserved_0x124_Handler,            // Reserved 0x124
    __Reserved_0x128_Handler,            // Reserved 0x128
    __Reserved_0x12C_Handler,            // Reserved 0x12C
    __Reserved_0x130_Handler,            // Reserved 0x130
    __Reserved_0x134_Handler,            // Reserved 0x134
    __Reserved_0x138_Handler,            // Reserved 0x138
    __Reserved_0x13C_Handler,            // Reserved 0x13C
    COMP2_IRQHandler,				     // COMP2
    COMP4_6_IRQHandler,				     // COMP4_6
    __Reserved_0x148_Handler,            // Reserved 0x148
    HRTIM1_Master_IRQHandler,     	     // HRTIM1_Master
    HRTIM1_TIMA_IRQHandler, 		     // HRTIM1_TIMA
    HRTIM1_TIMB_IRQHandler, 		     // HRTIM1_TIMB
    HRTIM1_TIMC_IRQHandler, 		     // HRTIM1_TIMC
    HRTIM1_TIMD_IRQHandler, 		     // HRTIM1_TIMD
    HRTIM1_TIME_IRQHandler, 		     // HRTIM1_TIME
    HRTIM1_FLT_IRQHandler, 		         // HRTIM1_FLT
    __Reserved_0x168_Handler,            // Reserved 0x168
    __Reserved_0x16C_Handler,            // Reserved 0x16C
    __Reserved_0x170_Handler,            // Reserved 0x170
    __Reserved_0x174_Handler,            // Reserved 0x174
    __Reserved_0x178_Handler,            // Reserved 0x178
    __Reserved_0x17C_Handler,            // Reserved 0x17C
    __Reserved_0x180_Handler,            // Reserved 0x180
    FPU_IRQHandler,						// FPU

};

/******************************************************************************
 * END OF FILE
 ******************************************************************************/
