#include "hal_adc.h"

/******************************/

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_INTERRUPT_HANDLER)(void) = NULL ;        
#endif
static inline void select_result_format(const ADC_config_t *_adc);
static inline void select_voltage(const ADC_config_t *_adc);

/******************************/

std_ReturneType ADC_initialize(const ADC_config_t *_adc)
{
    std_ReturneType ret = E_NOT_OK ;
    if(_adc == NULL)
        ret = E_NOT_OK ;
    else
    {
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT = _adc->Time ;
        ADCON2bits.ADCS = _adc->Frequency ;
        ADCON0bits.CHS  = _adc->ANx ;
        ret = gpio_pin_direction_intialize(&(_adc->ADC_pin));
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(_adc->priority == HIGH_PRIORITY)
            ADC_HIGH_PRIORITY_SET();
        else if(_adc->priority == LOW_PRIORITY)
            ADC_LOW_PRIORITY_SET();
        else{/* Nothing */}
        #endif
        ADC_INTERRUPT_HANDLER = _adc->ADC_INTERRUPT_HANDLER ;
        #endif
        select_result_format(_adc);
        select_voltage(_adc);
        ADC_CONVERTER_ENABLE();
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_deinitialize(const ADC_config_t *_adc)
{
    std_ReturneType ret = E_NOT_OK ;
    if(_adc == NULL)
        ret = E_NOT_OK ;
    else
    {
        ADC_CONVERTER_DISABLE();
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_select_channel(const ADC_config_t *_adc , uint8 channel)
{
    std_ReturneType ret = E_NOT_OK ;
    if(_adc == NULL)
        ret = E_NOT_OK ;
    else
    {
        ADCON0bits.CHS  = channel ;
        ret = gpio_pin_direction_intialize(&(_adc->ADC_pin));
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_start_conversion(const ADC_config_t *_adc)
{
    std_ReturneType ret = E_NOT_OK ;
    if(_adc == NULL)
        ret = E_NOT_OK ;
    else
    {
        ADC_CONVERTER_IN_PROGRESS();
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_is_conversion_done(const ADC_config_t *_adc , uint8 *conversion_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if((_adc == NULL) || (conversion_status == NULL))
        ret = E_NOT_OK ;
    else
    {
        *conversion_status = (uint8)(!(ADC_CONVERTER_STATUS()));
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_get_conversion_result(const ADC_config_t *_adc , uint16 *conversion_result)
{
    std_ReturneType ret = E_NOT_OK ;
    if((_adc == NULL) || (conversion_result == NULL))
        ret = E_NOT_OK ;
    else
    {
        if(_adc->Justified == ADC_LEFT)
        {
            *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6) ;
        }
        else
        {
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL) ;
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_get_conversion(const ADC_config_t *_adc , uint8 channel , uint16 *conversion_result)
{
    std_ReturneType ret = E_NOT_OK ;
    if((_adc == NULL) || (conversion_result == NULL))
        ret = E_NOT_OK ;
    else
    {
        uint8 l_conversion_status = 0 ;
        ret = ADC_select_channel(_adc , channel);
        ret = ADC_start_conversion(_adc);
        while(ADCON0bits.GO_nDONE);
        ret = ADC_get_conversion_result(_adc , conversion_result); 
    }
    return ret ;
}

/******************************/

std_ReturneType ADC_start_conversion_interrupt(const ADC_config_t *_adc , uint8 channel)
{
    std_ReturneType ret = E_NOT_OK ;
    if(_adc == NULL) 
        ret = E_NOT_OK ;
    else
    { 
        ret = ADC_select_channel(_adc , channel);
        ret = ADC_start_conversion(_adc); 
    }
    return ret ;
}

/******************************/

static inline void select_result_format(const ADC_config_t *_adc)
{
    if(ADC_Right == _adc->Justified)
    {
        Right_Justified();
    }
    else if(_adc->Justified == ADC_LEFT)
    {
        Left_Justified();
    }
    else
    {
        Right_Justified();
    }
}

/******************************/

static inline void select_voltage(const ADC_config_t *_adc)
{
    if(ADC_VCC_GND == _adc->Volte)
    {
        ADC_VREF_DISABLE();
    }
    else if(_adc->Volte == ADC_VREF)
    {
        ADC_VREF_ENABLE();
    }
    else
    {
        ADC_VREF_DISABLE();
    }
}

/******************************/

void ADC_ISR(void) 
{
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_INTERRUPT_HANDLER)
        ADC_INTERRUPT_HANDLER();
}

/******************************/