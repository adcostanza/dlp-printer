import processing.serial.*;
import javax.swing.*; 
PImage img;
Serial s;
boolean show = true;
int i = 0;
long timer = millis();
int mode = 0;
MyThread thread;
MyThread2 thread2;
boolean found = false;
boolean started = false;
void setup() {
  background(0);
  printArray(Serial.list());
  fullScreen(2);
  s = new Serial(this, Serial.list()[1],9600);
}
void showImage() {
  String j = "";
  if(i < 10) j = "0" + str(i);
  if(i>=10) j = str(i);
  String name = "";
  name="job/out00"+j+".png";
  
  //name = "job/out0013.png";
  img = loadImage(name);
  show  = false;
  image(img, 1280/2-200, 800/2+10, 1280/2, 800/2); 
  found = false;
}
void draw(){
  if(s.available() > 0) {
    
    thread2 = new MyThread2();
    thread2.start();
  }
  if((millis() - timer) > 25000 && mode == 0) {
    mode = 1;
  }
 
  if(mode == 0) {
    
    if(show) {
      
      showImage();
      println("Showing image");
      
    }
  }
  if(mode == 1) {
    if(!started) {
      thread = new MyThread();
      thread.start();
      started = true;
    }
  background(0);
    //println("Switching layers");

    
    
    
  }
}

 public class MyThread extends Thread
 {
 
   public void start()
   {
     super.start();
   }
   public void run()
   {
      s.write(binary(1));
    //wait till in location
    while(!found) {
      println("Waiting for response");
      delay(1000);
          
    }
    delay(2000);
    timer = millis();
    i = i+1;
    mode = 0;
    show = true;
    found = false;
    started = false;
   }
 }
 public class MyThread2 extends Thread
 {
 
   public void start()
   {
     super.start();
   }
   public void run()
   {
      while(s.available() > 0) {
    String r = s.readString();
    print("From serial: ");
    println(r);
    found = true;
  }
    }
   }