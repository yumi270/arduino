#include <WiFi.h>//WiFi library
#include <HTTPClient.h>//HTTP Client HTTP 客户端
#include "M5Atom.h"//atom matrix

//  wifi接続情報
const char  SSID[] = "JGUEST";          //"(指定されたSSID)";
const char PASSWORD[] = "Manakuru0723"; //"(指定されたパスワード)";

//  接続先ＵＲＬ
const char URL[] = "http://192.168.60.175/angle/index.php";

// HTTP Client　HTTP 客户端
HTTPClient http;

void setup() {
  Serial.begin(115200);       //  シリアル通信を開始
  M5.begin(true, false, true);  // IMUを使用
  M5.IMU.Init();                // IMUを初期化

  WiFi.begin(SSID, PASSWORD); //  Wifi接続を開始
  Serial.print("WiFi connecting");
  
  while (WiFi.status() != WL_CONNECTED) { // attempt to connect to Wifi network:// 尝试连接到 Wifi 网络：
     Serial.print(".");
     delay(100);
  }
  Serial.println(" connected"); //  接続完了
}

void loop() {
  // put your main code here, to run repeatedly:
  int button;
  char msg[128];//通常使用 128,256 的值
  float ax , ay , az ;  // 加速度
  float gx, gy, gz;
  float roll , pitch , yaw ;  // ジャイロ 陀螺仪
  float zero_roll,zero_pitch,zero_yaw;
  M5.IMU.getAccelData(&ax,&ay,&az); // 加速度を得る a = acceleration
  M5.IMU.getGyroData(&gx,&gy,&gz);  // ジャイロを得る g = gyro
  MahonyAHRSupdateIMU(gx * DEG_TO_RAD, 
                      gy * DEG_TO_RAD, 
                      gz * DEG_TO_RAD, 
                      ax, 
                      ay, 
                      az ,
                      &pitch,
                      &roll,
                      &yaw);
                      
         
  if (M5.Btn.wasPressed()){
    button=1;
    zero_roll=roll;
    zero_pitch=pitch;
    zero_yaw=yaw;
   }
   
 sprintf(msg, "%3.2f,%3.2f,%3.2f,%3.2f,%3.2f,%3.2f",roll , pitch , yaw  , zero_pitch,zero_roll,zero_yaw );
 Serial.println(msg);  
   
    int httpCode ;        //  httpのコード
      http.begin(URL);  //  httpを開始
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");//使用"application/x-www-form-urlencoded(网址编码)"内容类型,
      httpCode = http.POST(msg);  //  POSTで取得

      http.end();   //  httpを終了
      delay(10);      //  1000ms末  
      M5.update();
}
