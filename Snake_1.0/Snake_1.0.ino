
#include <LedControl.h>
LedControl lc = LedControl(6,3,5, 1);
int length = 3;
int direction = 0;
int xa, ya, r, r2;
int game = 1;


struct Point{
  int x;
  int y;
};

Point Snake[64];

void move(){
  if(Snake[0].x > 7) Snake[0].x = 0;
  if(Snake[0].y > 7) Snake[0].y = 0;
  if(Snake[0].x < 0) Snake[0].x = 7;
  if(Snake[0].y < 0) Snake[0].y = 7;

  lc.setLed(0, Snake[0].x, Snake[0].y, true);
  for(int i = length; i>0; i--){
    Snake[i].x = Snake[i-1].x;
    Snake[i].y = Snake[i-1].y;
  }

  if(direction == 0){
    Snake[0].y += 1;
  }if(direction == 1){
    Snake[0].y -= 1;
  }if(direction == 2){
    Snake[0].x += 1;
  }if(direction == 3){
    Snake[0].x -= 1;
  }
  
  lc.clearDisplay(0);
  for(int i = 0; i < length; i++){
    lc.setLed(0, Snake[i].x, Snake[i].y, true);
  }
  for(int i = length-1; i>0; i--){
    if(Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y){
      game = 0;
    }
  }


}

void setup() {
  randomSeed(analogRead(0));
  xa = random(0,7);
  ya = random(0,7);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  lc.shutdown(0, false);   
  lc.setIntensity(0, 10);   
  lc.clearDisplay(0);

  Snake[0].x = 2;
  Snake[0].y = 3;
  Snake[1].x = 1;
  Snake[1].y = 3;
  Snake[2].x = 0;
  Snake[2].y = 3;
}

void loop() {
  randomSeed(analogRead(0));
  if(game){ 
    lc.setLed(0,xa,ya, true);
    for(int i = length-1; i>0; i--){
      if(xa==Snake[i].x && ya==Snake[i].y){
        xa=random(0,7);
        ya=random(0,7);
      }
    }
    if(Snake[0].x == xa && Snake[0].y == ya){
      xa = random(0,7);
      ya = random(0,7);
      length += 1;
      delay(100);
    }
    r = analogRead(4);
    r2 = analogRead(5);
    if(r <= 400 && direction != 1) direction = 0;
    else if(r >= 600 && direction != 0) direction = 1;
    if(r2 <= 400 && direction != 3) direction = 2;
    else if(r2 >= 600 && direction != 2) direction = 3;
    move();
    lc.setLed(0,xa,ya, true);
    delay(300);
  }
  else{
    for(int i = 0; i < length; i++){
      lc.setLed(0, Snake[i].x, Snake[i].y, false);
    }
    delay(200);
    for(int i = 0; i<length; i++){
      lc.setLed(0, Snake[i].x, Snake[i].y, true);
    }
    delay(200);
  }
}
