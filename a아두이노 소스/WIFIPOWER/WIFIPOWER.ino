#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WString.h>
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
          client.print("ghi");
            String line = client.readStringUntil('\r');
              Serial.println(line);
            }
  }
  else{
      Serial.println("not yet");
      }
          delay(1000);
}
