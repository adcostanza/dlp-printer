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

int outLow = 88;
int outHigh = 92;

PID control = PID(&actual,&sp,&wanted,1,.25,.25, REVERSE);
//PID_ATune tune = PID_ATune(&actual,&sp);

void setup() {
  // put your setup code here, to run once:
  bobbin.attach(6);
  Serial.begin(9600);
  serialTimer = millis();
  control.SetOutputLimits(outLow,outHigh);
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
    wanted += double(data);
  }
  updateEnc();
  if(abs(wanted-actual) > 10) {
    outLow = 86;
    outHigh = 96;
  control.SetOutputLimits(outLow,outHigh);
  } else {
    outLow = 88;
    outHigh = 92;
    
  control.SetOutputLimits(outLow,outHigh);
  }
  if(wanted != actual) control.Compute();
  //int _run = tune.Runtime();
  bobbin.write(sp);
  //Serial << sp << "\n";
  if(micros()-serialTimer > 1000) {
    Serial<<"Wanted: "<<wanted<<", Actual: "<<actual<<", Speed: "<<sp<<"\n";
    serialTimer = micros();
  }
  
  

}
