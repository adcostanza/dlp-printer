#include <Streaming.h>

#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <Encoder.h>
#include <Servo.h>

Servo bobbin;
Encoder pos(2,7);
double actual = 0;
double wanted = 0;
unsigned long spTimer;
double sp = 90;
unsigned long serialTimer;
bool known = false;
int request = 0; //idle


PID control = PID(&actual,&sp,&wanted,1,.25,.2, REVERSE);
//PID_ATune tune = PID_ATune(&actual,&sp);

void setup() {
  // put your setup code here, to run once:
  bobbin.attach(6);
  Serial.begin(9600);
  serialTimer = millis();
  control.SetOutputLimits(88,92);
  control.SetMode(AUTOMATIC);
  control.SetSampleTime(200);
  //tune.SetOutputStep(1);
  //tune.SetControlType(0); //pid
  serialTimer = micros();
}
void updateEnc() {
  actual = double(pos.read());
}

void loop() {
  while(Serial.available() > 0) {
    int data = Serial.parseInt();
    wanted -= double(data);
  }
  updateEnc();
  if(abs(wanted-actual) > 10) {
  control.SetOutputLimits(86,95);
  } else {
  control.SetOutputLimits(88,92);
  }
  control.Compute();
  if(actual != wanted) known = false;
  if(actual == wanted && !known) {
    Serial << "1\n";
    known = true;
  }
  //int _run = tune.Runtime();
  bobbin.write(sp);
  //Serial << sp << "\n";
  if(micros()-serialTimer > 1000) {
    //Serial<<"Wanted: "<<wanted<<", Actual: "<<actual<<", Speed: "<<sp<<"\n";
    serialTimer = micros();
  }
  
  

}
