#ifndef APPLICATION_H
#define	APPLICATION_H

#include "ECU_Layer/ecu_layer_initialize.h"
#define _XTAL_FREQ 8000000
#define loop 1

extern dc_motor_t motor_1;
extern led_t led_green;
extern led_t led_red;
extern chr_lcd_4bit_t lcd_1;
extern keypad_t KeyPad1;

/*
extern led_t led0 ;
extern led_t led1 ;
extern led_t led2 ;
extern led_t led3 ;
extern interrupt_RBx_t rb4_int_obj ;
*/

#endif	/* APPLICATION_H */
