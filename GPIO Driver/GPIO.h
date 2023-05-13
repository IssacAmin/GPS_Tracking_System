#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include "../Utilities/tm4c123gh6pm.h"
#include "../Utilities/types.h"

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

typedef enum{
	portA,
	portB,
	portC,
	portD,
	portE,
	portF
} port;
	typedef enum{
	pin0,
	pin1,
	pin2,
	pin3,
	pin4,
	pin5,
	pin6,
	pin7
	} pin;



void port_dig_init(port portnumber, pin pinnumber, uint8_t direction );	//Pin initialization 

void port_dig_write(port portnumber, pin pinnumber, uint8_t data);			//Input

uint8_t port_dig_read(port portnumber, pin pinnumber );					//Output 

void port_dig_toggle(port portnumber, pin pinnumber);						//Toggle output






#endif 
