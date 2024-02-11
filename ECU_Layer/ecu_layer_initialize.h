#ifndef ECU_LAYER_INITIALIZE_H
#define	ECU_LAYER_INITIALIZE_H

#define _XTAL_FREQ 8000000

/**************************************/

#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "relay/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_segment.h"
#include "KeyPad/ecu_Keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"
#include "../MCAL_Layer/Interrupts/mcal_external_interrupt.h"
#include "../MCAL_Layer/Interrupts/mcal_internal_interrupt.h"
#include "../MCAL_Layer/Interrupts/mcal_interrupt_manger.h"
#include "../MCAL_Layer/EEPROM/hal_eeprom.h"
#include "../MCAL_Layer/ADC/hal_adc.h"

/**************************************/

void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INITIALIZE_H */

