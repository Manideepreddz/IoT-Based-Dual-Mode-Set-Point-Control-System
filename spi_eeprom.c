#include "spi.h"
#include "spi_eeprom_defines.h"
#include "spi_defines.h"
#include "spi_eeprom.h"
#include "delay.h"
#include "lcd.h"
#include <lpc21xx.h>

void WriteEnable(void)
{
	IOCLR0=1<<CS_0_7;
	spi(WREN);
	IOSET0=1<<CS_0_7;
}
void WriteDisable(void)
{
	IOCLR0=1<<CS_0_7;
	spi(WRDI);
	IOSET0=1<<CS_0_7;
}
void spi_eeprom_bytewrite(u16 wBuffAddr,u8 sDat)
{
	WriteEnable();
	IOCLR0=1<<CS_0_7;
	spi(WRITE);
	spi(wBuffAddr);
	spi(wBuffAddr>>8);
	spi(sDat);
	IOSET0=1<<CS_0_7;
	delay_ms(5);
	WriteDisable();
	/*CmdLCD(0x01);
	StrLCD("Sending");
	CmdLCD(GOTO_LINE2);
	CharLCD(sDat);
	delay_ms(500);*/
}
u8   spi_eeprom_byteread(u16 rBuffAddr)
{
	u8 rDat;
	IOCLR0=1<<CS_0_7;
	spi(READ);
	spi(rBuffAddr);
	spi(rBuffAddr>>8);
	rDat=spi(0x00);
	IOSET0=1<<CS_0_7;
	/*CmdLCD(0x01);
	StrLCD("recevining");
	CmdLCD(GOTO_LINE2);
	CharLCD(rDat);
	delay_ms(500);*/
	return rDat;
}
