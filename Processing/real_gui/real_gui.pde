// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial s;
int ser;
public void setup(){
  size(800, 400, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  
}

public void draw(){
  background(230);
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  
  serialList.setItems(Serial.list(),0);
  println(serialToggle);
}