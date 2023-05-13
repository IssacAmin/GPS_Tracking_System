//header File Guard
#ifndef LCD_ST7920 
#define LCD_ST7920

// Imports
#include <stdint.h>

//defines
#define SID_PORT portC
#define SID_PIN pin6
#define SLCK_PORT portB
#define SLCK_PIN pin7
#define CS_PORT portC
#define CS_PIN pin7
#define RESET_PORT portB
#define RESET_PIN pin6


typedef enum{
		UP,
    DOWN,
    RIGHT,
    LEFT,
    UP_RIGHT,
	  UP_LEFT,
	  DOWN_RIGHT,
	  DOWN_LEFT
} DIRECTION;



void SPI_Transmit(uint8_t Byte);
void Send_Command(uint8_t Byte);
void Send_Data(uint8_t Byte);
void lcd_init(void);
void Graphic_Init(void);
void Graphic_Stop(void);
void DrawBitmap(unsigned char *bitmap);
