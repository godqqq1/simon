#include <SPI.h>
#include <WiFi.h>

char *ssid = "RPI_ROUTER";          //  your network SSID (name) 
char *pass = "kimcoctcom123";   // your network password
IPAddress server('192.168.8.100');  // Google

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("123");
      client.println();
    
  }
}

void loop() {

}

