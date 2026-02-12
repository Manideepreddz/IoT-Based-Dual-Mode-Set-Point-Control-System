#include<lpc21xx.h>
#include "types.h"
#include "spi_eeprom.h"
#include "lcd.h"
#include "kpm.h"
#include "delay.h"
#include "esp01.h"

void eint0_virq_isr(void) __irq;

extern u8 str_setpoint[7],rDat[7]; 
extern float eeprom_setpoint;
extern int count,flag;
int val1,val2;

void Init_EINT(void)
{
	  PINSEL0 |= 0x000000C0;
    VICIntEnable = 1 << 15;
    VICVectCntl1 = (1 << 5) | 15;
    VICVectAddr1 = (u32)eint0_virq_isr;
    EXTMODE = 1 << 1;
}

void eint0_virq_isr(void) __irq
{
    u32 key;
    while(1)
    {
    CmdLCD(CLEAR_LCD);
    StrLCD("1.RTC 2.SETPOINT");
    CmdLCD(GOTO_LINE2);
    StrLCD("3.EXIT 4.SPI");

    key = KeyScan() - '0';

    if(key == 3)
        break;

    switch(key)
    {
        case 1:
            Change_RTC();
            break;

        case 2:Change_Setpoint();
		       flag=1;
               break;

        case 4:read_eeprom_for_setpoint();
			   break;			  
        
    }
    } 
	//write_eeprom_for_setpoint();
	//CmdLCD(CLEAR_LCD);

    EXTINT = 1 << 1;
    VICVectAddr = 0;
}

void read_eeprom_for_setpoint()
{
	   int j;
		for(j=0;j<4;j++)
		{
				rDat[j]=spi_eeprom_byteread(0x0000+j);
				delay_ms(50);
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("READ EEPROM");
		CmdLCD(GOTO_LINE2);
		delay_ms(200);
		eeprom_setpoint=str_to_float((char *)rDat);
		F32LCD(eeprom_setpoint,3);
		delay_ms(500); 
	          
}
void Change_Setpoint()
{	 int j=0;
     Setpoint((char *)str_setpoint, &count, &eeprom_setpoint);

    CmdLCD(CLEAR_LCD);
    StrLCD("Set Point:");
    CmdLCD(GOTO_LINE2);
    F32LCD(eeprom_setpoint, 4);
    delay_ms(500);
/*	CmdLCD(CLEAR_LCD);
    StrLCD("Set Point str:");
    CmdLCD(GOTO_LINE2);
	StrLCD((char *)str_setpoint);
	delay_ms(500); */
    //write_eeprom_for_setpoint((char *)str_setpoint);
		while(1)
		{
				spi_eeprom_bytewrite(0x0000+j, str_setpoint[j]);
				delay_ms(50);
				if(str_setpoint[j]=='\0')
					break;
				j++;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("SAVED IN EEPROM");
		delay_ms(500);
}
void write_eeprom_for_setpoint(char *str)
{	  
	        int j=0;
		while(1)
		{
				spi_eeprom_bytewrite(0x0000+j, str[j]);
				delay_ms(50);
				if(str[j]=='\0')
					break;
				j++;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("SAVED IN EEPROM");
		delay_ms(500); 
}
