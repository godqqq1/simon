#include <SPI.h>
#include <ESP8266WiFi.h>
byte ip[] = {192,168,1,113};
char* ssid = "RPI_ROUTER";
char* pass = "kimcoctcom123";

//Use port 23
WiFiServer server = WiFiServer(23);

void setup() {
  //init device
  WiFi.begin(ssid,pass);
  //start listening for clients
  

  Serial.begin(9600);     //For visual feedback on what's going on
  while(!Serial){
    ;   //cause Leonardo
  }
  delay(1000);
  server.begin();
  if(server.available()){
  Serial.println("Client available");
}
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  String sCommand;
  while(client.available()){
    char msg = client.read();
    sCommand.concat(msg);
  }
  Serial.println(sCommand);
  server.write("i read");
  client.write("i read2");  
  server.write("Testu \n");   
  delay(1000);
}
