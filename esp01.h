#ifndef _ESP01_H_
#define _ESP01_H_

void esp01_connectAP(void);
void esp01_sendTemp_ToThingspeak(float);
void esp01_readSetPoint_FromThingspeak(void);
void esp01_sendSetPoint_ToThingspeak(char *);

#endif
