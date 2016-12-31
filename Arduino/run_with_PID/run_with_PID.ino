#include <Streaming.h>

#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <Encoder.h>
#include <Servo.h>

Servo bobbin;
Encoder pos(2,7);
double actual = 0;
double wanted = 80;
unsigned long spTimer;
double sp = 80;
unsigned long serialTimer;

PID control = PID(&actual,&sp,&wanted,3,0,.05, REVERSE);
PID_ATune tune = PID_ATune(&actual,&sp);

void setup() {
  // put your setup code here, to run once:
  bobbin.attach(6);
  Serial.begin(9600);
  serialTimer = millis();
  control.SetOutputLimits(87,93);
  control.SetMode(AUTOMATIC);
  control.SetSampleTime(50);
  tune.SetOutputStep(1);
  tune.SetControlType(1); //pid
  
}
void updateEnc() {
  actual = double(pos.read());
}

void loop() {
  while(Serial.available() > 0) {
    int data = Serial.read();
    wanted = double(data);
  }
  updateEnc();
  //control.Compute();
  int _run = tune.Runtime();
  bobbin.write(sp);
  
  if(_run) {
    Serial << tune.GetKp() << "," << tune.GetKi() << "," << tune.GetKd() << "\n";
  }
  
  

}
