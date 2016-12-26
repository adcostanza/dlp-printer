#include <Streaming.h>

//green is broken
//A4 is blue
//A2 on off
// A4 direction
int power = A2;
int dir = A4;
float bottom = 25;
float zero = bottom+152.4; //6in
float wanted;
bool serialReceived = false;
float fudge = 3;
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
void _stop() {
  analogWrite(power,0);
  analogWrite(dir,0);
}
void _step(int dir_) {
  analogWrite(power,255);
  analogWrite(dir,dir_);
  delay(200);
  analogWrite(power,0);
}

void position() {
  
}
void setup() {
  pinMode(A0,INPUT);
  pinMode(power,OUTPUT);
  pinMode(dir,OUTPUT);
  Serial.begin(9600);
  wanted = zero; //6in higher than bottom
}

void loop() {
  //943 max
  //29 min
  //11.81in stroke = 299.974 mm stroke
  //299.974/(943-29)=0.3282 mm / unit analog sensor
  int enc = analogRead(A0);
  double pos = (enc-29)*0.3282;
  
  
  while(Serial.available() > 0) {
    //serialReceived = true;
    float request = Serial.parseFloat();
    wanted = request;
  }
  
  
 
    //position before receiving serial data
    //start with gross positioning
    if (pos >= wanted - fudge && pos <= wanted + fudge){ 
      _stop();
      Serial << "Close to zero\n"<< "Actual :" << pos << "\n" << "Wanted: " << wanted << "\n";
      if(pos >= wanted - 0.25 && pos <= wanted + 0.25) {
        Serial << "Found zero\n";
        delay(2000);
      } else if(pos < wanted) {
          _step(0);
      } else {
          _step(255);
      }
    }
    else if(pos < wanted) {
      forward_t(1000);
      Serial << "Actual :" << pos << "\n" << "Wanted: " << wanted << serialReceived << "\n\n";
    }else if (pos > wanted) {
      backward_t(1000);
      Serial << "Actual :" << pos << "\n" << "Wanted: " << wanted << serialReceived << "\n\n";
    }
  }

  
  




