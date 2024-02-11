#ifndef HAL_ADC_H
#define	HAL_ADC_H

#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupt.h"

#define ADC_CONVERTER_ENABLE()        (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()       (ADCON0bits.ADON = 0)

#define ADC_CONVERTER_IN_PROGRESS()   (ADCON0bits.GODONE = 1)
#define ADC_CONVERTER_IDEL()          (ADCON0bits.GODONE = 0)
#define ADC_CONVERTER_STATUS()        (ADCON0bits.GO_nDONE)
#define ADC_CONVERTER_DONE            1
#define ADC_CONVERTER_IN_PROSS        0

#define ADC_AN_0                      0X0 
#define ADC_AN_1                      0X1
#define ADC_AN_2                      0X2
#define ADC_AN_3                      0X3
#define ADC_AN_4                      0X4
#define ADC_AN_5                      0X5
#define ADC_AN_6                      0X6
#define ADC_AN_7                      0X7
#define ADC_AN_8                      0X8
#define ADC_AN_9                      0X9
#define ADC_AN_10                     0XA
#define ADC_AN_11                     0XB
#define ADC_AN_12                     0XC

#define ADC_VREF_ENABLE()             do{ADCON1bits.VCFG1 = 1 ; \
                                         ADCON1bits.VCFG0 = 1 ; \
                                         }while(0)
#define ADC_VREF_DISABLE()            do{ADCON1bits.VCFG1 = 0 ; \
                                         ADCON1bits.VCFG0 = 0 ; \
                                         }while(0)
#define ADC_VREF                      1
#define ADC_VCC_GND                   0

#define AN_0_FUNCTIONALITY            0XE 
#define AN_1_FUNCTIONALITY            0XD
#define AN_2_FUNCTIONALITY            0XC
#define AN_3_FUNCTIONALITY            0XB
#define AN_4_FUNCTIONALITY            0XA
#define AN_5_FUNCTIONALITY            0X9
#define AN_6_FUNCTIONALITY            0X8
#define AN_7_FUNCTIONALITY            0X7
#define AN_8_FUNCTIONALITY            0X6
#define AN_9_FUNCTIONALITY            0X5
#define AN_10_FUNCTIONALITY           0X4
#define AN_11_FUNCTIONALITY           0X3
#define AN_12_FUNCTIONALITY           0X2
#define AN_ALL_ANALOG_FUNCTIONALITY   0X0
#define AN_ALL_DIGITAL_FUNCTIONALITY  0XF

#define ADC_PORT_CONFIG(CONFIG)       (ADCON1bits.PCFG = CONFIG)

#define Right_Justified()             (ADCON2bits.ADFM = 1)
#define Left_Justified()              (ADCON2bits.ADFM = 0)
#define ADC_Right                     1
#define ADC_LEFT                      0

#define ADC_TAD_0                     0X0
#define ADC_TAD_2                     0X1
#define ADC_TAD_4                     0X2
#define ADC_TAD_6                     0X3
#define ADC_TAD_8                     0X4
#define ADC_TAD_12                    0X5
#define ADC_TAD_16                    0X6
#define ADC_TAD_20                    0X7

#define ADC_FOSC_2                    0X0
#define ADC_FOSC_4                    0X4
#define ADC_FOSC_8                    0X1
#define ADC_FOSC_16                   0X5
#define ADC_FOSC_32                   0X2
#define ADC_FOSC_64                   0X6
#define ADC_FRC                       0X3

typedef struct 
{
    #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_INTERRUPT_HANDLER)(void);
    INTERRUPT_PRIORITY_CFG priority;
    #endif
    pin_config_t ADC_pin   ;
    uint8 ANx              ;
    uint8 Frequency        ;
    uint8 Time             ;
    uint8 Justified    : 1 ;
    uint8 Volte        : 1 ;
    uint8 ADC_Reserved : 6 ;
}ADC_config_t;

std_ReturneType ADC_initialize(const ADC_config_t *_adc);
std_ReturneType ADC_deinitialize(const ADC_config_t *_adc);
std_ReturneType ADC_select_channel(const ADC_config_t *_adc , uint8 channel);
std_ReturneType ADC_start_conversion(const ADC_config_t *_adc);
std_ReturneType ADC_is_conversion_done(const ADC_config_t *_adc , uint8 *conversion_status);
std_ReturneType ADC_get_conversion_result(const ADC_config_t *_adc , uint16 *conversion_result);
std_ReturneType ADC_get_conversion(const ADC_config_t *_adc , uint8 channel , uint16 *conversion_result);
std_ReturneType ADC_start_conversion_interrupt(const ADC_config_t *_adc , uint8 channel);

#endif	/* HAL_ADC_H */