/* 
 * File:   ecu_relay.h
 * Author: Youssef
 *
 * Created on October 5, 2023, 6:19 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    RELAY_OFF_STATUS,
    RELAY_ON_STATUS
}RELAY;

typedef struct 
{
    uint8 relay_port   :4;
    uint8 relay_pin    :3;
    uint8 relay_status :1;
}relay_t;

std_ReturneType relay_intialize(const relay_t *_relay);
std_ReturneType relay_turn_on(const relay_t *_relay);
std_ReturneType relay_turn_off(const relay_t *_relay);
std_ReturneType relay_turn_toggle(const relay_t *_relay);

#endif	/* ECU_RELAY_H */

