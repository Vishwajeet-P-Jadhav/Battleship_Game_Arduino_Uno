#include <EEPROM.h>
#include <LedControl.h>

int DIN = 12; 
int CS =  11;
int CLK = 10;

int Left_Pushbutton = 2;
int Right_Pushbutton = 3;

int BombRow=0;
int nextColumn;

volatile int Battleship_position = 3; 
bool flag = false;

byte score = 0;

LedControl lc = LedControl(DIN,CLK,CS,1);

void setup() {
Serial.begin(9600);  

lc.shutdown(0,false);       
lc.setIntensity(0,4);       
lc.clearDisplay(0);    

attachInterrupt(digitalPinToInterrupt(Left_Pushbutton), MoveLeft, FALLING);
attachInterrupt(digitalPinToInterrupt(Right_Pushbutton), MoveRight, FALLING);

Serial.print("Previous High Score : ");
delay(2000);
Serial.println(EEPROM.read(0));
delay(1000);

for(int j=1;j<=2;j++){
   byte a[8] = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
   printPattern(a);
   delay(100);
   byte b[8] = {0x00,0x00,0x3C,0x24,0x24,0x3C,0x00,0x00};
   printPattern(b);
   delay(100);
   byte c[8] = {0x00,0x7E,0x42,0x42,0x42,0x42,0x7E,0x00};
   printPattern(c);
   delay(100);
   byte d[8] = {0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
   printPattern(d);
   delay(100);
   byte e[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
   printPattern(e);
   delay(100);
   }

lc.setLed(0,7,Battleship_position,HIGH);
}

void MoveLeft(){
  if(Battleship_position > 0){
    lc.setLed(0,7,Battleship_position,LOW);
    Battleship_position --;
    lc.setLed(0,7,Battleship_position,HIGH);
    }
}

void MoveRight(){
  if(Battleship_position < 7){
    lc.setLed(0,7,Battleship_position,LOW);
    Battleship_position ++;
    lc.setLed(0,7,Battleship_position,HIGH);
  }
}

void printPattern(byte character []) {

int i = 0;
  for(i=0;i<8;i++){
    lc.setRow(0,i,character[i]);
  }
}

void sendNextBomb(){
  nextColumn = random(0,8);
  for(BombRow=0; BombRow<6;BombRow++){
    lc.setLed(0,BombRow,nextColumn,HIGH);
    delay(100);
    lc.setLed(0,BombRow,nextColumn,LOW);
  }
  for(int a=0;a<=6;a++){
    for(int b=0;b<=6;b++){
      lc.setLed(0,a,b,LOW);
    }
  }
  flag = true;
  score ++;
}

void loop() {
  sendNextBomb();
  Serial.println(score);
  if(flag){
    lc.setLed(0,6,nextColumn,HIGH);
    flag = false;
    lc.setLed(0,6,nextColumn,LOW);
    if(nextColumn == Battleship_position){   
      delay(100);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,HIGH);
         }
      } 
      if(score > EEPROM.read(0)){
          EEPROM.write(0,score);
      }
      Serial.println("GAME OVER");
      delay(1000);
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,LOW);
         }
      } 
      lc.setIntensity(0,3);
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,HIGH);
         }
      } 
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,LOW);
         }
      } 
      lc.setIntensity(0,1);
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,HIGH);
         }
      } 
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,LOW);
         }
      } 
      lc.setIntensity(0,0);
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,HIGH);
         }
      } 
      delay(500);
      for(int a=0;a<=7;a++){
         for(int b=0;b<=7;b++){
             lc.setLed(0,a,b,LOW);
         }
      } 
      exit(0);
    } 
  }
}
