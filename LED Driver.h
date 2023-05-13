#ifndef LED 
#define LED 

#include "../GPIO Driver/GPIO.h"

typedef enum{
	RED=1,
	BLUE,
	GREEN
} COLOR;



void RGB_init(COLOR c);
void RGB_on(COLOR c);
void RGB_off(COLOR c);

void led_init(port portNumber, pin pinNumber);
void led_on(port portNumber, pin pinNumber);
void led_off(port portNumber, pin pinNumber);

#endif
