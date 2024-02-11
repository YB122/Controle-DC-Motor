#include "ecu_led.h"

/*****************************/

/**
 * 
 * @param led
 * @return 
 */

std_ReturneType led_initialize(const led_t *led)
{
    std_ReturneType ret = E_OK ;
    pin_config_t pin_obj  = {.port = led->port_name  
                            ,.pin = led->pin_number  
                            ,.direction = OUTPUT 
                            ,.logic = led->status };
    if(NULL == led)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_direction_intialize(&pin_obj);
    }
    
    return ret ;
}

/*****************************/

/**
 * 
 * @param led
 * @return 
 */

std_ReturneType led_turn_on(const led_t *led)
{
    std_ReturneType ret = E_OK ;
    pin_config_t pin_obj  = {.port = led->port_name  
                            ,.pin = led->pin_number  
                            ,.direction = OUTPUT 
                            ,.logic = led->status };
    if(NULL == led)
        ret = E_NOT_OK ;
    else
    {
        gpio_pin_write_logic(&pin_obj , HIGH);
    }
    
    return ret ;
}

/*****************************/

/**
 * 
 * @param led
 * @return 
 */

std_ReturneType led_turn_off(const led_t *led)
{
    std_ReturneType ret = E_OK ;
    pin_config_t pin_obj  = {.port = led->port_name  
                            ,.pin = led->pin_number  
                            ,.direction = OUTPUT 
                            ,.logic = led->status };
    if(NULL == led)
        ret = E_NOT_OK ;
    else
    {
        gpio_pin_write_logic(&pin_obj , LOW);
    }
    
    return ret ;
}

/*****************************/

/**
 * 
 * @param led
 * @return 
 */

std_ReturneType led_turn_toggle(const led_t *led)
{
    std_ReturneType ret = E_OK ;
    pin_config_t pin_obj  = {.port = led->port_name  
                            ,.pin = led->pin_number  
                            ,.direction = OUTPUT 
                            ,.logic = led->status };
    if(NULL == led)
        ret = E_NOT_OK ;
    else
    {
        gpio_pin_toogle_logic(&pin_obj);
    }
    
    return ret ;
}

/*****************************/
