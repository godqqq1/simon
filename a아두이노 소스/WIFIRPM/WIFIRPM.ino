#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WString.h>
const char* ssid     = "RPI_ROUTER";
const char* password = "kimcoctcom123";
int kill = 30;
int mtime = 0; //와이파이모듈 전용 rpm측정기2
int timee = 0;
float count = 0;
float count2 = 0.0;
int bef =0;
int flag = 0;
int beftime=0;
IPAddress server(192,168,8,200); 
int status = WL_IDLE_STATUS;
 WiFiClient client;
 String readString = String(100);
void setup() {
digitalWrite(5, HIGH);
  pinMode(5,OUTPUT);
  Serial.begin( 9600 );
  WiFi.begin(ssid, password);
  Serial.println( "Starting up..." );
  Serial.print("\n\r \n\rWorking to connect");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  while(true){
      int sta = client.connect(server, 50007);
      if (sta != 0) {
        Serial.println("Is Connected");
        break;
      }
      else{
      Serial.println("not yet");
      }
      delay(1000);
     }
}
void loop() {
  if(kill <= 0){
    digitalWrite(5, LOW);
    delay(10);
    digitalWrite(5, HIGH);
    }
    if((timee % 1) == 0){
    if(flag == 1){
      flag = 0;
      Serial.print("count==");
      Serial.println(count);
      Serial.print("RPM = ");
      //count2 = count/9.8;
      count2 = count/6; //나누기 fan 갯수
      count2 = count2/2.06;
      Serial.print((count2)*60);
      Serial.println(" RPM");
      count = 0;
      
  int sta = client.connect(server, 50007);
      if (sta != 0) {
        Serial.println("Is Connected");
  if(client.connected()){
          String tmp = "rpm!" + String((count2)*60);
            client.print(tmp);
            String line = client.readStringUntil('\r');
              Serial.println(line);
            }
  }
  else{
      Serial.println("not yet");
      }
  kill = kill - 1;
    }
  }
  if(timee != beftime){
    beftime = timee;
    flag = 1;
  }
  int level = digitalRead(BUILTIN_LED);
  //Serial.println(level);
    if(level == bef){
      
    }
    else{
      count = count+1;
    }
  delay(1);
  bef = level;
  mtime = mtime + 1;
  if(mtime == 1000){
    mtime = 0;
    timee = timee + 1;
  }
}
