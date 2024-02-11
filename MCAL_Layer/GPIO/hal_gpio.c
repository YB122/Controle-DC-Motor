#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA , &TRISB , &TRISC , &TRISD , &TRISE};
volatile uint8 *lat_register[] = {&LATA , &LATB , &LATC , &LATD , &LATE};
volatile uint8 *port_register[] = {&PORTA , &PORTB , &PORTC , &PORTD , &PORTD};

/********************************/
/**
 * 
 * @param _pin_config
 * @return 
 */
std_ReturneType gpio_pin_direction_intialize(const pin_config_t *_pin_config)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (_pin_config->pin > port_bin_max-1)) 
        ret = E_NOT_OK ;
    else
    {
        switch(_pin_config->direction)
        {
            case OUTPUT :
                CLEAR_BIT(tris_register[_pin_config->port] , _pin_config->pin);
                break;
            case INPUT:
                SET_BIT  (tris_register[_pin_config->port] , _pin_config->pin);
                break;
            default :
                ret = E_NOT_OK ;
        }
    }   
    return ret ;
}

/********************************/
/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
std_ReturneType gpio_pin_direction_status(const pin_config_t *_pin_config , direction_t *direction_status)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (direction_status == NULL) || (_pin_config->pin > port_bin_max-1))
        ret = E_NOT_OK ;
    else
    {
        *direction_status = READ_BIT(tris_register[_pin_config->port] , _pin_config->pin);
    }
    return ret ;
}
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
/********************************/

std_ReturneType gpio_pin_write_logic(const pin_config_t *_pin_config , uint8 logic)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (_pin_config->pin > port_bin_max-1)) 
        ret = E_NOT_OK ;
    else
    {
        switch(logic)
        {
            case LOW :
                CLEAR_BIT(lat_register[_pin_config->port] , _pin_config->pin);
                break;
            case HIGH:
                SET_BIT(lat_register[_pin_config->port] , _pin_config->pin);
                break;
            default :
                ret = E_NOT_OK ;
        }
    }
    return ret ;
}
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
/********************************/

std_ReturneType gpio_pin_read_logic(const pin_config_t *_pin_config , uint8 *logic)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (logic == NULL) || (_pin_config->pin > port_bin_max-1))
        ret = E_NOT_OK ;
    else
    {
        *logic = READ_BIT(port_register[_pin_config->port] , _pin_config->pin);
    }
    return ret ;
}
/**
 * 
 * @param _pin_config
 * @return 
 */
/********************************/

std_ReturneType gpio_pin_toogle_logic(const pin_config_t *_pin_config)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (_pin_config->pin > port_bin_max-1)) 
        ret = E_NOT_OK ;
    else
    {
        TOGGLE_BIT(lat_register[_pin_config->port] , _pin_config->pin);
    }
    return ret ;
}
/**
 * 
 * @param _pin_config
 * @return 
 */
/********************************/

std_ReturneType gpio_pin_intialize(const pin_config_t *_pin_config)
{
    std_ReturneType ret = E_OK ;
    if((_pin_config == NULL) || (_pin_config->pin > port_bin_max-1)) 
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_direction_intialize(_pin_config);
        if(_pin_config->direction == OUTPUT)
        {   
            ret = gpio_pin_write_logic(_pin_config , _pin_config->logic);
        }    
    }
    return ret ;
}
/**
 * 
 * @param port
 * @param direction_t
 * @return 
 */
/********************************/

std_ReturneType gpio_port_direction_intialize(port_index_t port , uint8 direction_t)
{
    std_ReturneType ret = E_OK ;
    if(port > port_max-1)
        ret = E_NOT_OK ;
    else
    {
        *tris_register[port] = direction_t ;
    }
    return ret ;
}
/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
/********************************/

std_ReturneType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status)
{
    std_ReturneType ret = E_OK ;
    if((direction_status == NULL) || (port > port_max-1))
        ret = E_NOT_OK ;
    else
    {
        *direction_status = *tris_register[port] ;
    }
    return ret ;
}
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
/********************************/

std_ReturneType gpio_port_write_logic(port_index_t port , uint8 logic)
{
    std_ReturneType ret = E_OK ;
    if(port > port_max-1)
         ret = E_NOT_OK;
    else
    {
        *lat_register[port] = logic ;
    }
    
    return ret ;
}
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
/********************************/

std_ReturneType gpio_port_read_logic(port_index_t port , uint8 *logic)
{
    std_ReturneType ret = E_OK ;
    if((NULL == logic) || (port > port_max-1))
        ret = E_NOT_OK;
    else
    {
        *logic = *port_register[port];
    }
    return ret ;
}
/**
 * 
 * @param port
 * @return 
 */
/********************************/

std_ReturneType gpio_port_toogle_logic(port_index_t port)
{
    std_ReturneType ret = E_OK ;
    if(port > port_max-1)
        ret = E_NOT_OK;
    else
    {
        *lat_register[port] ^= 0xFF ;
    }
    return ret ;
}

/********************************/
