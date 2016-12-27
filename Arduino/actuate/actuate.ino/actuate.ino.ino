#include <Streaming.h>

//green is broken
//A4 is blue
//A2 on off
// A4 direction
int power = A2;
int dir = A4;
float bottom = 25;
float zero = bottom+152.4; //6in

int req = -1;

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
void stop_t(int t) {
  analogWrite(power,0);
  analogWrite(dir,0);
  delay(t);
}
void _step(int dir_) {
  analogWrite(power,255);
  analogWrite(dir,dir_);
  delay(200);
  analogWrite(power,0);
}
void nextLayer() {
  double pos = _pos();
  Serial << "Position: " << pos << "\n";
  Serial << "Stepping 0.33mm into vat \n";
  _step(255); 
}

void position(double wanted) {
  double pos = _pos();
  if (pos >= wanted - 3 && pos <= wanted + 3){ 
      _stop();
      Serial << "Close to zero\n"<< "Actual :" << pos << "\n" << "Wanted: " << wanted << "\n";
      //now fine
      if(pos >= wanted - 0.25 && pos <= wanted + 0.25) {
        Serial << "Found zero, waiting for serial\n";
        req = -1;
      } else if(pos < wanted) {
          _step(0);
      } else {
          _step(255);
      }
    }
    else if(pos < wanted) {
      forward_t(1000);
      Serial << "Actual :" << pos << "\n" << "Wanted: " << wanted << "\n\n";
    }else if (pos > wanted) {
      backward_t(1000);
      Serial << "Actual :" << pos << "\n" << "Wanted: " << wanted << "\n\n";
    }
}
double _pos() {
  int enc = analogRead(A0);
  double _pos = (enc-29)*0.3282;
  return _pos;
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
  
  
  
  while(Serial.available() > 0) {
    //serialReceived = true;
    if(req == -1) {
      req = Serial.parseInt();
      Serial <<"Command " << req << " requested from Serial\n";
    } else {
      Serial << "Waiting to complete current command\n";
    }
    
    
  }
  //position at zero
    if(req == 0) {
      position(zero);
    }
    //move up a layer
    if(req == 1) {
      nextLayer();
      req = -1;
    }
    //for positioning build liquid
    if(req == 2) {
      Serial << "Positioning 6in above zero for placement of build liquid\n";
      position(zero+150);
    }
  }
