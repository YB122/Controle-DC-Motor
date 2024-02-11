#include "ecu_Keypad.h"

static const uint8 btn_values[ECU_KEYPAB_ROW][ECU_KEYPAB_COLUMNS] = 
{
    {'7' , '8' , '9' , '/'},
    {'4' , '5' , '6' , '*'},
    {'1' , '2' , '3' , '+'},
    {'%' , '0' , '=' , '-'}
};

/******************************/

std_ReturneType keypad_intialize(const keypad_t *_keypad_obj)
{
    std_ReturneType ret = E_OK ;
    uint8 rows_counter = 0 , columns_counter = 0 ;
    if(NULL == _keypad_obj)
        ret = E_NOT_OK ;
    else
    {
        for(rows_counter = 0 ; rows_counter < ECU_KEYPAB_ROW ; rows_counter++)
        {
            ret = gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0 ; columns_counter < ECU_KEYPAB_COLUMNS ; columns_counter++)
        {
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));   
        } 
    }
    return ret ;
}

/******************************/

std_ReturneType keypad_get_value(const keypad_t *_keypad_obj , uint8 *value)
{
    std_ReturneType ret = E_OK ;
    uint8 rows_counter = 0 , columns_counter = 0 , counter = 0 , cloumn_logic = 0 ;
    if((NULL == _keypad_obj) || (NULL == value))
        ret = E_NOT_OK ;
    else
    {
        for(rows_counter = 0 ; rows_counter < ECU_KEYPAB_ROW ; rows_counter++)
        {
            for(counter = 0 ; counter < ECU_KEYPAB_ROW ; counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[counter]) , LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[rows_counter]) , HIGH);
            __delay_ms(50);
            for(columns_counter = 0 ; columns_counter < ECU_KEYPAB_COLUMNS ; columns_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[columns_counter]) , &cloumn_logic);
                if(HIGH == cloumn_logic)
                {
                    *value = btn_values[rows_counter][columns_counter];
                }
            }
        }
    }
    return ret ;
}

/******************************/

