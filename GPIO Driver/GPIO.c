#include "./GPIO.h"

	
void port_dig_init(port portnumber, pin pinnumber, uint8_t direction ){
	
	switch(portnumber){
		case portA:
		//PortA code
		SYSCTL_RCGCGPIO_R |= 0x01; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x01)== 0); // Wait to stabilize
		GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTA_CR_R |= 1 <<pinnumber;
		GPIO_PORTA_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTA_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTA_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTA_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTA_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTA_PUR_R  |= (1 <<pinnumber);
		}
		GPIO_PORTA_DEN_R |= (1 <<pinnumber);
		
			break;
		case portB:
			//PortB code
		SYSCTL_RCGCGPIO_R |= 0x02; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x02)== 0); // Wait to stabilize
		GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTB_CR_R |= 1 <<pinnumber;
		GPIO_PORTB_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTB_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTB_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTB_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTB_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTB_PUR_R  |= (1 <<pinnumber);
		}
		GPIO_PORTB_DEN_R |= (1 <<pinnumber);
			break;
		case portC:
			//PortC code
		SYSCTL_RCGCGPIO_R |= 0x04; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x04)== 0); // Wait to stabilize
		GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTC_CR_R |= 1 <<pinnumber;
		GPIO_PORTC_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTC_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTC_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTC_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTC_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTC_PUR_R  |= (1 <<pinnumber);
		}
		GPIO_PORTC_DEN_R |= (1 <<pinnumber);
			break;
		case portD:
			//PortD code
		SYSCTL_RCGCGPIO_R |= 0x08; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x08)== 0); // Wait to stabilize
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTD_CR_R |= 1 <<pinnumber;
		GPIO_PORTD_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTD_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTD_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTD_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTD_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTD_PUR_R  |= (1 <<pinnumber);
		}
		GPIO_PORTD_DEN_R |= (1 <<pinnumber);
			break;
		case portE:
			//PortE code
				SYSCTL_RCGCGPIO_R |= 0x10; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x10)== 0); // Wait to stabilize
		GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTE_CR_R |= 1 <<pinnumber;
		GPIO_PORTE_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTE_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTE_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTE_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTE_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTE_PUR_R  |= (1 <<pinnumber);
		}
		GPIO_PORTE_DEN_R |= (1 <<pinnumber);
			break;
		case portF:
			//PortF code
				SYSCTL_RCGCGPIO_R |= 0x20; //Enable clock
		while ((SYSCTL_RCGCGPIO_R & 0x20)== 0); // Wait to stabilize
		GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
		GPIO_PORTF_CR_R |= 1 <<pinnumber;
		GPIO_PORTF_AMSEL_R &= ~(1 <<pinnumber); //Disable alternate functions
		GPIO_PORTF_PCTL_R &= ~(0xF << (pinnumber*4));
		GPIO_PORTF_AFSEL_R &= ~(1 <<pinnumber);
		if(direction == OUTPUT){
			GPIO_PORTF_DIR_R |= (1 <<pinnumber);}
		else if(direction == INPUT){
			GPIO_PORTF_DIR_R &=~ (1 <<pinnumber);
			GPIO_PORTF_PUR_R  |= 1 <<pinnumber;
		}
		GPIO_PORTF_DEN_R |= (1 <<pinnumber);
			break;
	}
}


void port_dig_write(port portnumber, pin pinnumber, uint8_t data){
	switch(portnumber){
		case portA:
			if(data == HIGH)
				GPIO_PORTA_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTA_DATA_R  &=~ (1 << pinnumber);
			break;
		case portB:
			if(data == HIGH)
				GPIO_PORTB_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTB_DATA_R  &=~ (1 << pinnumber);			
			break;
		case portC:
			if(data == HIGH)
				GPIO_PORTC_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTC_DATA_R  &=~ (1 << pinnumber);
			break;
		case portD:
			if(data == HIGH)
				GPIO_PORTD_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTD_DATA_R  &=~ (1 << pinnumber);
			break;
		case portE:
			if(data == HIGH)
				GPIO_PORTE_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTE_DATA_R  &=~ (1 << pinnumber);
			break;
		case portF:
			if(data == HIGH)
				GPIO_PORTF_DATA_R |= (1 << pinnumber);
			else if(data == LOW)
				GPIO_PORTF_DATA_R  &=~ (1 << pinnumber);
			break;

		}
}

uint8_t port_dig_read(port portnumber, pin pinnumber ){
	int value = 0;
	switch(portnumber){
		case portA:
			value = (GPIO_PORTA_DATA_R & ( 1 << pinnumber)) >> pinnumber;
			break;
		case portB:
				value = (GPIO_PORTB_DATA_R & ( 1 << pinnumber)) >> pinnumber;
		 break;
		case portC:
				value = (GPIO_PORTC_DATA_R & ( 1 << pinnumber)) >> pinnumber;
			break;
		case portD:
					value = (GPIO_PORTD_DATA_R & ( 1 << pinnumber)) >> pinnumber;
			break;
		case portE:
					value = (GPIO_PORTE_DATA_R & ( 1 << pinnumber)) >> pinnumber;
			break;
		case portF:
				 value = (GPIO_PORTF_DATA_R & ( 1 << pinnumber)) >> pinnumber;

			break;
	}
	return value;
}

void port_dig_toggle(port portnumber, pin pinnumber){
	switch(portnumber){
		case portA:
				GPIO_PORTA_DATA_R ^= 1 << pinnumber;
			break;
		case portB:
				GPIO_PORTB_DATA_R ^= 1 << pinnumber;
			break;
		case portC:
		
				GPIO_PORTC_DATA_R ^= 1 << pinnumber;
			break;
		case portD:
				GPIO_PORTD_DATA_R ^= 1 << pinnumber;
			break;
		case portE:
				GPIO_PORTE_DATA_R ^= 1 << pinnumber;
		
			break;
		case portF:
				GPIO_PORTF_DATA_R ^= 1 << pinnumber;
			break;

		}
	
}
