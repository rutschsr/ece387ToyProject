#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

#define __DELAY_BACKWARD_COMPATIBLE__

/* This is the Design By Contract macros.*/
#define DBC // Can turn off these macros by commenting out this line
#ifdef DBC
/* needs to be at main since we are going to use Pin13 as our LED to warn us on assert fails */
#define DBC_SETUP() \
	/* turn on Pin 13 as we will use to indicate assertion/error failed */ \
	DDRB |= _BV(DDB5); 

#define PRE_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
	}

#define POST_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		/* half the delay off on post condition */ \
		my_delay_ms(time_blink_delay/2); \
	}
#elif
/* These are empty for when turned off */
#define DBC_SETUP() {}
#define PRE_CONDITION(eval_expression, time_blink_delay) {}
#define POST_CONDITION(eval_expression, time_blink_delay) {}
#endif

/* C Prototypes of functions */
void stop(short one, short two, short three);
void my_delay_ms( unsigned int t);
short button(int a);

int main (void) 
{
	DBC_SETUP();
	DDRD |= _BV(DDD3);
	DDRD |= _BV(DDD4);
	DDRD |= _BV(DDD5);
	initUSART();
	stop(1, 0, 0);

	while(1) 
	{
		stop(1, 0, 0);
		if (button(PD7))
		{
		//	printWord("Button Press Detected");
		//	transmitByte('\r');
		//	transmitByte('\n');

			my_delay_ms(3000); 
			stop(0, 1, 0);
			my_delay_ms(2000); 
			stop(0, 0, 1);
			my_delay_ms(5000); 
			stop(1, 0, 0);
		}
	}
}

/* 
 * checks when a button on the D port pressed
 */
short button(int a)
{
	int b=0;
	b=0;
	//printString("A");
	//transmitByte('\r');
	//transmitByte('\n');
	//_delay_ms(15);
	if ((PIND & (1 << a)) != 0)
	{
	//	printString("B");
       	//	 transmitByte('\r');
       	//	 transmitByte('\n');
		/* software debounce */
		_delay_ms(15);
		if ((PIND & (1 << a)) != 0)
		{
			printString("C");
       			 transmitByte('\r');
       			 transmitByte('\n');
			b = 1;
		}
		else {
			//Added to ensure that the program doesnt mess up and run the stoplight when the button wasnt pressed. Guess and check and a combination of this and
                        //and button_pressed_return=0 above seemed to work to make the program stop messing up. Not entirely sure why this fixes the issue but have not seen the program
                        //mess up since this code has been in place

			b=0;
		}
	}
	else
	{
	//	printString("D");
          //               transmitByte('\r');
            //             transmitByte('\n');
		b = 0;
	}

	return b;
}

/* 
 * stop light
 */
void stop(short one, short two, short three)
{
	if (one)
        	PORTD |= _BV(PORTD5);
	else
        	PORTD &= ~_BV(PORTD5);

	if (two)
        	PORTD |= _BV(PORTD4);
	else
        	PORTD &= ~_BV(PORTD4);

	if (three)
        	PORTD |= _BV(PORTD3);
	else
        	PORTD &= ~_BV(PORTD3);
}

/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int t) 
{
	unsigned int i;

	for (i=0; i<(t/10); i++) 
	{
		_delay_ms(10);
	}
/*	if (t % 10) {
		_delay_ms(t % 10);
	}*/
}
