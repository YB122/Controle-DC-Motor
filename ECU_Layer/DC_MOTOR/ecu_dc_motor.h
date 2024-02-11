/* 
 * File:   ecu_dc_motor.h
 * Author: Youssef
 *
 * Created on October 7, 2023, 11:43 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    DC_MOTOR_OFF_STATUS,
    DC_MOTOR_ON_STATUS
}dc_motor_st;

typedef struct
{
    pin_config_t dc_motor[2];
}dc_motor_t;

std_ReturneType dc_motor_intialize(const dc_motor_t *_dc_motor);
std_ReturneType dc_motor_move_right(const dc_motor_t *_dc_motor);
std_ReturneType dc_motor_move_left(const dc_motor_t *_dc_motor);
std_ReturneType dc_motor_move_toggle(const dc_motor_t *_dc_motor);
std_ReturneType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

