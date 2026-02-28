#include<lpc21xx.h>
#include"lcd.h"
#include"delay.h"
#include"types.h"
#include"kpm.h"

#define MAX_DIGITS 8
u8 KpmLUT[4][4]=
{
	{'0','1','2','3'},
	{'4','5','6','7'},
	{'8','9','B','E'},
	{'0','.','K','0'}
};

void Init_KPM(void)
{
		IODIR1|=(0XF)<<ROW_4;
}
u32  ColScan(void)
{
		int status;
		status=(((IOPIN1>>COL_4)&0XF)<15)?0:1;
		return status;
}
u32  RowCheck(void)
{
	  u32 r;
	  for(r=0;r<=3;r++)
	  {
			IOPIN1=(IOPIN1&~(0XF<<ROW_4))|(~(1<<r)<<ROW_4);
			if(ColScan()==0)
				break;
		}
		IOCLR1=0XF<<ROW_4;
		return r;
}
u32  ColCheck(void)
{
		u32 c;
		for(c=0;c<=3;c++)
		{
			if(((IOPIN1>>(COL_4+c))&1)==0)
				break;
		}
		return c;
}
u8  KeyScan(void)
{
	  //Init_KPM();
		u32 r,c;
	  u8 key;
		while(ColScan());
		r=RowCheck();
		c=ColCheck();
	  key=KpmLUT[r][c];
		while(ColScan()==0);
	  return key;
}
	
float str_to_float(char *s)
{
    float val = 0, frac = 0, div = 1;
    int i = 0;

    while(s[i] && s[i] != '.')
        val = val * 10 + (s[i++] - '0');

    if(s[i] == '.')
    {
        i++;
        while(s[i])
        {
            frac = frac * 10 + (s[i++] - '0');
            div *= 10;
        }
    }
    return val + frac / div;
}

void Setpoint(char *buf, int *count, float *point)
{
    u8 key;
    int i = 0;
    int dot_flag = 0;

    CmdLCD(CLEAR_LCD);
    StrLCD("NEW SETPOINT");
    CmdLCD(GOTO_LINE2);

    while(1)
    {
        key = KeyScan();

        /* Number input */
        if((key >= '0' && key <= '9') && i < MAX_DIGITS)
        {
            buf[i++] = key;
            CharLCD(key);
        }

        /* Decimal point (only once) */
        else if(key == '.' && dot_flag == 0 && i < MAX_DIGITS)
        {
            dot_flag = 1;
            buf[i++] = key;
            CharLCD(key);
        }

        /* Backspace */
        else if(key == 'B' && i > 0)
        {
            if(buf[i-1] == '.') dot_flag = 0;
            i--;
            buf[i] = '\0';

            CmdLCD(GOTO_LINE2);
            StrLCD("                "); // clear line
            CmdLCD(GOTO_LINE2);
            StrLCD(buf);
        }

        /* Enter key */
        else if(key == 'K')
        {
            buf[i] = '\0';
            *point = str_to_float(buf);
            *count = i;
            break;
        }
    }
}
