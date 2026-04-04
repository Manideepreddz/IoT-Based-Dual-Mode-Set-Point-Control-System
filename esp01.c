#include <string.h>
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "kpm.h"

extern char buff[200];
extern unsigned char i;
extern char ptr[5],*ptr2,*ptr1,str_cloud_setpoint[7];
extern float cloud_setpoint;
void esp01_connectAP()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT");
	delay_ms(1000);

	UART0_Str("AT\r\n");          
	// AT ? Basic attention command (checks if ESP01 is responding)

	i=0;memset(buff,' ',200);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"OK"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("ATE0");
	delay_ms(1000);

	UART0_Str("ATE0\r\n");        
	// ATE0 ? Disable command echo from ESP01

	i=0;memset(buff,'\0',200);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"OK"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT+CIPMUX");
	delay_ms(1000);

	UART0_Str("AT+CIPMUX=0\r\n"); 
	// AT+CIPMUX=0 ? Set single TCP connection mode

	i=0;memset(buff,'\0',200);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"OK"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT+CWQAP");
	delay_ms(1000);

	UART0_Str("AT+CWQAP\r\n");    
	// AT+CWQAP ? Disconnect from currently connected WiFi

	i=0;memset(buff,'\0',200);
	while(i<4);
	delay_ms(1500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"OK"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT+CWJAP");
	delay_ms(1000);

	UART0_Str("AT+CWJAP=\"xyz\",\"123456789\"\r\n");
	// AT+CWJAP ? Connect ESP01 to WiFi access point (SSID, PASSWORD)

	i=0;memset(buff,'\0',200);
	while(i<4);
	delay_ms(2500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"WIFI CONNECTED"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);		
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
}

void esp01_sendTemp_ToThingspeak(float val)
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT+CIPSTART");
	delay_ms(1000);

	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	// AT+CIPSTART ? Open TCP connection to ThingSpeak server on port 80

	i=0;memset(buff,'\0',200);
	while(i<5);
	delay_ms(2500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1);
		StrLCD("AT+CIPSEND");
		delay_ms(1000);

		UART0_Str("AT+CIPSEND=52\r\n");
		// AT+CIPSEND ? Specify number of bytes to send over TCP
    //while(buff[i] != '>');
		i=0;memset(buff,'\0',200);
		delay_ms(500);

		UART0_Str("GET /update?api_key=2YV53DVE4XYUV99E&field1=");
		UART0_Float(val);
		UART0_Str("\r\n\r\n");
		// HTTP GET request ? Sends sensor value to ThingSpeak

		delay_ms(5000);
		delay_ms(5000);

		buff[i] = '\0';
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1);
		StrLCD(buff);
		delay_ms(2000);

		if(strstr(buff,"SEND OK"))
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("DATA UPDATED");
			delay_ms(1000);			
		}
		/*
		else if(!strstr(buff,"CLOSED"))
		{
			Write_CMD_LCD(0x01);
			Write_CMD_LCD(0x80);
			Write_str_LCD("AT+CIPCLOSE");
			delay_ms(1000);
			UART0_Str("AT+CIPCLOSE\r\n");
			i=0;memset(buff,'\0',200);
			while(i<5);
			delay_ms(2500);
			buff[i] = '\0';
			Write_CMD_LCD(0x01);
			Write_CMD_LCD(0x80);
			Write_str_LCD(buff);
			delay_ms(2000);
			if(strstr(buff,"OK"))
			{
				Write_CMD_LCD(0x01);
				Write_CMD_LCD(0x80);
				Write_str_LCD("OK");
				delay_ms(2000);				
			}
			else
			{
				Write_CMD_LCD(0x01);
				Write_CMD_LCD(0x80);
				Write_str_LCD("ERROR");
				delay_ms(2000);		
			}
		
		}*/
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("DATA NOT UPDATED");
			delay_ms(1000);	
		}
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
}

void esp01_sendSetPoint_ToThingspeak(char *val)
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD("AT+CIPSTART");
	delay_ms(1000);

	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	// AT+CIPSTART ? Open TCP connection to ThingSpeak server on port 80

	i=0;memset(buff,'\0',200);
	while(i<5);
	delay_ms(2500);
	buff[i] = '\0';

	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1);
	StrLCD(buff);
	delay_ms(2000);

	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("OK");
		delay_ms(1000);
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1);
		StrLCD("AT+CIPSEND");
		delay_ms(1000);

		UART0_Str("AT+CIPSEND=51\r\n");
		// AT+CIPSEND ? Specify number of bytes to send over TCP
    //while(buff[i] != '>');
		i=0;memset(buff,'\0',200);
		delay_ms(500);

		UART0_Str("GET /update?api_key=UN8JEP0N7MV2U4WJ&field1=");
		UART0_Str(val);
		UART0_Str("\r\n\r\n");
		// HTTP GET request ? Sends sensor value to ThingSpeak

		delay_ms(5000);
		delay_ms(5000);

		buff[i] = '\0';
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1);
		StrLCD(buff);
		delay_ms(2000);

		if(strstr(buff,"SEND OK"))
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("DATA UPDATED");
			delay_ms(1000);			
		}
		/*
		else if(!strstr(buff,"CLOSED"))
		{
			Write_CMD_LCD(0x01);
			Write_CMD_LCD(0x80);
			Write_str_LCD("AT+CIPCLOSE");
			delay_ms(1000);
			UART0_Str("AT+CIPCLOSE\r\n");
			i=0;memset(buff,'\0',200);
			while(i<5);
			delay_ms(2500);
			buff[i] = '\0';
			Write_CMD_LCD(0x01);
			Write_CMD_LCD(0x80);
			Write_str_LCD(buff);
			delay_ms(2000);
			if(strstr(buff,"OK"))
			{
				Write_CMD_LCD(0x01);
				Write_CMD_LCD(0x80);
				Write_str_LCD("OK");
				delay_ms(2000);				
			}
			else
			{
				Write_CMD_LCD(0x01);
				Write_CMD_LCD(0x80);
				Write_str_LCD("ERROR");
				delay_ms(2000);		
			}
		
		}*/
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("DATA NOT UPDATED");
			delay_ms(1000);	
		}
	}
	else
	{
		CmdLCD(GOTO_LINE2);
		StrLCD("ERROR");
		delay_ms(1000);		
		return;
	}
}

void esp01_readSetPoint_FromThingspeak()
{
    // char *value = NULL;
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("CIPSTART");
    delay_ms(1000);

    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
    i = 0;
    memset(buff, '\0', 200);
    while (i < 5);
    delay_ms(2500);
    buff[i] = '\0';

    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD(buff);
    delay_ms(2000);

    if (strstr(buff, "CONNECT") || strstr(buff, "ALREADY CONNECTED"))
    {
        CmdLCD(0x01);
        CmdLCD(0x80);
        StrLCD("CIPSEND");
        delay_ms(1000);

        /* 66 bytes approx */
        UART0_Str("AT+CIPSEND=66\r\n");
        delay_ms(500);

        UART0_Str("GET /channels/3244248/feeds/last.json?api_key=59LJIRKPMTWHCK7Y\r\n\r\n");
        delay_ms(5000);
		 
         buff[i] = '\0';
      	 ptr1=strrchr(buff,':');
		 ptr2=strrchr(ptr1,'}');
		 ptr2-=1;
	     ptr1+=2;
		 ptr1[ptr2-ptr1]='\0';
		 CmdLCD(CLEAR_LCD);
		/*StrLCD("string");
		CmdLCD(GOTO_LINE2);
		StrLCD(ptr1);
		delay_ms(2000);	
		CmdLCD(CLEAR_LCD);
		  */
		strcpy(str_cloud_setpoint,ptr1);

		/*StrLCD("string");
		CmdLCD(GOTO_LINE2);
		StrLCD(str_cloud_setpoint);
		delay_ms(2000);	*/
		CmdLCD(CLEAR_LCD);
		cloud_setpoint=str_to_float(ptr1);
		StrLCD("Str to float2");
		CmdLCD(GOTO_LINE2);
		F32LCD(cloud_setpoint,3);
		delay_ms(1000);
		i = 0;
        memset(buff, '\0', 200);
         UART0_Str("AT+CIPCLOSE\r\n");
        delay_ms(1000);	
    }
    else
    {
        CmdLCD(0x01);
        StrLCD("ERROR");
        delay_ms(2000);
    }
}
