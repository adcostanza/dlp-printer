import processing.serial.*;
import javax.swing.*; 
int num = 0;
int cmd = 0;
int i = 0;
PImage img;
Serial s;
long timer = 0;
boolean show = false;
boolean shown = false;
void setup() {
  
  background(0);
  //fullScreen();
  printArray(Serial.list());
  //size(1280,800);
  fullScreen(2);
  s = new Serial(this, Serial.list()[1],9600);
  show = true;
  //set timer for first image
  timer = millis();
  //s.write(cmd);
} 

void draw(){
  
  while(s.available() > 0) {
    String r = s.readString();
    println(r);
  }
  
  
  if(show) {
    showImage();
    show = false;
    shown = true;
    println("Showing image "+ i);
  }
  if(abs(millis() - timer) >= 5000 && shown) {
    i = i+1;
    timer = millis();
    shown = false;
    nextLayer();
  }
  
  
 
}
void nextLayer () {
  //background(0);
  cmd = 1;
  s.write("1");
  delay(1000);
  show = true;
}
void showImage() {
  String j = "";
  if(i < 10) j = "0" + str(i);
  if(i>=10) j = str(i);
  String name ="job/out00"+j+".png";
  //name = "job/out0013.png";
  img = loadImage(name);
  //show current image
  background(0);
  image(img, 0, 0, 1280, 800);  // Draw at coordinate (110, 90) at size 100 x 100
  
}