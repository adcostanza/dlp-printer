#include <Encoder.h>
#include <Servo.h>

Servo bobbin;
Encoder pos(2,7);
int p = 6;
unsigned long spTimer;
double sp = 40;
unsigned long serialTimer;
void setup() {
  // put your setup code here, to run once:
  bobbin.attach(p);
  Serial.begin(9600);
  spTimer = millis();
  serialTimer = millis();
}

void loop() {
  //Serial.println(millis());
  //Serial.println(spTimer);
  
  //increase speed every 1 second
  
  if((millis()-spTimer) > 500) {
    sp+= 1;
    if(sp > 120) sp = 40;
    spTimer = millis();
  }
  if((millis() -serialTimer) > 100) {
    Serial.print(sp);
    Serial.print(",");
    Serial.println(pos.read());
    serialTimer = millis();
  }
  
  bobbin.write(sp);
  // put your main code here, to run repeatedly:

}
