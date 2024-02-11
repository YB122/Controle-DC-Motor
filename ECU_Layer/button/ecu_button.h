/* 
 * File:   ecu_button.h
 * Author: Youssef
 *
 * Created on October 4, 2023, 3:45 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    BUTTON_RELEASED = 0 ,
    BUTTON_PRESSED
}button_status_t;

typedef enum 
{
    ACTIVE_HIGH,
    ACTIVE_LOW
}button_active_t;

typedef struct 
{
    pin_config_t    button_pin   ;
    button_status_t button_status;
    button_active_t button_active;
}button_t;

std_ReturneType button_intialize(const button_t *btn);
std_ReturneType button_read_status(const button_t *btn , button_status_t *btn_status);

#endif	/* ECU_BUTTON_H */

