#include "./Keypad.h"

//PORTA
//0-3 --> rows
//4-7 --> colums
void keypad_initialize( )
	{
		port_dig_init( R1_port , R1_pin , OUTPUT); // intialize pins 0-->3 as digital OUTPUT 
		port_dig_init( R2_port , R2_pin , OUTPUT); 
		port_dig_init( R3_port , R3_pin , OUTPUT);
		port_dig_init( R4_port , R4_pin , OUTPUT);
		port_dig_init( C1_port , C1_pin , INPUT); // intialize pins 4-->7 as digital INPUT
		port_dig_init( C2_port , C2_pin , INPUT);
		port_dig_init( C3_port , C3_pin , INPUT);
		port_dig_init( C4_port , C4_pin , INPUT);	
		// SET PINS 4--> 7 PUR = 1 by default 
	}
	
uint8_t keypad_u8Read() {
		uint8_t arr[4][4] = {
			{'1','2','3','A'},
				{'4','5','6','B'},
					{'7','8','9','C'},
						{'.','0','#','D'}
			} ;
		char row , col , x ; 
		char return_value = 0xFF ; // the initial value before reading is 0xFF (will remain 0xFF IF no button pressed  )
		for (row=0 ; row <= 3 ; row ++)
			{	
				port_dig_write( R1_port ,  R1_pin , 1);
				port_dig_write( R2_port ,  R2_pin , 1);
				port_dig_write( R3_port ,  R3_pin , 1);
				port_dig_write( R4_port ,  R4_pin , 1);
				
				switch(row){
					case 0:
						port_dig_write( R1_port  , R1_pin , 0);
						break;
					case 1:
						port_dig_write( R2_port  , R2_pin , 0);
						break;
					case 2:
						port_dig_write( R3_port  , R3_pin , 0);
						break;
					case 3:
						port_dig_write( R4_port  , R4_pin , 0);
							break;
				}
					//  delay_us(2); or add in the main not here 

				
				for(col= 0; col <=3 ; col ++ )
				{
					switch(col){
					case 0:
						x= port_dig_read( C1_port , C1_pin) ; 
						break;
					case 1:
						x= port_dig_read( C2_port , C2_pin) ; 
						break;
					case 2:
						x= port_dig_read( C3_port , C3_pin) ; 
						break;
					case 3:
						x= port_dig_read( C4_port , C4_pin) ; 
						break;
				}
					
					if (x==0) { 
						return_value= arr[row][col];
						break ; 
					}

				} 
				if(x==0) 
					break;
			}
			return return_value ;
	}
