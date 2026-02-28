#include "spi.h"
#include "spi_eeprom_defines.h"
#include "spi_defines.h"
#include <lpc21xx.h>
void SPI_Init(void)
{
	PINSEL0|=SCL_0_4|MISO_0_5|MOSI_0_6;
	IOSET0=1<<CS_0_7;
	IODIR0|=1<<CS_0_7;
	if(SPI_DIVISER>=8)
	{
		if(SPI_DIVISER%2==0)
			S0SPCCR=SPI_DIVISER;
		else
			S0SPCCR=SPI_DIVISER+1;
	}
	S0SPCR=1<<CPOL_BIT|1<<CPHA_BIT|1<<MSTR_BIT;
}
u8   spi(u8 sByte)
{
	u8 rByte;
	S0SPDR=sByte;
	while(((S0SPSR>>SPIF_BIT)&1)==0);
	rByte=S0SPDR;
	return rByte;
}
