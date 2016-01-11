@page uc_page Microcontroler Page
@section sys_conf System config

System config defined in inc/conf/config.h
File contain clock and peripheral configuration.

@section smps_peripheral Peripheral

na glownej stronie podstawowa konfiguracja periperali  i ich funkcja, bez szczegolow, szczegoly w innych plikach

### CLOCKS ####

|Clock        | Frequency test version / eventually |
|-------------|-------------------------------------|
|Core clock   | 74 MHz                              |
|AHB          | 74 MHz                              |
|APB1         | 18.5 MHz                            |
|APB2         | 74 MHz                              |

### GPIO ####

All GPIO defined in inc/conf/io_pins_config.h

| uC function           | GPIO | Driver function   | Usage                      |
|-----------------------|------|-------------------|----------------------------|
| ADC_V1   S(ADC12_IN6) | PC0  | Voltage sense 1   | SMPS output voltage        |
| ADC_V2   S(ADC12_IN7) | PC1  | Voltage sense 2   |                            |
| ADC_V3   F(ADC2_IN5)  | PC4  | Voltage sense 3   |                            | 
| ADC_I1   S(ADC12_IN8) | PC2  | Current sense 1   | SMPS primary current       |
| ADC_I2   S(ADC12_IN9) | PC3  | Current sense 2   |                            |
| ADC_I3   F(ADC2_IN3)  | PA6  | Current sense 3   |                            |
| ADC_TEMP S(ADC1_IN12) | PB1  | Temperature sense | Temperature sensor         |
| DAC1_CH2              | PA5  | NC                | NU*                        |
| DAC1_CH1              | PA4  | NC                | NU*                        |
| COMP2_INP             | PA7  |                   | SMPS primary current limit |
| OPAMP2_VINM           | PC5  | NC                |                            |
| COMP4_INP/OPAMP2_VINP | PB0  |                   |                            |
| COMP4_INM             | PB2  |                   |                            |
| COMP6_INP             | PB11 |                   |                            |
| HRTIM1_CHA1           | PA8  | PWMA1             | SMPS bridge PWM1           |
| HRTIM1_CHA2           | PA9  | PWMA2             | SMPS bridge PWM2           |
| HRTIM1_CHB1           | PA10 | PWMB1             | (SMPS bridge PWM3)         |
| HRTIM1_CHB2           | PA11 | PWMB2             | (SMPS bridge PWM4)         |
| HRTIM1_CHC1           | PB12 | PWMC1             | (SMPS synch rect PWM1)     |
| HRTIM1_CHC2           | PB13 | PWMC2             | (SMPS synch rect PWM2)     |
| HRTIM1_CHD1           | PB14 | PWMD1             |                            |
| HRTIM1_CHD2           | PB15 | PWMD2             |                            |
| HRTIM1_CHE1           | PC8  | PWME1             |                            |
| HRTIM1_CHE2           | PC9  | PWME2             |                            |
| HRTIM1_FLT5           | PC7  | Comparator/DIN    |                            |
| HRTIM1_EEV1           | PC11 | Comparator/DIN    |                            |
| HRTIM1_EEV2           | PC12 | DIN               |                            |
| SPI_NSS               | PA15 | UI                | UI                         |
| SPI_SCK               | PB3  | UI                | UI                         |
| SPI_MOSI              | PB5  | UI                | UI                         |
| SPI_MISO              | PB4  | UI                | UI?                        |
| USART1_TX             | PB6  | PFC USART         |(SMPS PFC)                  |
| USART1_RX             | PB7  | PFC USART         |(SMPS PFC)                  |
| TIM3_CH1              | PC6  | FAN Control       | SMPS fan PWM               |
| BUTTON                | PC13 | BUTTON            | UI                         |
| MISC0                 | PA0  |                   |                            |
| MISC1                 | PA1  |                   |                            |
| MISC2                 | PA2  |                   |                            |
| MISC3                 | PA3  |                   |                            |
| MISC4                 | PB10 |                   |                            |
| MISC5                 | PA12 |                   |                            |
| MISC6                 | PC10 |                   |                            |
| MISC7                 | PD2  |                   |                            |
| MISC8                 | PB8  |                   |                            |
| MISC9                 | PB9  |                   |                            |

NU - Not in use
*DAC1 use only internal, but can't be disconnected form GPIO

#### MISC IO ####

| Misc  | GPIO | Functions (not all) | 
|-------|------|---------------------|
| MISC0 | PA0  | TIM2_CH1            | 
| MISC1 | PA1  | TIM2_CH2            | 
| MISC2 | PA2  | TIM2_CH3/USART2_TX  | 
| MISC3 | PA3  | TIM2_CH4/USART2_RX  | 
| MISC4 | PB10 | FLT3/USART3_TX      | 
| MISC5 | PA12 | FLT1/COMMP2_OUT     | 
| MISC6 | PC10 | USART3_TX           | 
| MISC7 | PD2  | TIM3_ETR            | 
| MISC8 | PB8  | USART3_RX/CAN_RX    | 
| MISC9 | PB9  | USART3_TX/CAN_TX    | 

### ADC  ####

ADC1 and ADC2 clocked from AHB.

|  ADC       | Funtion                           | Conv time | Coments  | Data       |
|------------|-----------------------------------|-----------|----------|------------|
| ADC12_IN6  |  Voltage sense 1 (ADC_V1)         | 2.5 ADC   |          | ADC1->JDR2 |
| ADC12_IN7  |  Voltage sense 2 (ADC_V2)         | -----     | Free     | -----      |
| ADC2_IN5*  |  Voltage sense 3 (ADC_V3)         | -----     | Free     | -----      |
| ADC12_IN8  |  Current sense 1 (ADC_I1)         | 2.5 ADC   |          | ADC1->JDR1 |
| ADC12_IN9  |  Current sense 2 (ADC_I2)         | -----     | Free     | -----      |
| ADC2_IN3*  |  Current sense 3 (ADC_I3)         | -----     | Free     | -----      |
| ADC1_IN12  |  Temperature sense (ADC_TEMP)     | 181.5 ADC |          | DMA1_CH1   |
| ADC1_IN16  |  Temperature sense (ADC_UC_TEMP**)| 181.5 ADC |          | DMA1_CH1   |

* Fast channel
**ADC_TEMP sample timing must be greather than 2.2us

ADC1 - 10bit resolution
ADC2 - free

ADC1 - SMPS, temperature sense
ADC_V1      - ADC1_IN6 - SMPS SEC VOLTAGE
ADC_I1      - ADC1_IN8 - SMPS PRIM CURRENT
ADC_TEMP    - ADC1_IN12 - SMPS AUX TEMP
ADC_UC_TEMP - ADC1_IN16 - SMPS uC TEMP

#### ADC TRIGGER ####

| TRIGGER  | Connected to  | Source              |
|----------|---------------|---------------------|
| TRIGGER1 | ADC1 REGULAR  |HRTIM MASTER CMP2    |
| TRIGGER2 | ADC1 INJECTED |HRTIM TIMER A CMP2   |
| TRIGGER3 |               |                     |
| TRIGGER4 |               |                     |

ADC1 INJECTED SEQUENCE (TRIGGER2):
1. SMPS CURRENT - uint16_t gADC1_CH8 (IN8)

ADC1 REGULAR SEQUENCE (TRIGGER1):  max conversion time <10us
1. SMPS VOLTAGE - uint16_t gADC1_CH6  (IN6)
2. TEMP SMPS uint16_t gADC_REG[0] (IN12)
3. TEMP UC uint16_t gADC_REG[1] (IN16)(<2.2us)

ADC1 REGULAR SEQUENCE use DMA1_CH1 to transfer data from ADC1->DR to gADC1_REG array
DMA triggered by ADC->DR ??

opisac zapis z JDR

### HRTIMER ####

|HRTIMER  | Funtion  | PRESCALER  | FREQUENCY   | PERIOD    |
|---------|----------|------------|-------------|-----------|
|MASTER   | SMPS     |            |     xxxxx   |           |
|TIMER A  | SMPS     |            |     xxxxx   |           |
|TIMER B  | (SMPS)   |            |     xxxxx   |           |
|TIMER C  | (SMPS)   |            |     xxxxx   |           |
|TIMER D  | free     |            |     xxxxx   |           |
|TIMER E  | free     |            |     xxxxx   |           |

MASTER COMPARE1 - SMPS control loop
MASTER REPETITION -

### COMPARATORs ####

|COMPARATOR  | FUNCTION                   | INPUT POS    | INPUT NEG |  OUTPUT/POLARITY        |
|------------|----------------------------|--------------|-----------|-------------------------|
|COMP2       | SMPS PRIMARY CURRENT LIMIT | DAC1_CH2     |   PA7     |  LOW/FAULT1 (HRTIM_A)   |
|COMP4       | free                       |              |           |                         |
|COMP6       | free                       |              |           |                         |

### TIMER ####

|TIMER   |   Function          |   Timer type          | Timer clock | Details |
|--------|---------------------|-----------------------|-------------|---------|
|TIMER1  | ---------           | Adv timer 16bit       | -----       | -----   |
|TIMER2  | ---------           | General purpose 32bit | -----       | -----   |
|TIMER3  | FAN PWM             | General purpose 16bit | -----       | -----   |
|TIMER15 | ---------           | General purpose 16bit | -----       | -----   |
|TIMER16 | ---------           | General purpose 16bit | -----       | -----   |
|TIMER17 | Debug time meter    | General purpose 16bit | -----       | -----   |
|TIMER6  | delays              | Basic timer           | 1000 Hz     | -----   |
|TIMER7  | debouncing          | Basic timer           | 1000 Hz     | -----   |

### USART ####

|  USART  |  Function                          | Baud rate |
|---------|------------------------------------|-----------|
| USART1  | PPC communication                  |  9600     |
|(USART3) | Addition                           |  9600     |

### SPI ####

|SPI  |  Function                      | xxxxxxxxx | xxxxxxxxxxxxxxxxxx | xxx |
|-----|-------------------------------|-----------|--------------------|-----|
|SPI1 | User Interface communication  |           |                    |     |

### DAC ####

|DAC      | Function                   |  Connection   |
|---------|----------------------------|---------------|
|DAC1 ch1 | free                       |               |
|DAC1 ch2 | SMPS Primary current limit | COMP2_INM     |
|DAC2 ch1 | free                       |               |


DAC2 CH1 disconnected from GPIO (PA6).
DAC1 have not this option, so pins are useless ... :(

### ISR ###

|ISR name                      | IRS source | Priority | Functions |
|------------------------------|------------|----------|-----------|
|                              |            |          |           |

### FPU ####

### WATCHDOG ####

### SYSTICK ####
