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
