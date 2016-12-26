#include <Streaming.h>
int power = A2;
int dir = A4;
void backward_t(int t) {
  analogWrite(power,255);
  analogWrite(dir,255);
  delay(t);
}
void forward_t(int t) {
  analogWrite(power,255);
  analogWrite(dir,0);
  delay(t);
}
void stop_t(int t) {
  analogWrite(power,0);
  analogWrite(dir,0);
  delay(t);
}
void step_t(int dir_, int t) {
  analogWrite(power,255);
  analogWrite(dir,dir_);
  delay(t);
  analogWrite(power,0);
}
void setup() {
  pinMode(A0,INPUT);
  pinMode(power,OUTPUT);
  pinMode(dir,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  //943 max
  //29 min
  //11.81in stroke = 299.974 mm stroke
  //299.974/(943-29)=0.3282 mm / unit analog sensor
  int enc = analogRead(A0);
  double pos = (enc-29)*0.3282;
  step_t(255,1000);
  stop_t(1000);
  
}

  
  




