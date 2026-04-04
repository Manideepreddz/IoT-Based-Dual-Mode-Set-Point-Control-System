#ifndef __SPI_DEFINES_H__
#define __SPI_DEFINES_H__

#define FUNC_1    1
#define SCL_0_4   0x00000100
#define MISO_0_5  0x00000400
#define MOSI_0_6  0x00001000
#define CS_0_7    7

//SXSPCR SFR defined bits
#define CPHA_BIT  3
#define CPOL_BIT  4
#define MSTR_BIT  5
#define LSBF_BIT  6

//SXSPSR SFR
#define SPIF_BIT  7

//SPI diviser
#define FOSC        12000000
#define CCLK        (FOSC*5)
#define PCLK        (CCLK/4)
#define SPI_CLK      1000000
#define SPI_DIVISER (PCLK/SPI_CLK)

#endif
