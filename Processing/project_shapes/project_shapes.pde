PShape bot;
int i = 0;
void setup () {
  fullScreen(2);
  background(0);
}
void draw() {
  
  bot = loadShape("job/layer"+i+".svg");
  shape(bot, 510, 300,500,500);  // Draw at coordinate (110, 90) at size 100 x 100
  delay(3000);
  i=i+1;
}