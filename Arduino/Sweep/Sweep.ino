/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo Servo2;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);
  Servo2.attach(10);// attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 50; pos <= 138; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    Servo2.write(175-pos); // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
    myservo.write(138);
    Servo2.write(175-138);// tell servo to go to position in variable 'pos'
    delay(1000); 
  
  for (pos = 138; pos >= 50; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    Servo2.write(175-pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(50);
  Servo2.write(175-50);
  // tell servo to go to position in variable 'pos'
    delay(5000); 
}
