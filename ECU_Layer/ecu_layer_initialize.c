#include "ecu_layer_initialize.h"

/******************************/

chr_lcd_4bit_t lcd_1 = 
{
    .lcd_rs.port = PORTC_INDEX ,
    .lcd_rs.pin  = pin0        ,
    .lcd_rs.direction = OUTPUT ,
    .lcd_rs.logic = LOW        ,
    .lcd_en.port = PORTC_INDEX ,
    .lcd_en.pin  = pin1        ,
    .lcd_en.direction = OUTPUT ,
    .lcd_en.logic = LOW        ,
    .lcd_data[0].port = PORTC_INDEX ,
    .lcd_data[0].pin = pin2 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTC_INDEX ,
    .lcd_data[1].pin = pin3 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTD_INDEX ,
    .lcd_data[2].pin = pin0 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTD_INDEX ,
    .lcd_data[3].pin = pin1 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW 
};

/******************************/

keypad_t KeyPad1 =
{
    .keypad_row_pins[0].port = PORTB_INDEX,
    .keypad_row_pins[0].direction = OUTPUT,
    .keypad_row_pins[0].logic = LOW       ,
    .keypad_row_pins[0].pin = pin7        ,
    .keypad_row_pins[1].port = PORTB_INDEX,
    .keypad_row_pins[1].direction = OUTPUT,
    .keypad_row_pins[1].logic = LOW       ,
    .keypad_row_pins[1].pin = pin6        ,
    .keypad_row_pins[2].port = PORTB_INDEX,
    .keypad_row_pins[2].direction = OUTPUT,
    .keypad_row_pins[2].logic = LOW       ,
    .keypad_row_pins[2].pin = pin5        ,
    .keypad_row_pins[3].port = PORTB_INDEX,
    .keypad_row_pins[3].direction = OUTPUT,
    .keypad_row_pins[3].logic = LOW       ,
    .keypad_row_pins[3].pin = pin4        ,
    .keypad_columns_pins[0].port = PORTB_INDEX,
    .keypad_columns_pins[0].direction = INPUT     ,
    .keypad_columns_pins[0].logic = LOW           ,
    .keypad_columns_pins[0].pin = pin3            ,
    .keypad_columns_pins[1].port = PORTB_INDEX    ,
    .keypad_columns_pins[1].direction = INPUT     ,
    .keypad_columns_pins[1].logic = LOW           ,
    .keypad_columns_pins[1].pin = pin2            ,
    .keypad_columns_pins[2].port = PORTB_INDEX    ,
    .keypad_columns_pins[2].direction = INPUT     ,
    .keypad_columns_pins[2].logic = LOW           ,
    .keypad_columns_pins[2].pin = pin1            ,
    .keypad_columns_pins[3].port = PORTB_INDEX    ,
    .keypad_columns_pins[3].direction = INPUT     ,
    .keypad_columns_pins[3].logic = LOW           ,
    .keypad_columns_pins[3].pin = pin0                
};

/******************************/

led_t led_red =
{
    .status = LED_OFF ,
    .pin_number = pin3 ,
    .port_name = PORTD_INDEX
};

/******************************/

led_t led_green =
{
    .status = LED_OFF ,
    .pin_number = pin2 ,
    .port_name = PORTD_INDEX
};

/******************************/

dc_motor_t motor_1 =
{
    .dc_motor[0].direction = OUTPUT,
    .dc_motor[0].pin = pin0,
    .dc_motor[0].port = PORTA_INDEX,
    .dc_motor[0].logic = LOW,
    .dc_motor[1].direction = OUTPUT,
    .dc_motor[1].pin = pin1,
    .dc_motor[1].port = PORTA_INDEX,
    .dc_motor[1].logic = LOW,
};

/******************************/

void ecu_layer_initialize(void)
{  
    std_ReturneType ret = E_OK ;
    ret = dc_motor_intialize(&motor_1);
    ret = led_initialize(&led_green);
    ret = led_initialize(&led_red);
    ret = lcd_4_intialize(&lcd_1);
    ret = keypad_intialize(&KeyPad1);
}

/******************************/
