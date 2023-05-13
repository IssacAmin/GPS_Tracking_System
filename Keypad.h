#ifndef Keypad_H
#define Keypad_H


#include "../GPIO Driver/GPIO.h"

//Row1
#define R1_port portA
#define R1_pin pin7
//Row2
#define R2_port	portA
#define R2_pin	pin6
//Row3
#define R3_port	portA
#define R3_pin	pin5
//Row4
#define R4_port	portB
#define R4_pin	pin4
//Column1
#define C1_port	portE
#define C1_pin	pin5
//Column2
#define C2_port	portE
#define C2_pin	pin4
//Column3
#define C3_port	portB
#define C3_pin	pin1
//Column4
#define C4_port portB
#define C4_pin	pin0




uint8_t keypad_u8Read(void); 

void keypad_initialize(void);

#endif 
