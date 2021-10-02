#include <avr/io.h>
#include <avr/wdt.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include <util/delay.h>
int main(int argc, char **argv) 
{
	unsigned char data_buff[] = "Hi Dreg from AT90USBKEY2 \n";
	unsigned int i = 0;
	MCUSR &= ~_BV(WDRF);
	wdt_disable();
	DDRD |= _BV(DDD4);
	CLKPR = (1<<CLKPCE); 
	CLKPR = 0; 
	UCSR1B |= (1 << TXEN1);
	UBRR1L = BAUD_PRESCALE;
	UBRR1H = (BAUD_PRESCALE >> 8);
	UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|
	(0<<USBS1)|(0<<UCSZ12)|(1<<UCSZ11)|(1<<UCSZ10);
	while(1)
	{
		PORTD ^= _BV(PD4);
		_delay_ms(200); 
		while( !(UCSR1A & (1 << UDRE1)) );
		UDR1 = data_buff[i++ % (sizeof(data_buff) - 1)];
	}
	return 0;
}
