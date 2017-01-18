#include <SPI.h>
#include <ESP8266WiFi.h>
byte ip[] = {192,168,1,113};
char* ssid = "RPI_ROUTER";
char* pass = "kimcoctcom123";

//Use port 23
WiFiServer server = WiFiServer(23);
void setup() {
  //init device
  

  //start listening for clients
  

  Serial.begin(9600);     //For visual feedback on what's going on
  while(!Serial){
    ;   //cause Leonardo
  }
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED) { // 연결이 될 때 까지 반복
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // WPA/WAP2 네트워크에 연결

    delay(1000);
  }
  Serial.print("WiFi Connected to ");
  Serial.println(WiFi.localIP());
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
