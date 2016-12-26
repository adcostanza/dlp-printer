//A2 is green
//A4 is blue
void setup() {
  pinMode(A0,INPUT);
  pinMode(A2,OUTPUT);
  pinMode(A4,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0) {
    
  }
  
  int enc = analogRead(A0);
  //943 max
  //29 min
  //11.81in stroke = 299.974 mm stroke
  //299.974/(943-29)=0.3282 mm / unit analog sensor
  analogWrite(A2,255);
  analogWrite(A4,0);
  Serial << "0," << enc
  Serial.println();
  
  delay(500);
  //forward
  //analogWrite(A2,255);
  //analogWrite(A4,0);
  //delay(5000);
  //analogWrite(A2,255);
  //analogWrite(A4,0);
  //delay(5000);
   analogWrite(A2,0);
  analogWrite(A4,0);
  //backward
  //analogWrite(A2,255);
  //analogWrite(A4,255);
  //delay(5000);
  
}
