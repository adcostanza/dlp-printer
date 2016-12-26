import processing.serial.*;
PShape bot;
int num = 0;
int i = 0;
Serial s;
void setup() {
  //ize(640, 360);
  background(0);
  //fullScreen();
  printArray(Serial.list());
  s = new Serial(this, Serial.list()[1],9600);
} 

void draw(){
  
  bot = loadShape("job/layer"+i+".svg");
  shape(bot, 510, 300,500,500);  // Draw at coordinate (110, 90) at size 100 x 100
  delay(30000);
  i=i+1;
}