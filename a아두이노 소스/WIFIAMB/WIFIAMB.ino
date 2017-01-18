#include <ESP8266WiFi.h>
#include <DHT.h>
#include <SPI.h>
#include <WString.h>
#define DHTTYPE DHT22
#define DHTPIN  BUILTIN_LED
const char* ssid     = "RPI_ROUTER";
const char* password = "kimcoctcom123";
int kill = 30;
IPAddress server(192,168,8,200); 
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
int status = WL_IDLE_STATUS;
 WiFiClient client;
 String readString = String(100);
float humidity, temp_f;  // Values read from sensor
bool t = true;
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read senso
 
void setup(void)
{
    digitalWrite(5, HIGH);
  pinMode(5,OUTPUT);
  Serial.begin(9600);  // Serial connection from ESP-01 via 3.3v console cable
  while(!Serial){
    ;   //cause Leonardo
  }
  dht.begin();           // initialize temperature sensor
 
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
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
 void gettemperature() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
     humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(false);     // Read temperature as Fahrenheit
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
void loop(void)
{
  if(kill <= 0){
    digitalWrite(5, LOW);
    delay(10);
    digitalWrite(5, HIGH); 
  }
  gettemperature();
int sta = client.connect(server, 50007);
      if (sta != 0) {
        Serial.println("Is Connected");
  if(client.connected()){
          String tmp = "am1!" + String(temp_f);
          String hum = "am2!" + String(humidity);
          if(t == true){
            client.print(tmp);
            t = false;
          }
          else{
            client.print(hum);
            t = true;
          }
            String line = client.readStringUntil('\r');
              Serial.println(line);
            }
  }
  else{
      Serial.println("not yet");
      }
  kill = kill - 1;
  delay(1000);
} 
 
