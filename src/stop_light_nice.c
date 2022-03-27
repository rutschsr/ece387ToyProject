#include <avr/io.h>
#include <util/delay.h>

//PWM on Atmega32u using help from:
//https://extremeelectronics.co.in/avr-tutorials/servo-motor-control-by-using-avr-atmega32-microcontroller/


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
#define PRE_CONDITION_DBC(eval_expression, time_blink_delay) {}
#define POST_CONDITION_DBC(eval_expression, time_blink_delay) {}
#endif

/* C Prototypes of functions */
// Forward Declerations for those of us in C++ land
void stopLight(short green, short yellow, short red);
void my_delay_ms( unsigned int t);
short checkButtonPressed(int a);

int main (void) 
{
	//Setup DBC Preconditions and light initial setup. 
	DBC_SETUP();
	//Setup Stoplight Pins:
	DDRD |= _BV(DDD3);
	DDRD |= _BV(DDD4);
	DDRD |= _BV(DDD5);

	stopLight(1, 0, 0);//Set stoplight initial state (green)

	while(1) 
	{
		stopLight(1, 0, 0);//Set stoplight to default state (green)

		if (checkButtonPressed(PD7))//Check button pushed through debounce program
		{	

			my_delay_ms(3000);
		       //Set stoplight yellow after 3 seconds.	
			stopLight(0, 1, 0);
			my_delay_ms(2000); 
			//Set stoplight Red light after 2 second yellow.
			stopLight(0, 0, 1);
			my_delay_ms(5000); 
			//Set stoplight green again after 5 seconds on red
			stopLight(1, 0, 0);

		}
		
	}
}

/* 
 * checks when a button on the D port pressed
 */
short checkButtonPressed(int inputPin)
{
PRE_CONDITION_DBC(inputPin,6000);//Check DBC precondition (Pin is Passed in) for button pressed
	
	int button_pressed_return=0;
	button_pressed_return=0;




	if ((PIND & (1 << inputPin)) != 0)//Check if input is not zero since there is no boolean in C
	{



		/* software debounce */
		_delay_ms(15);//Debounce timer (button shouldnt have "bounce" longer than 15ms
		if ((PIND & (1 << inputPin)) != 0)
		{
	
       
      
			button_pressed_return = 1;
		}
		else {//Added to ensure that the program doesnt mess up and run the stoplight when the button wasnt pressed. Guess and check and a combination of this and
			//and button_pressed_return=0 above seemed to work to make the program stop messing up. Not entirely sure why this fixes the issue but have not seen the program
			//mess up since this code has been in place
			button_pressed_return=0;
		}
	}
	else
	{



		button_pressed_return = 0;//0 if button not pressed longer than debounce period
	}
	POST_CONDITION_DBC(button_pressed_return ==0 || button_pressed_return ==1,6000);// Check Design by contract post condition (0 or 1 value passed out)
	return button_pressed_return;//Return 0 or 1 Depending on if the button is pressed or not.
}

/* 
 * stop light functionality, takes 3 binary  values for green light, yellow light and red light.
 */
void stopLight(short green, short yellow, short red)
{
	PRE_CONDITION_DBC(green^yellow^red,6000);// Check Design by contract pre condition (only one light turned on)
	if (green)//Sets Green light
        	PORTD |= _BV(PORTD5);
	else
        	PORTD &= ~_BV(PORTD5);

	if (yellow)//Sets Yellow Light
        	PORTD |= _BV(PORTD4);
	else
        	PORTD &= ~_BV(PORTD4);

	if (red)//Sets Red Light0
        	PORTD |= _BV(PORTD3);
	else
        	PORTD &= ~_BV(PORTD3);

	POST_CONDITION_DBC(PORTD!=0,6000); //Check Design by contract post condition on (light turned on)
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
