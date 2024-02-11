/* 
 * File:   ecu_led.h
 * Author: Youssef
 *
 * Created on September 27, 2023, 12:59 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    LED_OFF,
    LED_ON
}led_status;

typedef struct
{
    uint8 port_name     :4;
    uint8 pin_number    :3;
    uint8 status        :1;
}led_t;


std_ReturneType led_initialize(const led_t *led);
std_ReturneType led_turn_on(const led_t *led);
std_ReturneType led_turn_off(const led_t *led);
std_ReturneType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

