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
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

   DDRD|=(1<<PD5)|(1<<PD6);   //PWM Pins as Out
}


void pwm(int servo1, int servo2)
{
	int step16 = 65535; // 1/8 of 16bit number
	int step8 = 255; // 1/8 of 8bit number

	
      OCR1A=316;  //90 degree
    



	
	
		/* IF - button1 is pressed - increase the PWM duty cycle by 12.5% or 1/8 */
		// PIN 10 - yellow
		//OCR1A=(float)servo1/(float)180*step16;
		// PIN 11 - green
		//OCR1B =(float)servo2/(float)180*step16;
		// PIN 3 - red
		//OCR2B += step8;
	
}