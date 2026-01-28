
#include <LedControl.h>
LedControl lc = LedControl(6,3,5, 1);
signed int SnakeX[64];
signed int SnakeY[64];
int length = 3;
int direction = 0;
int r;
int r2;
int xa = random(0,7);
int ya = random(0,7);
int game = 1;

void move(){
  
  if(SnakeX[0] > 7) SnakeX[0] = 0;
  if(SnakeY[0] > 7) SnakeY[0] = 0;
  if(SnakeX[0] < 0) SnakeX[0] = 7;
  if(SnakeY[0] < 0) SnakeY[0] = 7;

  lc.setLed(0, SnakeX[0], SnakeY[0], true);
  for(int i = length; i>0; i--){
    SnakeX[i] = SnakeX[i-1];
    SnakeY[i] = SnakeY[i-1];
  }
  if(direction == 0){
    SnakeY[0] += 1;
  }if(direction == 1){
    SnakeY[0] -= 1;
  }if(direction == 2){
    SnakeX[0] += 1;
  }if(direction == 3){
    SnakeX[0] -= 1;
  }
  


  
  lc.clearDisplay(0);
  for(int i = 0; i < length; i++){
    lc.setLed(0, SnakeX[i], SnakeY[i], true);
  }

  for(int i = length-1; i>0; i--){
    if(SnakeX[0] == SnakeX[i] && SnakeY[0] == SnakeY[i]){
      game = 0;
    }
  }


}

void setup() {
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  lc.shutdown(0, false);   
  lc.setIntensity(0, 10);   
  lc.clearDisplay(0);

  SnakeX[0] = 2;
  SnakeY[0] = 3;
  SnakeX[1] = 1;
  SnakeY[1] = 3;
  SnakeX[2] = 0;
  SnakeY[2] = 3;
}
void loop() {
  if(game){ 
    lc.setLed(0,xa,ya, true);
    for(int i = length-1; i>0; i--){
      if(xa==SnakeX[i] && ya==SnakeY[i]){
        xa=random(0,7);
        ya=random(0,7);
      }
    }
    if(SnakeX[0] == xa && SnakeY[0] == ya){
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
    Serial.println(direction);
    move();
    lc.setLed(0,xa,ya, true);
    delay(300);
  }
  else{
    for(int i = length-1; i>-1; i--){
      lc.setLed(0, SnakeX[i], SnakeY[i], true);
      delay(100);
      lc.setLed(0, SnakeX[i], SnakeY[i], false);
    }
  }
}
