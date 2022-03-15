
#include <Servo.h>
Servo servo1;
Servo servo2;

const int button1 = 6;
const int button2 = 7;

int button1state = 1;
int button2state = 1;

int servo1pos = 50;
int servo2pos = 125;


void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
  servo2.attach(10);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:



  button1state = digitalRead(button1);
  button2state = digitalRead(button2);

  if (button1state == LOW) {
    if (servo1pos < 150) {


      servo1pos++;
    }
  }
  else {
    if (servo1pos >= 50) {
      servo1pos--;
    }
  }


  if (button2state == LOW) {
    if (servo2pos > 40) {
      //Add limit here
      servo2pos--;
    }
  }
  else {
    if (servo2pos <= 125) {
      servo2pos++;
    }
  }
  servo1.write(servo1pos);
  servo2.write(servo2pos);








  delay(4);
}
