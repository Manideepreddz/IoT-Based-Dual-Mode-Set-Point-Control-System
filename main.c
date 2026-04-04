#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "esp01.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "kpm.h"
#include "adc.h"
#include <lpc21xx.h>

extern char buff[100],dummy;
extern unsigned char i,ch,r_flag;
int adcVal,count,temp,flag;
float analogReading,eeprom_setpoint,cloud_setpoint,degF,degC;
char str_setpoint[7],rDat[7],str_cloud_setpoint[7]; 
char ptr[5],*ptr2,*ptr1;
int main()
{
    Init_UART0();
	Init_LCD();
	Init_ADC();
	SPI_Init();
	Init_KPM();
	Init_EINT();
	Init_RTC();

	IODIR0|=3<<22;
	CmdLCD(0x80);
	StrLCD("ESP01 Interface");
    delay_ms(1000);
    esp01_connectAP();
	MIN=1;
  while(1)
  {                    
            read_eeprom_for_setpoint();
			       	        
            Read_LM35(&degC, &degF);	
	        CmdLCD(CLEAR_LCD);
			Display_RTC();
	        CmdLCD(GOTO_LINE2);
            StrLCD("Temp:");
            F32LCD(degC,2);
			CmdLCD(GOTO_LINE1+8);
            StrLCD("set:");
            F32LCD(eeprom_setpoint,2);
		    delay_ms(500);
			delay_s(2);
		    if(degC>eeprom_setpoint)
				{
				     IOSET0=3<<22;
				}
				else
				{
				   IOCLR0=3<<22;
				}
			if(flag==1)
	        { 
		    esp01_sendSetPoint_ToThingspeak((char *)str_setpoint);
			CmdLCD(CLEAR_LCD);
			StrLCD("SAVED SET IN CLOUD");
			delay_ms(100);
		    flag=0;
	        } 
			if(MIN%5==0)
			{	
			    CmdLCD(CLEAR_LCD);
				U32LCD(MIN);
				delay_s(2);		
	       		esp01_sendTemp_ToThingspeak(degC);
			}						
			if(MIN%5==0)
			{			
				esp01_readSetPoint_FromThingspeak();
				CmdLCD(CLEAR_LCD);
			    StrLCD("READ SET FROM CLOUD");
			    delay_ms(100);
				write_eeprom_for_setpoint(str_cloud_setpoint); 
			}	
	}
}

