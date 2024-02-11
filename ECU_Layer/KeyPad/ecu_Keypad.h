/* 
 * File:   ecu_Keypad.h
 * Author: Youssef
 *
 * Created on October 15, 2023, 6:55 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#define ECU_KEYPAB_ROW     4
#define ECU_KEYPAB_COLUMNS 4

typedef struct 
{
    pin_config_t keypad_row_pins[ECU_KEYPAB_ROW];
    pin_config_t keypad_columns_pins[ECU_KEYPAB_COLUMNS];
}keypad_t;

std_ReturneType keypad_intialize(const keypad_t *_keypad_obj);
std_ReturneType keypad_get_value(const keypad_t *_keypad_obj , uint8 *value);

#endif	/* ECU_KEYPAD_H */

