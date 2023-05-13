#include "UART.h" 
void Uart_Init(void){
	            /*   SYSCTL_RCGCUART_R |= 0x0002; // activate UART0
	               SYSCTL_RCGCGPIO_R |= 0x0004; // activate portA
                 UART1_CTL_R &= ~0X0001; // disable UART
	               UART1_IBRD_R = 104 ; //adjusting the integer baud rate 
	               UART1_FBRD_R = 11; // adjusting the floating baud rate
	               UART1_LCRH_R |= 0x0070 ; // enabling FIFO and 8bit word length
	               UART1_CTL_R = 0x00301 ; // enabling UART and RX and TX
	               GPIO_PORTC_AFSEL_R |= 0x30; // enabling alteranate function for PA0 PA1
	               GPIO_PORTC_PCTL_R = ( GPIO_PORTA_PCTL_R & 0xFF00FFFF) + 0x00110000;
	               GPIO_PORTC_DEN_R |= 0x30; // setting PA0 & PA1 as digital I/O
	               GPIO_PORTC_AMSEL_R &= ~0x30 ; // disabling anlog functions for PA0 & PA1
                */
SYSCTL_RCGCUART_R |= 0x20;
	SYSCTL_RCGCGPIO_R |= 0x10;
	UART5_CTL_R &= ~0x01;          //disable UART5
	UART5_IBRD_R = 104;
	UART5_FBRD_R = 11;
	UART5_LCRH_R  |= 0x60;
	UART5_CTL_R |= 0x301;          //enable UART5
	GPIO_PORTE_AFSEL_R |= 0x30;
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) | 0x00110000;
	GPIO_PORTE_DEN_R |= 0x30;
	GPIO_PORTE_AMSEL_R &= ~0x30 ; // disabling anlog functions for PE4 & PE5

}

void Uart_Write (char data)
{
	 while ((UART5_FR_R&0x0020) !=0){};// check if transmitter FIFO is full 
	 UART5_DR_R = data;
}

void Uart_Send_String( char* string )
{  	// function to send a string
	                     
	 while (*string){
									 
									 Uart_Write(*string);
									 string++;
	 }
	
}
 char Uart_Read(void)
{
	 while ((UART5_FR_R&0x0010) !=0){}; // waits until reciever FIFO is full to recieve the data
	 return (char)(UART5_DR_R & 0xFF);  // returns the 8 bits of the data
}			
 
 void Uart_recieve_String( char* string, int size ) 
{  // function to recieve a string                  
	 int i;
	 for ( i = 0 ; i < size; i++)
				string [i] = Uart_Read();											 									
}
							
/*
do{
	
		Uart_Write ( string[i]);
	i++;
			} while (string[i]!= '\0' );
	*/
										 
