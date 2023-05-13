#include "./Systick Driver/Systick.h"
#include "./Keypad Driver/Keypad.h"
#include "./UART Driver/UART.h"
#include "./GPS Driver/GPS.h"
#include "./LCD Driver/LCD_ST7920.h"
#include "./LED Driver/LED Driver.h"

//Bitmap array Assignment 
uint8_t logo[] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,
0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF8,
0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF8,
0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF8,
0xFF, 0xFE, 0x00, 0x00, 0x00, 0x18, 0x00, 0x78, 0x1E, 0x00, 0x18, 0x00, 0x00, 0x00, 0x7F, 0xF8,
0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x07, 0xFE, 0x01, 0x80, 0x00, 0x00, 0x1F, 0xF8,
0xFF, 0xE0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x0F, 0xF8,
0xFF, 0xE0, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x80, 0x01, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x07, 0xF8,
0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xF8,
0xFF, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x78,
0xFE, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x78,
0xFC, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x18,
0xF8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x18,
0xF0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00,
0xE0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00,
0xC0, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00,
0x80, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00,
0x80, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x86, 0x00, 0x00, 0x60, 0x7F, 0xFF, 0xFF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xE0, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xE0, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0x80, 0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFE, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x18, 0x00, 0x1F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xE0, 0x00, 0x78, 0x06, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x07, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xE0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x1F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xE0, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00,
0xF8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x18,
0xF8, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x18,
0xFE, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x78,
0xFF, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x78,
0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x01, 0xF8,
0xFF, 0xC0, 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0x80, 0x00, 0x00, 0x03, 0xF8,
0xFF, 0xF0, 0x00, 0x00, 0x18, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x18, 0x00, 0x00, 0x07, 0xF8,
0xFF, 0xF8, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x1F, 0xF8,
0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xF8,
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xFF, 0xF8,
0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF8,
0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF8,
0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF8,
0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFC
};

uint8_t image[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int main(void){
	
	//Coordinates Array Initialization
	float coordinate[2];
	float prev_coordinate[2];
	float entered_coordinate[2] = {3003.96233, 3116.637167                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          };
	
	//keypad control variables
	 char keypadInput = 'x';
	char keypadBuffer[25];
	int keypadCounter = 0;
	int i = 0;
	//calculation variables
	char msg[500];
	float distance;
	float displacement;
	float current_displacement;
	float total_distance;
	float bearing;
	DIRECTION direction;
	uint8_t lastKnownX = 7 ;
	uint8_t lastKnownY = 43;
	//Pins pin Initialization
		//lcd pin initialization
		port_dig_init(SID_PORT, SID_PIN, OUTPUT);
		port_dig_init(SLCK_PORT, SLCK_PIN, OUTPUT);
		port_dig_init(CS_PORT, CS_PIN, OUTPUT);
		port_dig_init(RESET_PORT, RESET_PIN, OUTPUT);
		
		//RGB leds pin Initialization
		port_dig_init(portA, pin2, OUTPUT);
		port_dig_init(portA, pin3, OUTPUT);
		port_dig_init(portA, pin4, OUTPUT);
		RGB_init(RED);
		RGB_init(GREEN);
		RGB_init(BLUE);
		//Keypad pin Initialization
		keypad_initialize();
		
		//Uart Initialization
		Uart_Init();
		
		//Lcd INIT
		lcd_init();
		DrawBitmap(logo);
		delay_ms(1500);
		lcd_clear();
		// 1'st coordinates input		
		/*SendString(0,0, "  Latitude: ");
		while(keypad_u8Read() != '#')
		{
			keypadInput = keypad_u8Read();
			if(keypadInput != (char)0xff)
			{
				keypadBuffer[keypadCounter] = keypadInput;
				
				while(keypadInput != (char)0xff)
					{
					keypadInput = keypad_u8Read();
					//sprintf(msg, "%c", keypadInput);
					//SendString(0,0, msg);
					SendString(1, 0, keypadBuffer);
				}
				keypadCounter++;
			}
		}
		SendString(1,0,keypadBuffer);
		entered_coordinate[0] = atof(keypadBuffer);
		delay_ms(500);
		for(i = 0; i< 25;i++)
		{
			keypadBuffer[i] = '\0';
		}
		keypadCounter = 0;
		// 2nd coordinate input 
		SendString(2,0, "Longitude: ");
		while(keypad_u8Read() != '#')
		{
			keypadInput = keypad_u8Read();
			if(keypadInput != (char)0xff)
			{
				keypadBuffer[keypadCounter] = keypadInput;
				
				while(keypadInput != (char)0xff)
					{
					keypadInput = keypad_u8Read();
					//sprintf(msg, "%c", keypadInput);
					//SendString(0,0, msg);
					SendString(3, 0, keypadBuffer);
				}
				keypadCounter++;
			}
		}
		SendString(3,0,keypadBuffer);
		entered_coordinate[1] = atof(keypadBuffer);
		delay_ms(500);
		
		lcd_clear();
*/
		SendString(0,0,"  Calculating...");
