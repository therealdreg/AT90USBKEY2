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
	unsigned char data_buff[] = "\n Hi Dreg from AT90USBKEY2, write 1 byte-ASCII to repeat \n";
	unsigned char byte_readed_str[] = "\n byte-ASCII readed: ";
	unsigned int i = 0;
	unsigned char read_byte = 0;
	
	MCUSR &= ~(1<<WDRF);
	wdt_disable();
	
	DDRD |= (1<<DDD4) | (1<<DDD6) | (1<<DDD5) | (1<<DDD7); 
	
	CLKPR = (1<<CLKPCE); 
	CLKPR = 0; 
	
	UCSR1B |= (1 << TXEN1) | (1 << RXEN1);
	UBRR1L = BAUD_PRESCALE;
	UBRR1H = (BAUD_PRESCALE >> 8);
	UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|
	(0<<USBS1)|(0<<UCSZ12)|(1<<UCSZ11)|(1<<UCSZ10);
	
	while(1)
	{		
		while(!(UCSR1A & (1<<RXC1)))
		{
			i = 0;
			do 
			{		
				PORTD ^= (1<<PD4);
				_delay_ms(30);
				PORTD ^= (1<<PD6);
				_delay_ms(30);
				PORTD ^= (1<<PD5);
				_delay_ms(30);
				PORTD ^= (1<<PD7);
				_delay_ms(30);
						
				if((UCSR1A & (1 << UDRE1)))
				{
					UDR1 = data_buff[i++];
				}
			} while (data_buff[i] != '\0');
		}
		read_byte = UDR1;
		
		i = 0;
		do
		{
			while( !(UCSR1A & (1 << UDRE1)) );
			UDR1 = byte_readed_str[i++];
		} while (byte_readed_str[i] != '\0');
		
		while( !(UCSR1A & (1 << UDRE1)) );
		UDR1 = read_byte;
		
		while( !(UCSR1A & (1 << UDRE1)) );
		UDR1 = '\n';
	}
	
	return 0;
}
