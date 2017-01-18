#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
const double conv = 0.015875; //mm/step
int lh = 6; //steps per layer height
int known = false;
int wanted = 0;
int steps;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(50);
}

void loop() {
  while(Serial.available() > 0) {
    int data = Serial.parseInt();
    wanted += data*lh;
    if(data > 10) myStepper.setSpeed(100);
    else myStepper.setSpeed(50);
    myStepper.step(lh * data);
  }
}
