#include "./GPS.h"
#include <string.h>
#include <stdlib.h>
 // contains the data saved from the GPS module

const double ER = 6371000;
const double PI = 3.141592653589793238;
void gps_read(char * messege)
{
	int i;
// checking the validity of data
	char c[100];
	do{
		c[0] = Uart_Read();
	}while(c[0] != '$');
	for(i = 1; i <100; i++){
		c[i] = Uart_Read();
	}
	}
		//Uart_recieve_String(messege , 100);


// converting the latitude or longitude to degree
float degreeToDecimal (float coordinate)
{
	float decimal;
	int degree;
	float minutes;
	coordinate = coordinate / 100;
	degree = (int) coordinate;
	minutes =  ((coordinate - degree) * 100);
	decimal = degree + (minutes/60);
	
	return decimal;
}

float radian (float angle) // coverting the degree to radian
{
	
return (angle * PI)/180;
}



// getting the distance using haversine formula
float get_distance( float f_long , float f_lat , float s_long , float s_lat )
{
float first_long = (radian(degreeToDecimal(f_long)));
float first_lat = (radian(degreeToDecimal(f_lat)));
float second_long = (radian(degreeToDecimal(s_long)));
float second_lat = (radian(degreeToDecimal(s_lat)));
	

float diff_long =	second_long - first_long ; 
float diff_lat = second_lat - first_lat ; 
	
	float a = pow(sin(diff_lat / 2),2) + cos (first_lat) * cos (second_lat) * pow(sin(diff_long / 2),2);
	double c = 2 * asin ( sqrt (a)) ;
	return ER * c ;

}



	// parsing the string to float
	int GPS_manipulated_string (char* messege, float* coordinates)
	{
		int i = 0;
		int valid =0;
	for(i = 0; i < 5;i++)
		{
			const char delim[] = ",";
			char* token;
				int counter;
				valid = 0;
				gps_read(messege);
				token = strtok(messege, delim);
			 while( token != NULL ) {
					if(strcmp(token, "$GPRMC") == 0)
					{
							counter = 0;
					}
					else if(counter == 2)
					{
							if(strcmp(token, "A") == 0)
								valid = 1;
							else if(strcmp(token, "V") == 0)
								valid = 0;
					}
					else if(counter == 3 && valid ==1)
					{
						coordinates[0] = atof(token);
					}
					else if(counter ==5 && valid == 1)
						coordinates[1] = atof(token);
					token = strtok(NULL, delim);
					counter++;
		}
	}
		if(valid == 1)
			return 0;
		else 
			return 1;
}

DIRECTION getDirection(double curLat, float curLong, float prevLat, float prevLong, float startBearing)
{      float currentBearing = getBearing(curLat, curLong, prevLat, prevLong);

    double diff = (currentBearing - startBearing);
    if(diff < 0)
        diff += 360;
        
    if( ((diff > 337.5) && (diff<=360)) || ((diff >= 0)&&(diff <= 22.5)))
        return UP;
		
   else if ((diff > 22.5) && (diff <= 67.5))
        return UP_RIGHT;
		
   else if ((diff > 67.5) && (diff <= 112.5))
        return RIGHT;
	 
	 else if ((diff > 112.5) && (diff <= 157.5))
        return DOWN_RIGHT;
	 
	 else if ((diff > 157.5) && (diff <= 202.5))
        return DOWN;
	 else if ((diff > 202.5) && (diff <= 247.5))
        return DOWN_LEFT;
	 
	 else if ((diff > 247.5) && (diff <= 292.5))
        return LEFT;
	 
	 else if ((diff > 292.5) && (diff <= 337.5))
        return UP_LEFT;
	 else 
		 return UP;

    
}
	



float getBearing(float curLat, float curLong, float prevLat, float prevLong){
    float brng;
    float x;
    float y;
    curLat = radian(curLat);
    curLong = radian(curLong);
    prevLat = radian(prevLat);
    prevLong = radian(prevLong);

 y = sin(curLong-prevLong) * cos(curLat);
 x = cos(prevLat)*sin(curLat) - sin(prevLat)*cos(curLat)*cos(curLong-prevLong);
 brng = atan2(y, x) *180/PI;
 if (brng < 0)
     brng += 360;
     return brng;
 }

