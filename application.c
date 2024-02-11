#include "application.h"

std_ReturneType ret = E_OK ;
dc_motor_t motor_1;
led_t led_green;
led_t led_red;
chr_lcd_4bit_t lcd_1;
keypad_t KeyPad1;

uint8 result_txt[6] , counter_pass = 4 , value = (uint8)NULL , counter_value = 0 , flag = 1 , pass[6] = "1111" , YourPass[6];
uint8 forsa = 3 ;
uint16 result = 0 ;

int main(void)
{ 
    ecu_layer_initialize();
    ret = lcd_4_send_command(&lcd_1 , lcd_clear);
    DM(100);
    ret = lcd_4_send_string_position(&lcd_1 , 1 , 2 , (uint8*)"Welcome Youssef");
    DM(1500);
    ret = lcd_4_send_command(&lcd_1 , lcd_clear);
    DM(100);   
    while(loop)
    {
        while(flag)
        {
            while(forsa)
            {
                ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"Write your pass");
                counter_pass = 4;
                counter_value = 1;
                result = 0 ;
                while(counter_pass)
                {
                    while(!value)
                    {
                       ret = keypad_get_value(&KeyPad1 , &value); 
                    } 
                    result = (result*10)+(value-48);
                    ret = lcd_4_send_string_position(&lcd_1 , 2 , counter_value , (uint8*)"*");
                    value = (uint8)NULL ;
                    counter_value++;
                    counter_pass--;
                }
                DM(500);
                ret = convert_short_to_string(result , YourPass);
                flag = (uint8)strcmp((char*)YourPass , (char*)pass);
                if(flag == 0)
                {
                    ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                    DM(100);
                    ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"Correct Pass");
                    ret = led_turn_on(&led_green);
                    DM(2000);
                    break;
                }         
                else
                {
                    forsa--;
                    if(forsa == 0)
                    {
                        
                    }
                    else
                    {
                        ret = led_turn_on(&led_red);
                        ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                        DM(100);
                        ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"Wrong Pass");
                        DM(2000);
                        ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                        DM(100);
                        ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"you have   tries");
                        ret = convert_byte_to_string(forsa , result_txt);
                        ret = lcd_4_send_string_position(&lcd_1 , 1 , 10 , result_txt);
                        DM(2000);          
                        ret = led_turn_off(&led_red);
                        ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                        DM(100);
                    }   
                }               
            }
            if(forsa)
            {/* Nothing */}
            else
            {
                ret = led_turn_on(&led_red);
                ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                DM(100);
                ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"you use 3 tries");
                ret = lcd_4_send_string_position(&lcd_1 , 2 , 1 , (uint8*)"you are in block");
                DM(5000);
                forsa = 3;   
                ret = lcd_4_send_command(&lcd_1 , lcd_clear);
                DM(100);      
                ret = led_turn_off(&led_red);
            }  
        }
        ret = lcd_4_send_command(&lcd_1 , lcd_clear);
        DM(100);           
        ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"you can use ");
        ret = lcd_4_send_string_position(&lcd_1 , 2 , 1 , (uint8*)"motor ");
        DM(2000);
        while(loop)
        {
            value = (uint8)NULL ;         
            ret = lcd_4_send_command(&lcd_1 , lcd_clear);
            DM(100);
            ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"1-right 2-left");
            ret = lcd_4_send_string_position(&lcd_1 , 2 , 1 , (uint8*)"3-toggle 4-stop");
            while(!value)
            {
               ret = keypad_get_value(&KeyPad1 , &value); 
            } 
            ret = lcd_4_send_command(&lcd_1 , lcd_clear);
            DM(100);
            value -= 48;
            switch(value)
            {
                case 1 :
                    ret = dc_motor_stop(&motor_1);
                    DM(300);
                    ret = dc_motor_move_right(&motor_1);  
                    ret = led_turn_on(&led_green);
                    break;
                case 2 :
                    ret = dc_motor_stop(&motor_1);
                    DM(300);
                    ret = dc_motor_move_left(&motor_1);
                    ret = led_turn_on(&led_green);
                    break;
                case 3 :
                    ret = dc_motor_move_toggle(&motor_1);
                    ret = led_turn_on(&led_green);
                    break;
                case 4 :
                    ret = dc_motor_stop(&motor_1);
                    ret = led_turn_off(&led_green);
                    DM(1000);
                    break;
                default :
                    ret = lcd_4_send_string_position(&lcd_1 , 1 , 1 , (uint8*)"choose 1->4");
                    DM(1000);
                    break;
            }                         
        }      
    }
    return (EXIT_SUCCESS);
}