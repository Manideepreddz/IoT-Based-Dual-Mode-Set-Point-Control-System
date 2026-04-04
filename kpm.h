#ifndef __KPM_H__
#define __KPM_H__

#include "types.h"

//userdefines functions for the Keypad
void Init_KPM(void);
u32  ColScan(void);
u32  RowCheck(void);
u32  ColCheck(void);
u8   KeyScan(void);
void Setpoint(char *buf, int *count, float *point);
void Change_Setpoint(void);
float str_to_float(char *s);

//keypad connection pin no
#define ROW_4     16//p1.16-p1.19
#define COL_4     20//p1.20-p1.23

void Init_RTC(void);
void Change_RTC(void);
void Change_HOURS(void);
void Change_MINS(void);
void Change_SECS(void);
void Change_DATES(void);
void Change_MONTHS(void);
void Change_YEARS(void);
void Change_DAYS(void);
void Display_RTC(void);
void Invalid_Input(void);
void delete_space(u32);

#endif
