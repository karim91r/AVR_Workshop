#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
  unsigned char count=0;
  unsigned char sm=0;
  unsigned char mh=0;
  unsigned char hours_1=0;
  unsigned char hours_0=0;
  unsigned char minutes_0=0;
  unsigned char minutes_1=0;
  unsigned char secound_0=0;
  unsigned char secound_1=0;
ISR(TIMER0_OVF_vect)
{
  TCNT0=6;
  count++;
  if(count==4)
  {
    secound_0++;
    sm++;
    if(secound_0==10)
    {
      secound_1++;
      secound_0=0;
    }
   count=0;
  }
  if(sm==60)
  {
    sm=0;
    secound_1=0;
    mh++;
     minutes_0++;
     if(minutes_0==10)
     {
      minutes_1++;
      minutes_0=0;
     }
  }
  if(mh==60)
  {
    mh=0;
    minutes_1=0;
    hours_0++;
    if(hours_0==10)
    {
      hours_1++;
      hours_0=0;
    }

  }
}
 ISR(INT1_vect)
 { 
   TCCR0 = 0x00;
 }

 ISR(INT2_vect)
 {
    TCCR0 =0x05;
 }
 ISR(INT0_vect)
 {
     hours_1=0;
   hours_0=0;
   minutes_1=0;
   secound_0=0;
   secound_1=0;
   minutes_0=0;
   sm=0;
   mh=0;
   count=0;
 }
void Timer0_init_Normal_Mode(void)
{
  TCNT0=6;
  TCCR0 |= (1<<FOC0) | (1<<CS02) | (1<<CS00);
  TIMSK |=(1<<TOIE0);
  SREG |=(1<<7);
}
void resume_INT2(void)
{
  PORTB |=(1<<PB2);
  DDRB &=(~(1<<PB2));
  MCUCSR &=~(1<<ISC2);
  GICR |=(1<<INT2);
  SREG |=(1<<7);   
}
void Paused_INT1(void)
{
  DDRD &=~(1<<3);
  MCUCR |=(1<<ISC11) & ~(1<<ISC10);
 GICR |=(1<<INT1); 
  SREG |=(1<<7);   
}
void reset_INT0(void)
{
  DDRD &=~(1<<2);
  GICR |=(1<<6);
  MCUCR |=(1<<ISC00) | (1<<ISC01);
  SREG |=(1<<7);  
}

int main(void)
{

  DDRC |=0x0F;
  PORTC &=0xF0;
  Timer0_init_Normal_Mode();
  resume_INT2();
  Paused_INT1();
  reset_INT0();
  while(1)
  {
    PORTA= (1<<0);
    PORTC= (PORTC & 0xF0) | (hours_1 & 0x0F);
    _delay_ms(2);
    PORTA= (1<<1);
    PORTC= (PORTC & 0xF0) | (hours_0 & 0x0F);
    _delay_ms(2);  
    PORTA= (1<<2);
    PORTC= (PORTC & 0xF0) | (minutes_1 & 0x0F);
    _delay_ms(2);
    PORTA= (1<<3);
    PORTC= (PORTC & 0xF0) | (minutes_0 & 0x0F);
    _delay_ms(2);
    PORTA= (1<<4);
    PORTC= (PORTC & 0xF0) | (secound_1 & 0x0F);
    _delay_ms(2); 
    PORTA= (1<<5);
    PORTC= (PORTC & 0xF0) | (secound_0 & 0x0F);
    _delay_ms(2);                     
  }
}