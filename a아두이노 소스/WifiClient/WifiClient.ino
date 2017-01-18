#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WString.h>
#include <DHT11.h>    //라이브러리 불러옴
int pin=2;            //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
char ssid[] = "RPI_ROUTER";          //  your network SSID (name) 
char pass[] = "kimcoctcom123";   // your network password
IPAddress server(192,168,8,100); 
int status = WL_IDLE_STATUS;

// Initialize the client library
 WiFiClient client;
 String readString = String(100);

void setup() {
   Serial.begin(9600);
    while(!Serial){
    ;   //cause Leonardo
  }
   Serial.println("Attempting to connect to WPA network...");
   Serial.print("SSID: ");
   Serial.println(ssid);

   WiFi.begin(ssid, pass);
   while ( WiFi.status() != WL_CONNECTED) { 
     Serial.println("Couldn't get a wifi connection");
     Serial.print("Attempting to connect to WPA SSID: ");
     Serial.println(ssid);
     delay(1000);
   } 
     Serial.println("Connected to wifi");
     Serial.println("Starting connection...");
     // if you get a connection, report back via serial:
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
  int sta = client.connect(server, 50007);
      if (sta != 0) {
        Serial.println("Is Connected");
  if(client.connected()){
    int err;
  float temp, humi;
            if((err=dht11.read(humi, temp))==0)
  {
    client.print(temp);
    }
            String line = client.readStringUntil('\r');
              Serial.println(line);
            }
  }
  else{
      Serial.println("not yet");
      }
          delay(1000);
}
