#ifndef GPS_H
#define GPS_H
#include "../UART Driver/UART.h"
#include <Math.h>
#include <String.h>
#include <stdlib.h>
#include "../LCD Driver/LCD_ST7920.h"



void gps_read(char* msg);
float degreeToDecimal (float coordinate);
float radian (float angle);
float get_distance ( float f_long , float f_lat , float s_long , float s_lat );
int GPS_manipulated_string (char* messege, float* coordinates);
DIRECTION getDirection(double curLat, float curLong, float prevLat, float prevLong, float startBearing);
float getBearing(float curLat, float curLong, float prevLat, float prevLong);
#endif
