#include "mcal_external_interrupt.h"

/***********************************/

Interrupt_handler Interrupt_handler_INT0     = NULL ;
Interrupt_handler Interrupt_handler_INT1     = NULL ;
Interrupt_handler Interrupt_handler_INT2     = NULL ;

Interrupt_handler Interrupt_handler_RB4_HIGH = NULL ;
Interrupt_handler Interrupt_handler_RB5_HIGH = NULL ;
Interrupt_handler Interrupt_handler_RB6_HIGH = NULL ;
Interrupt_handler Interrupt_handler_RB7_HIGH = NULL ;
Interrupt_handler Interrupt_handler_RB4_LOW  = NULL ;
Interrupt_handler Interrupt_handler_RB5_LOW  = NULL ;
Interrupt_handler Interrupt_handler_RB6_LOW  = NULL ;
Interrupt_handler Interrupt_handler_RB7_LOW  = NULL ;

static std_ReturneType Interrupt_INTx_ENABLE(const interrupt_INTx_t *int_obj);
static std_ReturneType Interrupt_INTx_DISABLE(const interrupt_INTx_t *int_obj);
static std_ReturneType Interrupt_INTx_PRIORITY_INIT(const interrupt_INTx_t *int_obj);
static std_ReturneType Interrupt_INTx_EDGE_INIT(const interrupt_INTx_t *int_obj);
static std_ReturneType Interrupt_INTx_PIN_INIT(const interrupt_INTx_t *int_obj);
static std_ReturneType Interrupt_INTx_CLEAR_FLAG(const interrupt_INTx_t *int_obj);

static std_ReturneType INT0_SET_Interrupt_handler(void (* Interrupt_handler)(void));
static std_ReturneType INT1_SET_Interrupt_handler(void (* Interrupt_handler)(void));
static std_ReturneType INT2_SET_Interrupt_handler(void (* Interrupt_handler)(void));
static std_ReturneType Interrupt_INTx_SET_Interrupt_handler(const interrupt_INTx_t *int_obj);

static std_ReturneType Interrupt_RBx_ENABLE(const interrupt_RBx_t *int_obj);
static std_ReturneType Interrupt_RBx_DISABLE(const interrupt_RBx_t *int_obj);
static std_ReturneType Interrupt_RBx_PRIORITY_INIT(const interrupt_RBx_t *int_obj);
static std_ReturneType Interrupt_RBx_PIN_INIT(const interrupt_RBx_t *int_obj);
static std_ReturneType Interrupt_RBx_CLEAR_FLAG(const interrupt_RBx_t *int_obj);

static std_ReturneType RB4_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void));
static std_ReturneType RB5_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void));
static std_ReturneType RB6_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void));
static std_ReturneType RB7_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void));
static std_ReturneType RB4_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void));
static std_ReturneType RB5_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void));
static std_ReturneType RB6_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void));
static std_ReturneType RB7_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void));
static std_ReturneType Interrupt_RBx_SET_Interrupt_handler(const interrupt_RBx_t *int_obj);

/***********************************/

std_ReturneType Interrupt_INTx_initialize(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        ret |= Interrupt_INTx_DISABLE(int_obj);
        ret |= Interrupt_INTx_CLEAR_FLAG(int_obj);
        ret |= Interrupt_INTx_EDGE_INIT(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= Interrupt_INTx_PRIORITY_INIT(int_obj);
        #endif
        ret |= Interrupt_INTx_SET_Interrupt_handler(int_obj);
        ret |= Interrupt_INTx_PIN_INIT(int_obj);
        ret |= Interrupt_INTx_ENABLE(int_obj);
    }
    return ret ;
}

/***********************************/

std_ReturneType Interrupt_INTx_deinitialize(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        ret = Interrupt_INTx_DISABLE(int_obj);
    }
    return ret ;
}

/***********************************/

std_ReturneType Interrupt_RBx_initialize(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        ret = Interrupt_RBx_DISABLE(int_obj);
        ret = Interrupt_RBx_CLEAR_FLAG(int_obj);       
        ret = Interrupt_RBx_PRIORITY_INIT(int_obj);
        ret = Interrupt_RBx_PIN_INIT(int_obj);
        ret = Interrupt_RBx_SET_Interrupt_handler(int_obj);    
        ret = Interrupt_RBx_ENABLE(int_obj);
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

std_ReturneType Interrupt_RBx_deinitialize(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        ret = Interrupt_RBx_DISABLE(int_obj);
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_INTx_ENABLE(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->source)
        {
            case INT_0 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_INT0_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            case INT_1 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();  
                else if(int_obj->priority == HIGH_PRIORITY)
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_INT1_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            case INT_2 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();  
                else
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_INT2_INTERRUPT_ENABLE(); 
                ret = E_OK ; 
                break ;
            default   : ret = E_NOT_OK ; 
        }
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_INTx_DISABLE(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->source)
        {
            case INT_0 : 
                EXTERNAL_INT0_INTERRUPT_DISABLE(); 
                ret = E_OK ; 
                break ;
            case INT_1 : 
                EXTERNAL_INT1_INTERRUPT_DISABLE() ; 
                ret = E_OK ; 
                break ;
            case INT_2 : 
                EXTERNAL_INT2_INTERRUPT_DISABLE() ;
                ret = E_OK ; 
               break ;
            default   : ret = E_NOT_OK ; 
        }
    }
    return ret ;
}

/***********************************/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static std_ReturneType Interrupt_INTx_PRIORITY_INIT(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
       switch(int_obj->source)
        {
            case INT_1 : 
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_INT1_LOW_PRIORITY_SET();  
                else
                    EXTERNAL_INT1_HIGH_PRIORITY_SET();
                ret = E_OK ;
                break ;
            case INT_2 : 
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_INT2_LOW_PRIORITY_SET();
                else
                    EXTERNAL_INT2_HIGH_PRIORITY_SET();
                ret = E_OK ;
                break ;
            default :
                ret = E_NOT_OK ; 
        } 
    }
    return ret ;
}
#endif

/***********************************/

static std_ReturneType Interrupt_INTx_EDGE_INIT(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->source)
        {
            case INT_0 : 
                if(int_obj->edge == FALLING)
                    EXTERNAL_INT0_FALLING_EDGE_SET();  
                else
                    EXTERNAL_INT0_RISING_EDGE_SET();
                ret = E_OK ;
                break ;
            case INT_1 : 
                if(int_obj->edge == FALLING)
                    EXTERNAL_INT1_FALLING_EDGE_SET();   
                else
                    EXTERNAL_INT1_RISING_EDGE_SET(); 
                ret = E_OK ;
                break ;
            case INT_2 : 
                if(int_obj->edge == FALLING)
                    EXTERNAL_INT2_FALLING_EDGE_SET(); 
                else
                    EXTERNAL_INT2_RISING_EDGE_SET();
                ret = E_OK ;
                break ;
            default :
                ret = E_NOT_OK ; 
        }   
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_INTx_PIN_INIT(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {        
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_INTx_CLEAR_FLAG(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->source)
        {
            case INT_0 : 
                EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
                ret = E_OK ;
                break ;
            case INT_1 : 
                EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
                ret = E_OK ;
                break ;
            case INT_2 : 
                EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
                ret = E_OK ;
                break ;
            default :
                ret = E_NOT_OK ; 
        }   
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_ENABLE(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->mcu_pin.pin)
        {
            case pin4 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_RBx_LOW_PRIORITY_SET();  
                else if(int_obj->priority == HIGH_PRIORITY)
                    EXTERNAL_RBx_HIGH_PRIORITY_SET();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_RBx_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            case pin5 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_RBx_LOW_PRIORITY_SET();  
                else if(int_obj->priority == HIGH_PRIORITY)
                    EXTERNAL_RBx_HIGH_PRIORITY_SET();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_RBx_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            case pin6 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_RBx_LOW_PRIORITY_SET();  
                else if(int_obj->priority == HIGH_PRIORITY)
                    EXTERNAL_RBx_HIGH_PRIORITY_SET();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_RBx_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            case pin7 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(int_obj->priority == LOW_PRIORITY)
                    EXTERNAL_RBx_LOW_PRIORITY_SET();  
                else if(int_obj->priority == HIGH_PRIORITY)
                    EXTERNAL_RBx_HIGH_PRIORITY_SET();
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                #endif
                EXTERNAL_RBx_INTERRUPT_ENABLE();
                ret = E_OK ; 
                break ;
            default   :
                ret = E_NOT_OK ; 
        }
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_DISABLE(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {        
        EXTERNAL_RBx_INTERRUPT_DISABLE();
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_PRIORITY_INIT(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(int_obj->priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            EXTERNAL_RBx_LOW_PRIORITY_SET();
            ret = E_OK ;
        }
        else if(int_obj->priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            EXTERNAL_RBx_HIGH_PRIORITY_SET();
            ret = E_OK ;
        }
        else{ /* Nothing */ }
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        ret = E_OK ;
        #endif
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_PIN_INIT(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {        
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_CLEAR_FLAG(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {        
        EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType INT0_SET_Interrupt_handler(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_INT0 = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType INT1_SET_Interrupt_handler(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_INT1 = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType INT2_SET_Interrupt_handler(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_INT2 = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_INTx_SET_Interrupt_handler(const interrupt_INTx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->source)
        {
            case INT_0 : 
                ret = INT0_SET_Interrupt_handler(int_obj->external_interrupt);
                break ;
            case INT_1 : 
                ret = INT1_SET_Interrupt_handler(int_obj->external_interrupt);
                break ;
            case INT_2 : 
                ret = INT2_SET_Interrupt_handler(int_obj->external_interrupt);
                break ;
            default :
                ret = E_NOT_OK ; 
        }   
    }
    return ret ;
}

/***********************************/

void INT0_ISR(void)
{
    EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(Interrupt_handler_INT0)
        Interrupt_handler_INT0();
}

/***********************************/

void INT1_ISR(void)
{
    EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(Interrupt_handler_INT1)
        Interrupt_handler_INT1();
}

/***********************************/

void INT2_ISR(void)
{
    EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(Interrupt_handler_INT2)
        Interrupt_handler_INT2();
}

/***********************************/

void RB4_ISR(uint8 RB4_source)
{
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(0 == RB4_source)
    {
        if(Interrupt_handler_RB4_HIGH)
            Interrupt_handler_RB4_HIGH();
        else{ /* Nothing */ }
    }
    else if(1 == RB4_source)
    {
        if(Interrupt_handler_RB4_LOW)
            Interrupt_handler_RB4_LOW();
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

/***********************************/

void RB5_ISR(uint8 RB5_source)
{
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(0 == RB5_source)
    {
        if(Interrupt_handler_RB5_HIGH)
            Interrupt_handler_RB5_HIGH();
        else{ /* Nothing */ }
    }
    else if(1 == RB5_source)
    {
        if(Interrupt_handler_RB5_LOW)
            Interrupt_handler_RB5_LOW();
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

/***********************************/

void RB6_ISR(uint8 RB6_source)
{
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(0 == RB6_source)
    {
        if(Interrupt_handler_RB6_HIGH)
            Interrupt_handler_RB6_HIGH();
        else{ /* Nothing */ }
    }
    else if(1 == RB6_source)
    {
        if(Interrupt_handler_RB6_LOW)
            Interrupt_handler_RB6_LOW();
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

/***********************************/

void RB7_ISR(uint8 RB7_source)
{
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*
     code
    */
    if(0 == RB7_source)
    {
        if(Interrupt_handler_RB7_HIGH)
            Interrupt_handler_RB7_HIGH();
        else{ /* Nothing */ }
    }
    else if(1 == RB7_source)
    {
        if(Interrupt_handler_RB7_LOW)
            Interrupt_handler_RB7_LOW();
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

/***********************************/

static std_ReturneType RB4_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB4_HIGH = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB5_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB5_HIGH = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB6_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB6_HIGH = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB7_SET_Interrupt_handler_HIGH(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB7_HIGH = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB4_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB4_LOW = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB5_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB5_LOW = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB6_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB6_LOW = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType RB7_SET_Interrupt_handler_LOW(void (* Interrupt_handler)(void))
{
    std_ReturneType ret = E_NOT_OK ;
    if(Interrupt_handler == NULL)
        ret = E_NOT_OK ;
    else
    {
        Interrupt_handler_RB7_LOW = Interrupt_handler ;
        ret = E_OK ;
    }
    return ret ;
}

/***********************************/

static std_ReturneType Interrupt_RBx_SET_Interrupt_handler(const interrupt_RBx_t *int_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(int_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        switch(int_obj->mcu_pin.pin)
        {
            case pin4 : 
                ret = RB4_SET_Interrupt_handler_HIGH(int_obj->external_interrupt_HIGH);
                ret = RB4_SET_Interrupt_handler_LOW(int_obj->external_interrupt_LOW);
                ret = E_OK ;
                break ;
            case pin5 : 
                ret = RB5_SET_Interrupt_handler_HIGH(int_obj->external_interrupt_HIGH);
                ret = RB5_SET_Interrupt_handler_LOW(int_obj->external_interrupt_LOW);
                ret = E_OK ;
                break ;
            case pin6 : 
                ret = RB6_SET_Interrupt_handler_HIGH(int_obj->external_interrupt_HIGH);
                ret = RB6_SET_Interrupt_handler_LOW(int_obj->external_interrupt_LOW);
                ret = E_OK ;
                break ;
            case pin7 : 
                ret = RB7_SET_Interrupt_handler_HIGH(int_obj->external_interrupt_HIGH);
                ret = RB7_SET_Interrupt_handler_LOW(int_obj->external_interrupt_LOW);
                ret = E_OK ;
                break ;
            default :
                ret = E_NOT_OK ; 
        }   
    }
    return ret ;
}

/***********************************/