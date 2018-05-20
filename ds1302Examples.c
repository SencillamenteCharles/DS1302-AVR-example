/*
 * ds1302Examples.c
 *
 * Created: 19/05/2018 07:04:55 p. m.
 *  Author: Charles
 */ 
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>

/* PINS REQUIRED
PORT D |2:RST |1:SCLK |0: IO|
PORT B |FOR VISUALIZATION OF DATA |
*/
#define set_ds1302_segs 0x80
void    set_ds1302(uint8_t command,uint8_t data);
uint8_t get_ds1302(uint8_t command,uint8_t data);
int main(void)
{
	set_ds1302(0x8E,0x00);//enable ds1302
	set_ds1302(0x8C,0x10);//año
	set_ds1302(0x88,0x12);//mes
	set_ds1302(0x86,0x23);//dia
	set_ds1302(0x84,0x01);//hora
	set_ds1302(0x82,0x45);//minutos
	set_ds1302(0x80,0x55);//segundos
	DDRB=255;
	uint8_t datax=0b10000010;
	datax|=(0b00000001 & (datax>>1)   );
	
    while(1)
    {
        	PORTB=get_ds1302(0b10000001,0);
			
	}		
}
void set_ds1302(uint8_t command,uint8_t data)
{
	//PINS CONFIGURATION
	DDRD|=0b00000111;// firtst 3 pins for the ds1302, as outputs
	PORTD&=0b11111000;// clearing the  3 pins
	PORTD|=0b00000100;//set RST for initialize comunication
	for (int i=0;i<8;i++)
	{
	  PORTD&= 0b11111110;	
	  PORTD|=(0b00000001 & (command>>i)   );
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(2);
	  PORTD|=0b00000010;//set SCLK
	  _delay_us(2);
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(1);
	}
	for (int i=0;i<8;i++)
	{
	  PORTD&= 0b11111110;	
	  PORTD|=(0b00000001 & (data>>i)   );
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(2);
	  PORTD|=0b00000010;//set SCLK
	  _delay_us(2);
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(1);
	  
	}
	PORTD&=0b11111000;// clearing the  3 pins
	_delay_us(100);
}
uint8_t get_ds1302(uint8_t command,uint8_t data)
{
	//PINS CONFIGURATION
	DDRD|=0b00000111;// first 3 pins for the ds1302, as outputs
	PORTD&=0b11111000;// clearing the  3 pins
	PORTD|=0b00000100;//set RST for initialize comunication
	for (int i=0;i<8;i++)
	{
	  PORTD&= 0b11111110;	
	  PORTD|=(0b00000001 & (command>>i)   );
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(2);
	  PORTD|=0b00000010;//set SCLK
	  _delay_us(2);
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(1);
	}	
	
	DDRD&=0b11111110;
	PORTD|=0b00000001;//enabling its pull-up
	data=0;
	for (int i=0;i<8;i++)
	{
	  data|= (( 0b00000001 & PIND   )<<i);
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(2);
	  PORTD|=0b00000010;//set SCLK
	  _delay_us(2);
	  PORTD&=0b11111101;//clear SCLK
	  _delay_us(1);
	  
	}
	PORTD&=0b11111000;// clearing the  3 pins
	_delay_us(100);
	return data;
}
