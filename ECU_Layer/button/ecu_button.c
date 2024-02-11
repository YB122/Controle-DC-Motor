#include "ecu_button.h"

/*****************************/

/**
 * 
 * @param btn
 * @return 
 */

std_ReturneType button_intialize(const button_t *btn)
{
    std_ReturneType ret = E_OK ;
    if(btn == NULL) 
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
    return ret ;
}

/*****************************/

/**
 * 
 * @param btn
 * @return 
 */

std_ReturneType button_read_status(const button_t *btn , button_status_t *btn_status)
{
    std_ReturneType ret = E_OK ;
    logic_status pin_logic = LOW ;
    if((btn == NULL) || (btn_status == NULL)) 
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_read_logic(&(btn->button_pin) , (uint8 *)(&pin_logic));
        if(ACTIVE_HIGH == (btn->button_active))
        {
            if(HIGH == pin_logic)
            {
                *btn_status = BUTTON_PRESSED ;
            }
            else
            {
                *btn_status = BUTTON_RELEASED ;
            }
        }
        else if ((btn->button_active) == ACTIVE_LOW)
        {
            if(LOW == pin_logic)
            {
                *btn_status = BUTTON_PRESSED ;
            }
            else
            {
                *btn_status = BUTTON_RELEASED ;
            }
        }
    }
    return ret ;
}

/*****************************/
