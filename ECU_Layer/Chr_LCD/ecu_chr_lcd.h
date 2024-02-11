#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/******************************/

#define lcd_clear                                    0X01
#define lcd_return_home                              0X02
#define lcd_entry_mode_dec_shift_off                 0X04
#define lcd_entry_mode_dec_shift_on                  0X05
#define lcd_entry_mode_inc_shift_off                 0X06
#define lcd_entry_mode_inc_shift_on                  0X07
#define lcd_cursor_move_shift_left                   0X10
#define lcd_cursor_move_shift_right                  0X14
#define lcd_display_shift_right                      0X18
#define lcd_display_shift_left                       0X1C
#define lcd_display_on_underline_off_cursor_off      0X0C
#define lcd_display_on_underline_off_cursor_on       0X0D
#define lcd_display_on_underline_on_cursor_off       0X0E
#define lcd_display_on_underline_on_cursor_on        0X0F
#define lcd_display_off_cursor_off                   0X08
#define lcd_4bit_mode_2_line                         0X28
#define lcd_8bit_mode_2_line                         0X38
#define lcd_cgram_start                              0X40
#define lcd_ddram_start                              0X80
#define row1                                         0X01
#define row2                                         0X02
#define row3                                         0X03
#define row4                                         0X04

/******************************/

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/************** 4bit ****************/

std_ReturneType lcd_4_intialize(chr_lcd_4bit_t *lcd);
std_ReturneType lcd_4_send_command(chr_lcd_4bit_t *lcd , uint8 command);
std_ReturneType lcd_4_send_char_data(chr_lcd_4bit_t *lcd , uint8 data);
std_ReturneType lcd_4_send_char_data_position(chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 data);
std_ReturneType lcd_4_send_string(chr_lcd_4bit_t *lcd , uint8 *str);
std_ReturneType lcd_4_send_string_position(chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 *str);
std_ReturneType lcd_4_send_custome_char(chr_lcd_4bit_t *lcd , 
                                        uint8 row                 , 
                                        uint8 column              , 
                                        const uint8 _ch[]         , 
                                        uint8 mem_pos);

/************** 8bit ****************/

std_ReturneType lcd_8_intialize(chr_lcd_8bit_t *lcd);
std_ReturneType lcd_8_send_command(chr_lcd_8bit_t *lcd , uint8 command);
std_ReturneType lcd_8_send_char_data(chr_lcd_8bit_t *lcd , uint8 data);
std_ReturneType lcd_8_send_char_data_position(chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 data);
std_ReturneType lcd_8_send_string(chr_lcd_8bit_t *lcd , uint8 *str);
std_ReturneType lcd_8_send_string_position(chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 *str);
std_ReturneType lcd_8_send_custome_char(chr_lcd_8bit_t *lcd , 
                                        uint8 row                 , 
                                        uint8 column              , 
                                        const uint8 _ch[]         , 
                                        uint8 mem_pos);

/************************************/

std_ReturneType convert_byte_to_string(uint8 value , uint8 *str)  ;
std_ReturneType convert_short_to_string(uint16 value , uint8 *str);
std_ReturneType convert_int_to_string(uint32 value , uint8 *str)  ;

/************************************/

#endif	/* ECU_CHR_LCD_H */

