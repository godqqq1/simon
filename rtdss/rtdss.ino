#include <Wire.h>
#include <SPI.h>
#include <WString.h>
#include <PV_RTD_RS232_RS485_Shield.h>
PV_RTD_RS232_RS485 my_rtds( 83, 100.0 );
PV_RTD_RS232_RS485 my_rtds2( 86, 100.0 );
 String readString = String(100);
void setup() {
digitalWrite(2, HIGH);
  pinMode(2,OUTPUT);
  Serial.begin( 115200 );
  Serial.println( "Starting up..." );
  I2C_RTD_PORTNAME.begin();
  my_rtds.Factory_Reset();
  my_rtds.Disable_All_RTD_Channels();
  my_rtds.Enable_RTD_Channel( 3, 1 );
  my_rtds.Set_RTD_SPS( 20 );
  my_rtds.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 1, 64 );
  
  my_rtds2.Disable_All_RTD_Channels();
  my_rtds2.Enable_RTD_Channel( 3, 1 );
  my_rtds2.Set_RTD_SPS( 20 );
  my_rtds2.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 1, 64 );
  delay( 3000 );
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
}
void loop() {
    digitalWrite(2, LOW);
    delay(10);
    digitalWrite(2, HIGH);
  float t = my_rtds.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print( "The three-wire RTD on channel 83 is reading " );
  Serial.print( t, 6 );
  Serial.println( " degrees Celsius" );
  float t2 = my_rtds2.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print( "The three-wire RTD on channel 86 is reading " );
  Serial.print( t2, 6 );
  Serial.println( " degrees Celsius" );
  delay( 1600 );
}
