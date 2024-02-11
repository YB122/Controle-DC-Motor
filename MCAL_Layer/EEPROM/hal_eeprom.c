#include "hal_eeprom.h"

/**************************************/

std_ReturneType DATA_EEPROM_WRITE_BYTE(uint16 BADD , uint8 BDATA)
{
    std_ReturneType ret = E_OK ;
    uint8 GLOBAL_INTERRUPT_STATUS = INTCONbits.GIE ;
    EEADRH = ((uint8)(BADD >> 8) & (0X03)) ;
    EEADR = ((uint8)(BADD) & (0XFF));
    EEDATA = BDATA ;
    EECON1bits.EEPGD = Access_data_EEPROM_memory ;
    EECON1bits.CFGS = Access_Flash_program_or_data_EEPROM_memory ;
    EECON1bits.WREN = Allows_write_cycles_to_Flash_program_data_EEPROM ;
    (INTCONbits.GIE = 0);
    EECON2 = 0X55 ;
    EECON2 = 0XAA ;
    EECON1bits.WR = Write_cycle_to_the_EEPROM_is_not_complete ;
    while(EECON1bits.WR);
    EECON1bits.WREN = Inhibits_write_cycles_to_Flash_program_data_EEPROM ;
    INTCONbits.GIE = GLOBAL_INTERRUPT_STATUS ;
    return ret ;
}

/**************************************/

std_ReturneType DATA_EEPROM_READ_BYTE(uint16 BADD , uint8 *BDATA)
{
    std_ReturneType ret = E_NOT_OK ;
    if(BDATA == NULL)
        ret = E_NOT_OK ;
    else
    {
        EEADRH = ((uint8)(BADD >> 8) & (0X03)) ;
        EEADR = ((uint8)(BADD) & (0XFF));
        EECON1bits.EEPGD = Access_data_EEPROM_memory ;
        EECON1bits.CFGS = Access_Flash_program_or_data_EEPROM_memory ;
        EECON1bits.RD = initiate_an_EEPROM_read ;
        NOP();
        NOP();
        *BDATA = EEDATA ;
        ret = E_OK ;
    }  
    return ret ;
}

/**************************************/