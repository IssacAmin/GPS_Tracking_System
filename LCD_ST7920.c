#include "./LCD_ST7920.h"

#include "../GPIO Driver/GPIO.h"
#include "../Systick Driver/Systick.h"


// Function Implementations 
void SPI_Transmit(uint8_t Byte)
{
		int i = 0;
    for(i = 0; i < 8;i++)
    {
        if((Byte<< i)& 0x80)
            port_dig_write(SID_PORT, SID_PIN, HIGH);
        else
            port_dig_write(SID_PORT, SID_PIN, LOW);
        
        //clock for serial connection
        port_dig_write(SLCK_PORT, SLCK_PIN, LOW);
        port_dig_write(SLCK_PORT, SLCK_PIN, HIGH);
    }
}

void Send_Command(uint8_t Byte)
{
    //CS pin must be high during serial communication
    port_dig_write(CS_PORT,CS_PIN, HIGH);

    //SYNC + RS(0) RW(0) BYTE
    SPI_Transmit(0xf8);
    // HIGH NIBBLE BYTE
    SPI_Transmit(Byte & 0xf0);
    //LOWER NIBBLE BYTE
    SPI_Transmit((Byte<<4) & 0xf0);
    delay_us(50);

    port_dig_write(CS_PORT,CS_PIN, LOW);
   
}

void Send_Data(uint8_t Byte)
{
    //CS pin must be high during serial communication
    port_dig_write(CS_PORT,CS_PIN, HIGH);

    //SYNC + RS(1) RW(0) BYTE
    SPI_Transmit(0xfa);
    // HIGH NIBBLE BYTE
    SPI_Transmit(Byte & 0xf0);
    //LOWER NIBBLE BYTE
    SPI_Transmit((Byte<<4) & 0xf0);
    delay_us(50);

    port_dig_write(CS_PORT,CS_PIN, LOW);
}

void lcd_init(void)
{
    port_dig_write(RESET_PORT,RESET_PIN, LOW);
    delay_ms(10);
    port_dig_write(RESET_PORT,RESET_PIN, HIGH);
    delay_ms(50);

    Send_Command(0x30);
    delay_us(110);

    Send_Command(0x30);
    delay_us(40);

    Send_Command(0x08);
    delay_us(110);

    Send_Command(0x01);
    delay_ms(12);

    Send_Command(0x06);
    delay_ms(1);

    Send_Command(0x0c);
    delay_ms(1);

    Send_Command(0x02);
    delay_ms(1);


}

void Graphic_Init(void)
{
    Send_Command(0x30);
    delay_ms(1);

    Send_Command(0x34);
    delay_ms(1);

    Send_Command(0x36);
    delay_ms(1);
}

void Graphic_Stop(void)
{
    Send_Command(0x30);
    delay_ms(1);
}

void DrawBitmap(unsigned char *image)
{

        unsigned char i, j, k;
				Graphic_Init();

        for ( i = 0 ; i < 2 ; i++ ) 
        {
            for ( j = 0 ; j < 32 ; j++ ) 
            {
                Send_Command(0x80 | j) ;
                if ( i == 0 ) 
                {
                    Send_Command(0x80);
                } 
                else 
                {
                    Send_Command(0x88);
                }
                for ( k = 0 ; k < 16 ; k++ )
                {
                    Send_Data( *image++ ) ;
                }
            }
        }
	Graphic_Stop();
}
void UpdateBitmap(unsigned char *image,DIRECTION direction, uint8_t *lastKnownX, uint8_t *lastKnownY)
{
			//iterator declaration.
    //initial x location = 7
    //initial y location = 43
    //Filling the new box of pixels to update route.
    
    //checking if new box is out of bounds 
    if((*lastKnownX == 0 && direction == LEFT) ||
     (*lastKnownX == 15 && direction ==RIGHT)  || 
     (*lastKnownY ==0 && direction == UP) ||
     (*lastKnownY ==43 && direction == DOWN)
     )
    {
		int x = 0;
		int positionIndex;
     //shift bitmap to make room
    switch(direction)
    // each case will shift the X, y locations accordingly to fill new pixels to draw route in specified direction.
    {
        case UP:
        //x location is the same, y location is shifted up 4 pixels.
        bitmap_clear(image);
        *lastKnownY = 43;
        break;
        case DOWN:
        //x location is the same, y location is shifted down 4 pixels.
        bitmap_clear(image);
        *lastKnownY = 0;
        break;
        case RIGHT:
        //y is the same, x is shifted 1 location for 8 pixels.
        bitmap_clear(image);
        *lastKnownX = 0;
        break;
        case LEFT:
        bitmap_clear(image);
        *lastKnownX = 15;
        break;
        default:
        break;
    }
        //filling box
        positionIndex = (*lastKnownX) + 16*(*lastKnownY);
		
        for(x = 0; x < 4; x++)
        {
            image[positionIndex] = 0xff;
            positionIndex += 16;
        }
				lcd_clear();
        
    }
    else
    {
		int x = 0;
		int positionIndex;
    switch(direction)
    // each case will shift the X, y locations accordingly to fill new pixels to draw route in specified direction.
    {
        case UP:
        //x location is the same, y location is shifted up 4 pixels.
        *lastKnownY -= 4;
        break;
        case DOWN:
        //x location is the same, y location is shifted down 4 pixels.
        *lastKnownY += 4;
        break;
        case RIGHT:
        //y is the same, x is shifted 1 location for 8 pixels.
        *lastKnownX += 1;
        break;
        case LEFT:
        *lastKnownX -= 1;
        break;
        default:
        break;
    }
		positionIndex = (*lastKnownX) + 16*(*lastKnownY);
        for(x = 0;x < 4;x++)
        {
            image[positionIndex] = 0xff;
            positionIndex += 16;
        }
    }
    //re-drawing the new bitmap
    DrawBitmap(image);
}
void SendString(int row, int col, unsigned char* string)
{
	switch (row)
	{
		case 0:
			col |= 0x80;
			break;
		case 1:
			col |= 0x90;
			break;
		case 2: 
			col |= 0x88;
			break;
		case 3:
			col |= 0x98;
			break;
		default: //row 0
			col |= 0x80;
			break;
	}
	
	Send_Command(col);
	
	while (*string)
	{
		Send_Data(*string++);
	}
}

/*void Bitmap_Init(uint8_t image[],uint8_t logo[])
{
	int i;
	for(i = 0; i < 768; i++)
	{
		image[i] = img[i]; 
	}
	for(i = 0; i < 1024; i++)
	{
		logo[i] = logo1[i];
	}
}*/

void bitmap_clear(unsigned char *bitmap)
{
	int i = 0;
	for(i = 0; i < 1024; i++)
		bitmap[i] = 0x00;
}

void draw_route(unsigned char *bitmap,DIRECTION direction, uint8_t *lastKnownX, uint8_t *lastKnownY)
{
	switch(direction)
	{
		case UP_RIGHT:
			UpdateBitmap(bitmap, UP, lastKnownX, lastKnownY);
			UpdateBitmap(bitmap, RIGHT, lastKnownX, lastKnownY);
			break;
		case UP_LEFT:
			UpdateBitmap(bitmap, UP, lastKnownX, lastKnownY);
			UpdateBitmap(bitmap, LEFT, lastKnownX, lastKnownY);
			break;
		case DOWN_RIGHT:
			UpdateBitmap(bitmap, DOWN, lastKnownX, lastKnownY);
			UpdateBitmap(bitmap, RIGHT, lastKnownX, lastKnownY);
			break;
		case DOWN_LEFT:
			UpdateBitmap(bitmap, DOWN, lastKnownX, lastKnownY);
			UpdateBitmap(bitmap, LEFT, lastKnownX, lastKnownY);
			break;
		
		default:
			break;
	}
}
