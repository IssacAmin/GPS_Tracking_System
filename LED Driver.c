#include "./LED Driver.h"


void RGB_init(COLOR c){
	port_dig_init(portF,c,OUTPUT);
}

void RGB_on(COLOR c){
port_dig_write(portF,c,HIGH);
}

void RGB_off(COLOR c){
port_dig_write(portF,c,LOW);
}

void led_init(port portNumber, pin pinNumber){
		port_dig_init(portNumber, pinNumber,OUTPUT);
}
void led_on(port portNumber, pin pinNumber){
port_dig_write(portNumber,pinNumber,HIGH);

}

void led_off(port portNumber, pin pinNumber){
port_dig_write(portNumber,pinNumber,LOW);

}
