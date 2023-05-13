#ifndef SYSTICK_H
#define SYSTICK_H
#include "../Utilities/tm4c123gh6pm.h"
#include "../Utilities/types.h"

void delay_s(unsigned int time);	//Delay in seconds
void delay_ms(unsigned int time);	//Delay in millisecond
void delay_us(unsigned int time);		//Delay in microsecond


#endif
