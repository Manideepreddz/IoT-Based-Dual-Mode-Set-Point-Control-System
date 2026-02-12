#include"adc.h"
#include"delay.h"
#include<lpc21xx.h>

extern int adcVal;
extern float analogReading;

void Init_ADC()
{
    PINSEL0|=0x00000000;
	ADCR=(1<<PDN_BIT)|(CLKDIV<<CLK_DIV_BITS);
}

void Read_ADC(int chno,int* adcVal,float* analogReading)
{
	ADCR&=0xFFFFFF00;
	ADCR|=(1<<START_CONV_BIT)|(1<<chno);
	delay_us(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<START_CONV_BIT);
	*adcVal=((ADDR>>RESULT_BITS)&1023);
	*analogReading=(*adcVal)*(3.3/1023);
}
void Read_LM35(float *degC,float *degF)
{
	int adc;
	float ear;
	Read_ADC(1,&adc,&ear);
	*degC=ear*100.0;
	*degF=((*degC)*(9/5))+32;
}
