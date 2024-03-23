#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
   DDRC |=(1<<0);
   DDRC |=(1<<1);
   DDRC |=(1<<2);
   DDRB |=(1<<1);
  while(1)
  {
     PORTC |=(1<<0);
     _delay_ms(500);
     PORTC &=~(1<<0);
     PORTC |=(1<<1);
     _delay_ms(500);
     PORTC &=~(1<<1);
     PORTC |=(1<<2);
     _delay_ms(500);
     PORTC &=~(1<<2);
     _delay_ms(500);
     PORTB |=(1<<1);
     _delay_ms(2000);
     PORTB &=~(1<<1);     
  }
}