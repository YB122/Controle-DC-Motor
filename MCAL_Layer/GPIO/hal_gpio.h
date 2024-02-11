/* 
 * File:   hal_gpio.h
 * Author: Youssef
 *
 * Created on September 27, 2023, 12:31 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
//#include <proc/pic18f4620.h>
#include "../device_config.h"
#include "../mcal_std_types.h"

#define port_bin_max 8
#define port_max 5

#define SELF_LATC_REG   ((volatile SELF_LATC *)0xF8B)
#define D_SELF_LATC_REG (*((volatile SELF_LATC *)0xF8B))

#define SELF_SELF_SSPCON_REG   ((volatile SELF_SSPCON *)0xF8B)
#define D_SELF_SELF_SSPCON_REG (*((volatile SELF_SSPCON *)0xF8B))

#define HWREG8(_x) (*((volatile uint8 *)(_x)))
#define youssef_LATC  (HWREG8(0xF8B))
#define youssef_TRISC (HWREG8(0xF94))
#define youssef_LATA  (HWREG8(0xF89))
#define youssef_TRISA (HWREG8(0xF92))
#define youssef_LATB  (HWREG8(0xF8A))
#define youssef_TRISB (HWREG8(0xF93))
#define SET_BIT(REG_ADDR,BIT_POSN)    (HWREG8(REG_ADDR) |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG_ADDR,BIT_POSN)  (HWREG8(REG_ADDR) &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG_ADDR,BIT_POSN) (HWREG8(REG_ADDR) ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG_ADDR,BIT_POSN)   ((HWREG8(REG_ADDR) >> BIT_POSN) & BIT_MASK)

typedef enum
{
    LOW,
    HIGH
}logic_status;

typedef enum
{
    OUTPUT,
    INPUT        
}direction_t;

typedef enum
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7
}pin_index_t;

typedef enum
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct
{
    uint8 port      : 3 ;
    uint8 pin       : 3 ;
    uint8 direction : 1 ;
    uint8 logic     : 1;
}pin_config_t;

/********************************/

std_ReturneType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
std_ReturneType gpio_pin_direction_status(const pin_config_t *_pin_config , direction_t *direction_status);
std_ReturneType gpio_pin_write_logic(const pin_config_t *_pin_config , uint8 logic);
std_ReturneType gpio_pin_read_logic(const pin_config_t *_pin_config , uint8 *logic);
std_ReturneType gpio_pin_toogle_logic(const pin_config_t *_pin_config);
std_ReturneType gpio_pin_intialize(const pin_config_t *_pin_config);

/********************************/

std_ReturneType gpio_port_direction_intialize(port_index_t port , uint8 direction_t);
std_ReturneType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status);
std_ReturneType gpio_port_write_logic(port_index_t port , uint8 logic);
std_ReturneType gpio_port_read_logic(port_index_t port , uint8 *logic);
std_ReturneType gpio_port_toogle_logic(port_index_t port);

/********************************/

#endif	/* HAL_GPIO_H */

