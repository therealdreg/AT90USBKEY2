#include <avr/io.h>
#include <avr/wdt.h>

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

int main (void)
{
 unsigned char data_buff[] = "Hola";
 unsigned int i = 0;

      MCUSR &= ~_BV(WDRF);
      wdt_disable();

CLKPR = (1<<CLKPCE); // set CLKPR bit to change clock prescaler
	CLKPR = 0; // no clock prescaler
  
   UCSR1B |= (1 << TXEN1); 
   
   UBRR1L = BAUD_PRESCALE; 
   UBRR1H = (BAUD_PRESCALE >> 8); 

   // Set the USART Asynchronous communication mode,
   // no parity bit, 1 stop bit, 8 bit data 
   UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|

		    (0<<USBS1)|(0<<UCSZ12)|(1<<UCSZ11)|(1<<UCSZ10);	
 
   for (;;) // Loop forever
   {
      
      while( !(UCSR1A & (1 << UDRE1)) );
      UDR1 = data_buff[i++ % (sizeof(data_buff) - 1)];

   } 

}
