#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

#include "../mcal_std_types.h"
#include "../Interrupts/mcal_internal_interrupt.h"

#define Access_Flash_program_memory                        1
#define Access_data_EEPROM_memory                          0
#define Access_Configuration_registers                     1
#define Access_Flash_program_or_data_EEPROM_memory         0
#define Allows_write_cycles_to_Flash_program_data_EEPROM  1
#define Inhibits_write_cycles_to_Flash_program_data_EEPROM 0
#define Write_cycle_to_the_EEPROM_is_not_complete          1 
#define Write_cycle_to_the_EEPROM_is_complete              0
#define initiate_an_EEPROM_read                            1
#define Does_not_initiate_an_EEPROM_read                   0

std_ReturneType DATA_EEPROM_WRITE_BYTE(uint16 BADD , uint8 BDATA);
std_ReturneType DATA_EEPROM_READ_BYTE(uint16 BADD , uint8 *BDATA);

#endif	/* HAL_EEPROM_H */

