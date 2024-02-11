#include "ecu_chr_lcd.h"

/***************************************/

static std_ReturneType lcd_send_4bit(chr_lcd_4bit_t *lcd , uint8 command);
static std_ReturneType lcd_4bit_send_enable_signale(chr_lcd_4bit_t *lcd);
static std_ReturneType lcd_8bit_send_enable_signale(chr_lcd_8bit_t *lcd);
static std_ReturneType lcd_8bit_set_cursor(chr_lcd_8bit_t *lcd , uint8 row , uint8 column);
static std_ReturneType lcd_4bit_set_cursor(chr_lcd_4bit_t *lcd , uint8 row , uint8 column);

/***************************************/

std_ReturneType lcd_4_intialize(chr_lcd_4bit_t *lcd)
{
    std_ReturneType ret = E_OK ;
    uint8 l_pins = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_pins = 0 ; l_pins < 4 ; l_pins++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_pins]));
        }     
        DM(20);
        ret = lcd_4_send_command(lcd , lcd_8bit_mode_2_line);
        DM(5);
        ret = lcd_4_send_command(lcd , lcd_8bit_mode_2_line);
        DU(150);
        ret = lcd_4_send_command(lcd , lcd_8bit_mode_2_line);
        ret = lcd_4_send_command(lcd , lcd_clear);
        ret = lcd_4_send_command(lcd , lcd_return_home);
        ret = lcd_4_send_command(lcd , lcd_entry_mode_inc_shift_off);
        ret = lcd_4_send_command(lcd , lcd_display_on_underline_off_cursor_off);
        ret = lcd_4_send_command(lcd , lcd_4bit_mode_2_line);
        ret = lcd_4_send_command(lcd , lcd_ddram_start);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_command(chr_lcd_4bit_t *lcd , uint8 command)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        ret = lcd_send_4bit(lcd , command >> 4);
        ret = lcd_4bit_send_enable_signale(lcd);
        ret = lcd_send_4bit(lcd , command);
        ret = lcd_4bit_send_enable_signale(lcd);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_char_data(chr_lcd_4bit_t *lcd , uint8 data)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        ret = lcd_send_4bit(lcd , data >> 4);
        ret = lcd_4bit_send_enable_signale(lcd);
        ret = lcd_send_4bit(lcd , data);
        ret = lcd_4bit_send_enable_signale(lcd);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_char_data_position(chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 data)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        ret = lcd_4_send_char_data(lcd , data);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_string(chr_lcd_4bit_t *lcd , uint8 *str)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        while(*str)
        {
            ret = lcd_4_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_string_position(chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 *str)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        while(*str)
        {
            ret = lcd_4_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_4_send_custome_char(chr_lcd_4bit_t *lcd , 
                                        uint8 row                 , 
                                        uint8 column              , 
                                        const uint8 _ch[]         , 
                                        uint8 mem_pos)
{
    std_ReturneType ret = E_OK ;
    uint8 counter = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_4_send_command(lcd , lcd_cgram_start + (mem_pos * 8));
        for(counter = 0 ; counter < 8 ; counter++)
        {
            ret = lcd_4_send_char_data_position(lcd , row , column , _ch[counter]);          
        }
        ret = lcd_4_send_char_data_position(lcd , row , column , mem_pos);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_intialize(chr_lcd_8bit_t *lcd)
{
    std_ReturneType ret = E_OK ;
    uint8 l_pins = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_pins = 0 ; l_pins < 8 ; l_pins++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_pins]));
        } 
        DM(20);
        ret = lcd_8_send_command(lcd , lcd_8bit_mode_2_line);
        DM(5);
        ret = lcd_8_send_command(lcd , lcd_8bit_mode_2_line);
        DU(150);
        ret = lcd_8_send_command(lcd , lcd_8bit_mode_2_line);
        ret = lcd_8_send_command(lcd , lcd_clear);
        ret = lcd_8_send_command(lcd , lcd_return_home);
        ret = lcd_8_send_command(lcd , lcd_entry_mode_inc_shift_off);
        ret = lcd_8_send_command(lcd , lcd_display_on_underline_off_cursor_off);
        ret = lcd_8_send_command(lcd , lcd_8bit_mode_2_line);
        ret = lcd_8_send_command(lcd , lcd_ddram_start);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_command(chr_lcd_8bit_t *lcd , uint8 command)
{
    std_ReturneType ret = E_OK ;
    uint8 l_counter = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]) , (command >> l_counter) & (uint8)0X01);
        }
        ret = lcd_8bit_send_enable_signale(lcd);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_char_data(chr_lcd_8bit_t *lcd , uint8 data)
{
    std_ReturneType ret = E_OK ;
    uint8 l_counter = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]) , (data >> l_counter) & (uint8)0X01);
        }
        ret = lcd_8bit_send_enable_signale(lcd);
        
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_char_data_position(chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 data)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_8bit_set_cursor(lcd , row , column);
        ret = lcd_8_send_char_data(lcd , data);
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_string(chr_lcd_8bit_t *lcd , uint8 *str)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        while(*str)
        {
            ret = lcd_8_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_string_position(chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 *str)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_8bit_set_cursor(lcd , row , column);
        while(*str)
        {
            ret = lcd_8_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

/***************************************/

std_ReturneType lcd_8_send_custome_char(chr_lcd_8bit_t *lcd , 
                                        uint8 row                 , 
                                        uint8 column              , 
                                        const uint8 _ch[]         , 
                                        uint8 mem_pos)
{
    std_ReturneType ret = E_OK ;
    uint8 counter = 0 ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = lcd_8_send_command(lcd , lcd_cgram_start + (mem_pos * 8));
        for(counter = 0 ; counter < 8 ; counter++)
        {
            ret = lcd_8_send_char_data_position(lcd , row , column , _ch[counter]);          
        }
        ret = lcd_8_send_char_data_position(lcd , row , column , mem_pos);
    }
    return ret ;
}

/***************************************/

std_ReturneType convert_byte_to_string(uint8 value , uint8 *str)  
{
    std_ReturneType ret = E_OK ;
    if(NULL == str)
        ret = E_NOT_OK ;
    else
    {
        memset(str , '\0' , 4);
        sprintf((char *)str , "%i" , value);
    }
    return ret ;
}

/***************************************/

std_ReturneType convert_short_to_string(uint16 value , uint8 *str)
{
    std_ReturneType ret = E_OK ;
    if(NULL == str)
        ret = E_NOT_OK ;
    else
    {
        memset(str , '\0' , 6);
        sprintf((char *)str , "%i" , value);
    }
    return ret ;
}

/***************************************/

std_ReturneType convert_int_to_string(uint32 value , uint8 *str)  
{
    std_ReturneType ret = E_OK ;
    if(NULL == str)
        ret = E_NOT_OK ;
    else
    {
        memset(str , '\0' ,11);
        sprintf((char *)str , "%i" , value);
    }
    return ret ;
}

/***************************************/

static std_ReturneType lcd_send_4bit(chr_lcd_4bit_t *lcd , uint8 command)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (command >> 0) & (uint8)0X01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (command >> 1) & (uint8)0X01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , (command >> 2) & (uint8)0X01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , (command >> 3) & (uint8)0X01);
        ret = E_OK ;
    }
    return ret ;
}

/***************************************/

static std_ReturneType lcd_4bit_send_enable_signale(chr_lcd_4bit_t *lcd)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , HIGH);
        DU(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , LOW);
    }
    return ret ;
}

/***************************************/

static std_ReturneType lcd_8bit_send_enable_signale(chr_lcd_8bit_t *lcd)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , HIGH);
        DU(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) ,  LOW);
    }
    return ret ;
}

/***************************************/

static std_ReturneType lcd_8bit_set_cursor(chr_lcd_8bit_t *lcd , uint8 row , uint8 column)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        column--;
        switch (row)
        {
            case row1 :
                ret = lcd_8_send_command(lcd , ((0X80) + column));
                break;
            case row2 :
                ret = lcd_8_send_command(lcd , ((0XC0) + column));
                break;
            case row3 :
                ret = lcd_8_send_command(lcd , ((0X94) + column));
                break;
            case row4 :
                ret = lcd_8_send_command(lcd , ((0XD4) + column));
                break;
            default :
                break;
        }
    }
    return ret ;
}

/***************************************/

static std_ReturneType lcd_4bit_set_cursor(chr_lcd_4bit_t *lcd , uint8 row , uint8 column)
{
    std_ReturneType ret = E_OK ;
    if(NULL == lcd)
        ret = E_NOT_OK ;
    else
    {
        column--;
        switch (row)
        {
            case row1 :
                ret = lcd_4_send_command(lcd , ((0X80) + column));
                break;
            case row2 :
                ret = lcd_4_send_command(lcd , ((0XC0) + column));
                break;
            case row3 :
                ret = lcd_4_send_command(lcd , ((0X94) + column));
                break;
            case row4 :
                ret = lcd_4_send_command(lcd , ((0XD4) + column));
                break;
            default :
                break;
        }
    }
    return ret ;
}

/***************************************/
