#include "ecu_seven_segment.h"

/**********************************/

std_ReturneType seven_segment_intialize(const segment_t *seg)
{
    std_ReturneType ret = E_OK ;
    if(seg == NULL) 
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_direction_intialize(&(seg->segment_pins[0]));
        ret = gpio_pin_direction_intialize(&(seg->segment_pins[1]));
        ret = gpio_pin_direction_intialize(&(seg->segment_pins[2]));
        ret = gpio_pin_direction_intialize(&(seg->segment_pins[3]));      
    }
    return ret ;
}

/**********************************/

std_ReturneType seven_segment_write_number(const segment_t *seg , uint8 number)
{
    std_ReturneType ret = E_OK ;
    if((seg == NULL) && (number > 9))
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[0]) , ((number & 0x01)) >> 0);
        ret = gpio_pin_write_logic(&(seg->segment_pins[1]) , ((number & 0x02)) >> 1);
        ret = gpio_pin_write_logic(&(seg->segment_pins[2]) , ((number & 0x04)) >> 2);
        ret = gpio_pin_write_logic(&(seg->segment_pins[3]) , ((number & 0x08)) >> 3);
    }
    return ret ;
}

/**********************************/