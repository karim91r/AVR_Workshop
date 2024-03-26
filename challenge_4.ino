#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char num=0;
ISR(INT2_vect)
{
		if((PORTC & 0x0F) == 9)
			{
				num = 0;
			}
		else
			{
				num++;
			}
		PORTC = (PORTC & 0xF0) | (num & 0x0F);
}


void INT0_init(void)
{
  DDRB &=~(1<<2);
  GICR |=(1<<5);
  MCUCR |=(1<<ISC00) | (1<<ISC01);
  SREG |=(1<<7);
}
int main(void)
{
  INT0_init();
  DDRC |=0x0F;
  PORTC &=0xF0;
  while(1)
  {

  }
}