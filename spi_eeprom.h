#ifndef __SPI_EEPROM_H__
#define __SPI_EEPROM_H__

#include"types.h"
void WriteEnable(void);
void WriteDisable(void);
void spi_eeprom_bytewrite(u16 wBuffAddr,u8 sDat);
u8   spi_eeprom_byteread(u16 rBuffAddr);
void read_eeprom_for_setpoint(void);
void write_eeprom_for_setpoint(char*);

#endif
