#ifndef UART_H
#define UART_H
#include "../Utilities/tm4c123gh6pm.h" 
#include "../Utilities/types.h" 

void Uart_Init(void);
void Uart_Write (char data);
char Uart_Read  (void);
void Uart_recieve_String( char* string , int size);
void Uart_Send_String( char* string);


#endif
