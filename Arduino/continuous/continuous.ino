#include <Servo.h>
Servo bobbin;
int p = 6;
void setup() {
  // put your setup code here, to run once:
  bobbin.attach(p);
  Serial.begin(9600);
}

void loop() {
  for(int g=0;g<225;g++) {
    
    bobbin.write(g);
    Serial.println(g);
    delay(500);
    
  }
  // put your main code here, to run repeatedly:

}
