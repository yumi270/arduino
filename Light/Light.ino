#include "M5Atom.h"
#define SPEAKER 25
#define MAXLED 25
#define COL_G 0xff0000  // 緑色の値
#define COL_R 0x00ff00  // 赤色の値
#define COL_B 0x0000ff  // 青色の値
#define LED_BUILTIN 25
long led_on  = 0xFFFFFF ;  //  ON表示色
long led_off = 0x000000 ;  //  OFF 表示色
boolean pattern[11][5][5] ={
  /* 1 */
  {
    { 1,1,0,1,1 },
    { 0,0,1,0,0 },
    { 0,0,1,0,0 },
    { 0,1,1,1,0 },
    { 0,0,1,0,0 },
  },
  /* 2 */
  {
    { 0,0,0,0,1 },
    { 0,0,0,0,1 },
    { 0,0,0,0,1 },
    { 0,0,0,0,1 },
    { 0,0,0,0,1 },
  },
  /* 3 */
  {
    { 0,0,1,1,1 },
    { 0,0,0,0,1 },
    { 0,0,1,1,1 },
    { 0,0,1,0,0 },
    { 0,0,1,1,1 },
  },
  /* 4 */
  {
    { 0,0,1,1,1 },
    { 0,0,0,0,1 },
    { 0,0,1,1,1 },
    { 0,0,0,0,1 },
    { 0,0,1,1,1 },
  },
  /* 5 */
  {
    { 0,0,1,0,1 },
    { 0,0,1,0,1 },
    { 0,0,1,0,1 },
    { 0,0,1,1,1 },
    { 0,0,0,0,1 },
  },
    /* 6 */
  {
    { 0,0,1,1,1 },
    { 0,0,1,0,0 },
    { 0,0,1,1,1 },
    { 0,0,0,0,1 },
    { 0,0,1,1,1 },
  },
      /* 7 */
  {
    { 0,0,1,0,0 },
    { 0,1,0,1,0 },
    { 0,0,1,0,0 },
    { 0,0,1,0,0 },
    { 1,1,1,1,1 },
  },
    /* 8 */
  {
    { 1,1,1,1,1 },
    { 1,0,0,1,1 },
    { 1,0,1,0,1 },
    { 1,1,0,0,1 },
    { 1,1,1,1,1 },
  },
      /* 9 */
  {
    { 1,0,1,0,1 },
    { 0,0,1,0,0 },
    { 1,1,1,1,1 },
    { 0,0,1,0,0 },
    { 1,0,1,0,1 },
  },
      /* 10 */
  {
    { 0,0,0,0,0 },
    { 1,1,0,1,1 },
    { 1,1,1,1,1 },
    { 0,1,1,1,0 },
    { 0,0,1,0,0 },
  },
        /* 11 */
  {
    { 0,0,0,0,0},
    { 1,1,0,1,1 },
    { 1,0,1,0,1 },
    { 0,1,0,1,0 },
    { 0,0,1,0,0 },
  }
};
// variables will change:

void setup() {
  // put your setup code here, to run once:
 
  M5.begin(true, false, true); // Serial , I2C , Display
  pinMode(SPEAKER,OUTPUT);
  delay(50);
}

int num = 0 ;
int button = 0;

void loop() {
  for(int x=0;x<88;x++){     
     digitalWrite(SPEAKER,HIGH);
     delayMicroseconds(1136);
     digitalWrite(SPEAKER,LOW);
     delayMicroseconds(1136);       
   }
     delay(1000);//0.8s
      
  if(digitalRead(39)==LOW){
    while(digitalRead(39)==LOW);
    button++;
  }
  
  if (button %2 == 0){
  // put your main code here, to run repeatedly:
  show_pattern(num);  //  サイコロのパターンを表示
  ++ num ;            //  カウントを1進める
  if(num >= 11)        //  5まできたら
    num = 0 ;         //  0に戻す
  delay(1000);       //  1000ms 待機
  M5.update();       //  M5の状態を更新
  }

}

void show_pattern(int num){

  
  int x , y , pos;
  for(y = 0 ; y < 5 ; ++y ){     // 縦
    for(x = 0 ; x < 5 ; ++x ){   // 横
      pos = y*5 + x ;            // 縦*5+横がポジション
      if(pattern[num][y][x] == 1){  //  対象numのパターンを表示
      M5.dis.drawpix(pos,led_on);
      }else{
       M5.dis.drawpix(pos,led_off);
      }
    }
  }  
}
