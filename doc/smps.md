@page smps_page SMPS Page

## Konfiguracja co i jak i czmeu ##

Mainpage opis projektu, ze podzielony na dwie czesci. Schemat ogolny genratorow. Schemat szczegolowy mojego roziwazania. Parametry generowanych impulsow. Zalozenia. Co zrobione. Co do zrobienia.

Jedna strona SMPS.
Druga strona EDM.


Po polaczkowemu, ogolnie o konfiguracji tutaj. Na angielszczyzne przetlumacze pozniej.


@todo moze podzielic dokumentacje na dwie czesci. czesc SMPS i EDM? bedzie to bardziej elastyczne no i czytelne. i tez wywalic do 2 plikow html



@section smps_hardware Hardware

Details about hardware on xxxxxx

@section smps_peripheral Peripheral

periperale i ich zastosowanie opisac chyba tutaj w mejnie.

w plikach ze zrodlami chyba nie bede tego dawal, bo nie bardzo ma to sens. ale zobaczymy jeszcze.






## HRTIMER ##


\f$ f_{BRIDGE\_PWM} = 100 kHz \f$


HRTIMER  | Funtion                   | PRESCALER  | FREQUENCY   | PERIOD    | Config          |
---------|---------------------------|------------|-------------|-----------|-----------------|
MASTER   | VOLTAGE CONTROL LOOP      |            |     xxxxx   |           |                 |
TIMER A  | PWM + CURRENT ADC TRIGER  |            |     xxxxx   |           |PUSH-PULL OUTPUT |
TIMER B  | ??????                    |            |     xxxxx   |           |                 |
TIMER C  | ADDITIONAL SMPS           |            |     xxxxx   |           |                 |



### TIMER A ###

REGISTER | Descrption                                               | VALUE |
---------|----------------------------------------------------------|-------|
PERIOD   |                                                          |       |
COMPARE1 | 100kHz duty controled complementary PWM                  |       |
COMPARE2 | Primary surrent sense adc triger                         |       |


FAULT CONFIGURATION
FAULT    | Description                                              | SOURCE |
---------|----------------------------------------------------------|--------|
FAULT 1  | Low polarity. Overcurrent protection                     |        |
FAULT x  | Low polarity. xxx                                        |        |


### TIMER B ###




### TIMER C ###

Not use


## COMPARATOR ##


COMPARATOR  | FUNCTION   | INPUT POS | INPUT NEG | OUTPUT |
------------|------------|-----------|-----------|--------|
|            |           |           |        |


## ADC's ##





### Primary current sense ###

Frequency of current sense signal is equal to doubled f_BRIDGE_PWM

\f$ f_{prim\_current} = 2*f_{BRIDGE\_PWM} = 2* 100 kHz = 200 kHz \f$

Cut off frequency for current sense signal is set by low pass filter Rxx-Cxx and equal to:
\f$ f_{s\_prim_current} = 1/(2*PI*Rxx*Cxx) =  xxx kHz \f$

According to Nyquist-Shannon sampling theorem minimum sampling frequency for current sense signal is:

\f$ f_{sample\_prim_current} = 2*f_{s\_prim\_current} = 2* xxx = xxx kHz \f$

which is corresponding to sample rate equal to xxx Msps

\f$ F_{sample\_prim_current} = 1 Msps \f$

Plot showing prim current etc.

ADC convertion is thresholding by .... (probably timer1)

ADC clock is set as:
\f$ f_{c\_ADC} = f_{APB2}/2 = 55MHz /2 = 27.5 MHz  \f$

\f$ T_{CONV8b} = 8 cycles \f$

\f$ T_{CONV12b} = 12 cycles \f$


\f$ T_{TOTAL} = T_S + T_{CONV}  \f$

\f$ T_{TOTAL} = {f_{ADC}} over {F_{sRate}} = 27.5 MHz / 1Msps = 27.5 cycles \f$

\f$ T_S = T_{TOTAL} - T_{CONV8b} =  27.5 - 8 = 9.5 cycles \f$

\f$ T_S = T_{TOTAL} - T_{CONV12b} =  27.5 - 12 = 5.5 cycles\f$

If T_S is set as 3 cycles then:

\f$ F_{sRate} = f_{ADC} / T_{TOTAL} = {f_{ADC}} over {T_S + T_{CONV12b}} = 27.5 MHz / 15 = 1.83 Msps   \f$

\f$ F_{sRate} = f_{ADC} / T_{TOTAL} = {f_{ADC}} over {T_S + T_{CONV8b}} = 27.5 MHz / 11 = 2.5 Msps   \f$


chyba 8bit wezme ??? czeba pametac ze mam konwersje current i poznie voltage. wiec Msps'y musza byc 2x wieksze
tylko jak zrobic zeby probkowalo 10 razy. bo triger wyzwoli mi tylko raz

### Secondary voltage sense ###

ooooopisac .........................


### Hardware current limit ####

Hardware current limit is provided by ....

![SMPS waveforms] (../img/smps/smps_waveforms.png)
![SMPS waveforms2] (../img/smps/smps_waveforms2.png)


## SMPS work algorithm ##






walnac jakis diagram CMC

To docelowo tutaj



## SMPS basic parameters ##



To pewnie tu docelowo


## Error handlers ##



obsluga bledow moze w oddzielnym pliku, zobaczymy


## SMPS configuration ##



Converter parameters and configuration in inc/conf/smps_config.h.
Stuff refer to implemented PID regulators (CCM control) placed in inc/conf/reg_config.h.
Details in appropriate files.

