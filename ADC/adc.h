#ifndef __ADC_H__
#define __ADC_H__

#include "uart0.h"
#define ADC_CLK 3000000
#define CLKDIV  ((PCLK/ADC_CLK)-1)

#define CLK_DIV_BITS   8
#define PDN_BIT        21
#define START_CONV_BIT 24

#define RESULT_BITS  6
#define DONE_BIT    31

//userdefines functions for the LM35 and ADC
void Init_ADC(void);
void Read_ADC(int chno,int* adcval,float* analogredaing);
void Read_LM35(float *degC,float *degF);

#endif
