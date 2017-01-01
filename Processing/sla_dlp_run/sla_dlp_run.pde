import processing.serial.*;
import javax.swing.*; 
int num = 0;
int cmd = 0;
int i = 0;
PImage img;
Serial s;
long timer = 0;
boolean show = true;
boolean shown = false;
boolean black = true;
void setup() {
  
  background(0);
  //fullScreen();
  printArray(Serial.list());
  //size(1280,800);
  fullScreen(2);
  s = new Serial(this, Serial.list()[1],9600);
  //set timer for first image
  timer = millis();
} 

void draw(){
  
  while(s.available() > 0) {
    String r = s.readString();
    print("From serial: ");
    println(r);
  }
  
  
  if(millis()-timer < 5000) {
    
    if(show) {
      println("Showing image "+ i);
      timer = millis();
    }
    showImage();
  }
  if((millis() - timer) >= 5000 && !black) {
    background(0);
    black = true;
  }
   if((millis() - timer) >= 5000 && black) {
    background(0);
    println("Switching layers");
    i = i+1;
    
    s.write(binary(1));
    //wait till in location
    while(s.available() <= 0) {
      background(0);
      println("Waiting for response");
      delay(1000);
    }
    timer = millis();
    shown = false;
    show = true;
  }
  
  
 
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
  black=false;
  show  = false;
  shown = true;
  image(img, 0, 0, 1280, 800);  // Draw at coordinate (110, 90) at size 100 x 100
}