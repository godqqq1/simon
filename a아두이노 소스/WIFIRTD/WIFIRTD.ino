#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WString.h>
#include <PV_RTD_RS232_RS485_Shield.h>
PV_RTD_RS232_RS485 my_rtds( 82, 100.0 );
const char* ssid     = "RPI_ROUTER";
const char* password = "kimcoctcom123";
int kill = 30;
IPAddress server(192,168,8,200); 
int status = WL_IDLE_STATUS;
 WiFiClient client;
 String readString = String(100);
void setup() {
digitalWrite(2, HIGH);
  pinMode(2,OUTPUT);
  Serial.begin( 115200 );
  WiFi.begin(ssid, password);
  Serial.println( "Starting up..." );
  I2C_RTD_PORTNAME.begin();
  my_rtds.Factory_Reset();
  my_rtds.Disable_All_RTD_Channels();
  my_rtds.Enable_RTD_Channel( 3, 1 );
  my_rtds.Set_RTD_SPS( 20 );
  my_rtds.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 1, 64 );
  delay( 3000 );
  Serial.print("\n\r \n\rWorking to connect");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
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
    digitalWrite(2, LOW);
    delay(10);
    digitalWrite(2, HIGH);
    }
  float t = my_rtds.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print( "The three-wire RTD on channel 1 is reading " );
  Serial.print( t, 6 );
  Serial.println( " degrees Celsius" );
  int sta = client.connect(server, 50007);
      if (sta != 0) {
        Serial.println("Is Connected");
  if(client.connected()){
          String tmp = "rtd!" + String(t);
            client.print(tmp);
            String line = client.readStringUntil('\r');
              Serial.println(line);
            }
  }
  else{
      Serial.println("not yet");
      }
  kill = kill - 1;
  delay( 1600 );
}
