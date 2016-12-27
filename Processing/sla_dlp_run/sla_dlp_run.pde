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
  
  fullScreen(2);
  s = new Serial(this, Serial.list()[1],9600);
  show = true;
  //set timer for first image
  timer = millis();
  //s.write(cmd);
} 

void draw(){
  
  
  println(abs(timer - millis()));
  while(s.available() > 0) {
    String r = s.readString();
    println(r);
  }
  if(show) {
    if (!shown) {
      showImage();
      timer = millis();
      shown = true;
    } 
    else if (abs(timer-millis()) >= 5000) {
      timer = millis();
      show = false;
    }
  } else {
     if (timer - millis() <= 2000) {
      nextLayer();
    } 
    
  }
 
}
void nextLayer () {
  background(0);
  cmd = 1;
  s.write("1");
  show = true;
  timer = millis();
  shown = false;
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
  println("Showing image: "+name);
  i=i+1;
}