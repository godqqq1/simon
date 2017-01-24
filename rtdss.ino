#include <Wire.h>
#include <SPI.h>
#include <WString.h>
#include <PV_RTD_RS232_RS485_Shield.h>
PV_RTD_RS232_RS485 my_rtds1( 82, 100.0 );
PV_RTD_RS232_RS485 my_rtds2( 83, 100.0 );
 String readString = String(100);
void setup() {
digitalWrite(2, HIGH);
  pinMode(2,OUTPUT);
  Serial.begin( 9600 );
  Serial.println( "Starting up..." );
  I2C_RTD_PORTNAME.begin();
  my_rtds1.Factory_Reset();
  my_rtds1.Disable_All_RTD_Channels();
  my_rtds1.Enable_RTD_Channel( 3, 1 );
  my_rtds1.Set_RTD_SPS( 20 );
  my_rtds1.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds1.Set_RTD_PGA( 3, 1, 64 );
  my_rtds2.Disable_All_RTD_Channels();
  my_rtds2.Enable_RTD_Channel( 3, 1 );
  my_rtds2.Set_RTD_SPS( 20 );
  my_rtds2.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 1, 64 );
  
  delay( 3000 );
}
void loop() {
    digitalWrite(2, LOW);
    delay(10);
    digitalWrite(2, HIGH);
  float t = my_rtds1.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print( "1-1:" );
  Serial.println( t, 6 );
  t = my_rtds1.Get_RTD_Temperature_degC( 3, 2 );
  Serial.print( "1-2:" );
  Serial.println( t, 6 );
  t = my_rtds1.Get_RTD_Temperature_degC( 3, 3 );
  Serial.print( "1-3:" );
  Serial.println( t, 6 );
  t = my_rtds1.Get_RTD_Temperature_degC( 3, 4 );
  Serial.print( "1-4:" );
  Serial.println( t, 6 );
  float t2 = my_rtds2.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print( "2-1:" );
  Serial.println( t2, 6 );
  t2 = my_rtds2.Get_RTD_Temperature_degC( 3, 2 );
  Serial.print( "2-2:" );
  Serial.println( t2, 6 );
  delay( 1600 );
}
