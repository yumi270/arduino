#define SPEAKER 25
void setup() {
pinMode(SPEAKER,OUTPUT);
//speaker 扬声器
}
void loop(){
 //三回ループ
 for(int x=0;x<3;x++){
  //  1/440hz=2.273ms
  //  200/2.273=88.xx
  for(int y=0;y<88;y++){
    digitalWrite(SPEAKER,HIGH);//出力high
    delayMicroseconds(1136);//bi
    digitalWrite(SPEAKER,LOW);//出力low
    delayMicroseconds(1136);
  }
  delay(800);//0.8s
 }
 //880hz 1s=1000ms 1000/1.25=800
  for(int y=0;y<800;y++){
    digitalWrite(SPEAKER,HIGH);
    delayMicroseconds(568);//pi
    digitalWrite(SPEAKER,LOW);
    delayMicroseconds(568);
  }
  delay(200);//0.2s
}
