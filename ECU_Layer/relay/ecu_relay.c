#include "ecu_relay.h"

/*************************/

std_ReturneType relay_intialize(const relay_t *_relay)
{
    std_ReturneType ret = E_OK ;
    if(_relay == NULL) 
        ret = E_NOT_OK ;
    else
    {
        pin_config_t pin_obj  = {.port = _relay->relay_port  
                                ,.pin = _relay->relay_pin  
                                ,.direction = OUTPUT
                                ,.logic = _relay->relay_status };
        ret = gpio_pin_direction_intialize(&pin_obj);
    }
    return ret ;
}

/*************************/

std_ReturneType relay_turn_on(const relay_t *_relay)
{
   std_ReturneType ret = E_OK ;
    if(_relay == NULL) 
        ret = E_NOT_OK ;
    else
    {
        pin_config_t pin_obj  = {.port = _relay->relay_port  
                                ,.pin = _relay->relay_pin  
                                ,.direction = OUTPUT
                                ,.logic = _relay->relay_status };
        ret = gpio_pin_write_logic(&pin_obj , HIGH);
    }
    return ret ; 
}

/*************************/

std_ReturneType relay_turn_off(const relay_t *_relay)
{
    std_ReturneType ret = E_OK ;
    if(_relay == NULL) 
        ret = E_NOT_OK ;
    else
    {
        pin_config_t pin_obj  = {.port = _relay->relay_port  
                                ,.pin = _relay->relay_pin  
                                ,.direction = OUTPUT
                                ,.logic = _relay->relay_status };
        ret = gpio_pin_write_logic(&pin_obj , LOW);
    }
    return ret ;
}

/*************************/

std_ReturneType relay_turn_toggle(const relay_t *_relay)
{
    std_ReturneType ret = E_OK ;
    if(_relay == NULL) 
        ret = E_NOT_OK ;
    else
    {
        pin_config_t pin_obj  = {.port = _relay->relay_port  
                                ,.pin = _relay->relay_pin  
                                ,.direction = OUTPUT
                                ,.logic = _relay->relay_status };
        ret = gpio_pin_toogle_logic(&pin_obj);
    }
    return ret ;
}

/*************************/
