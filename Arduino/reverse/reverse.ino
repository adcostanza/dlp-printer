int dir = A4;
void setup() {
  // put your setup code here, to run once:
  pinMode(dir,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(dir,255);
  delay(1000);
}
