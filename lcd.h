#ifndef __LCD_H__
#define __LCD_H__

#include "types.h"

void Init_LCD(void);
void CmdLCD(u8 cmdbyte);
void WriteLCD(u8 Byte);
void U32LCD(u32 data);
void S32LCD(s32 data);
void CharLCD(u8 ascii);
void StrLCD(char *str);
void F32LCD(f32 fn,u32 Dp);

#define MODE_8BIT_LINE1   0X30
#define MODE_8BIT_LINE2   0X38
#define GOTO_LINE1        0X80
#define GOTO_LINE2        0XC0
#define CLEAR_LCD         0X01
#define SHIFT_CUR_RIGHT   0X06
#define DSP_ON_CUR_ON     0X0E

//lcd connection pin no
#define LCD_DATA   8//p0.8-p0.15
#define LCD_RS    16//p0.16
#define LCD_RW    17//p0.17
#define LCD_EN    18//p0.18

#endif

