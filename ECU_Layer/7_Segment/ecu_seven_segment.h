/* 
 * File:   ecu_seven_segment.h
 * Author: Youssef
 *
 * Created on October 15, 2023, 3:07 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    SEGMENT_COMMON_ANODE  ,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct 
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

std_ReturneType seven_segment_intialize(const segment_t *seg);
std_ReturneType seven_segment_write_number(const segment_t *seg , uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

