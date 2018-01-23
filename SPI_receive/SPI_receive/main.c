/* 
 * SPI-SLAVE.cpp * 
 * Created: 2/16/2017 10:42:51 AM 
 * Author : kun/nisi 
 * 
 * This is the receive part of an ATmega328 SPI demonstration program.
 * Connect pins 16,17,18,19,GND to an atmega328 running the send SPI program
 * it takes what is received from SPI, byte by byte and outputs it to port D.
 * Connect 8 LEDS to port D (remember resistors!!) to see the effect.
 */

#define F_CPU 8000000UL 
#include<avr/io.h> 
#include<avr/interrupt.h> 

void SPISlaveInt (void);
void InitPort (void); 	
ISR (SPI_STC_vect);
	
int main (void) { 
	SPISlaveInt(); 
	InitPort(); 
	sei();	
	
	while(1){
	}	 
}
	
void SPISlaveInt (void)
{
	//Set   MISO   as output
	DDRB|=(1<<PINB4);
	//Enable SPI and enable SPI interrupt
	SPCR=(1<<SPE)|(1<<SPIE);
}

void InitPort (void)
{
	//Set  PD6(OC0A) as output
	DDRD=0xFF;
}

ISR (SPI_STC_vect)
{
	//Data is sent to portD
	PORTD=SPDR;
}
