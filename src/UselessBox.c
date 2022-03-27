#include <avr/io.h>
#include <util/delay.h>

// Switch 1 on 6 (PD7)
// Switch 2 on 7 (PE6)
#define button1 PD7
#define button2 PE6

// Servo 1 on 9 (PB5)
// Servo 2 on 10 (PB6)

// Forward Declerations
void pwm_hw_setup();
void pwm(int servo1, int servo2);

int button1state = 1;
int button2state = 1;

int main()
{
     pwm_hw_setup();

    DDRC |= _BV(DDC7);

    while (1)
    {
        button1state = (PIND & (1 << button1));
        button2state = (PINE & (1 << button2));

        if (button2state)
        {
            PORTC |= _BV(PORTC7);
        }
        else
        {
            PORTC &= ~_BV(PORTC7);
        }
        pwm(90 ,90);
        _delay_ms(15);
    }
}

void pwm_hw_setup()
{
	// TIMER 0 - 8 bit
	// EXAMPLE set PWM 50%
	// OCR0A = 128;
	// OCR0B = 128;
	
	OCR0A = 0;
	OCR0B = 0;

    	// set none-inverting mode
	TCCR0A |= (1 << COM0A1);
    	// set fast PWM Mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
    	// set prescaler to 8 and starts PWM
	TCCR0B |= (1 << CS01);
	
	// TIMER 1 - 16 bit
	// OC1A and OC1B synced
	// EXAMPLE set PWM for 25% duty cycle @ 16bit
	// OCR1A = 0x3FFF;
	// set PWM for 75% duty cycle @ 16bit
	// OCR1B = 0xBFFF;
	
    	// set TOP to 16bit
	ICR1 = 0xFFFF;

	OCR0A = 0x0000;
	OCR0B = 0x0000;

	// set none-inverting mode
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set Fast PWM mode using ICR1 as TOP - MODE 14
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
    
	// START the timer with no prescaler
	TCCR1B |= (1 << CS10);

	// TIMER 2 - 8 bit
	// OC2A and OC2B synced
	// EXAMPLE - 50% DUTY
	// OCR2A = 128;

	// set PWM for 0% duty cycle
	OCR1A = 0;
	OCR1B = 0;

	// set none-inverting mode
	TCNT0 |= (1 << COM0A1);
	TCNT0 |= (1 << COM0B1);

	// set fast PWM Mode
	TCNT0 |= (1 << WGM01) | (1 << WGM00);
	// START WITH NO PRESCALER
	TCCR0B |= (1 << CS00);

	// SELECT PINS we're going out on for our schematic
	DDRB|=(1<<PB5);  /* set OC2B = Arduino_Pin3 pin as output - TIMER 2 */
	DDRB|=(1<<PB6);  /* set OC1B = Arduino_Pin10 pin as output - TIMER 1 */
	//DDRB|=(1<<PB2);  /* set OC2A = Arduino_Pin11 pin as output - TIMER 2 */
}


void pwm(int servo1, int servo2)
{
	int step16 = 65535; // 1/8 of 16bit number
	int step8 = 255; // 1/8 of 8bit number

	



	
	
		/* IF - button1 is pressed - increase the PWM duty cycle by 12.5% or 1/8 */
		// PIN 10 - yellow
		OCR1A=(float)servo1/(float)180*step16;
		// PIN 11 - green
		OCR1B =(float)servo2/(float)180*step16;
		// PIN 3 - red
		//OCR2B += step8;
	
}