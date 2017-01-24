#include <Wire.h>
#include <PV_RTD_RS232_RS485_Shield.h>
PV_RTD_RS232_RS485 my_rtds( 82, 100.0 );
PV_RTD_RS232_RS485 my_rtds2( 83, 100.0 );


void setup() {
  Serial.begin( 9600 );
  Serial.println( "Starting up..." );
  
  I2C_RTD_PORTNAME.begin();
  my_rtds.Factory_Reset();
  my_rtds.Disable_All_RTD_Channels();
  my_rtds.Enable_RTD_Channel( 3, 1 );
  my_rtds.Enable_RTD_Channel( 3, 2 );
  my_rtds.Enable_RTD_Channel( 3, 3 );
  my_rtds.Enable_RTD_Channel( 3, 4 );
  my_rtds.Set_RTD_SPS( 20 );
  my_rtds.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 1, 64 );
    my_rtds.Set_RTD_Idac( 3, 2, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 2, 64 );
    my_rtds.Set_RTD_Idac( 3, 3, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 3, 64 );
    my_rtds.Set_RTD_Idac( 3, 4, 0.000250 );
  my_rtds.Set_RTD_PGA( 3, 4, 64 );
  
  my_rtds2.Factory_Reset();
  my_rtds2.Disable_All_RTD_Channels();
  my_rtds2.Enable_RTD_Channel( 3, 1 );
  my_rtds2.Enable_RTD_Channel( 3, 2 );
  my_rtds2.Enable_RTD_Channel( 3, 3 );
  my_rtds2.Enable_RTD_Channel( 3, 4 );
  my_rtds2.Set_RTD_SPS( 20 );
  my_rtds2.Set_RTD_Idac( 3, 1, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 1, 64 );
  my_rtds2.Set_RTD_Idac( 3, 2, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 2, 64 );
  my_rtds2.Set_RTD_Idac( 3, 3, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 3, 64 );
  my_rtds2.Set_RTD_Idac( 3, 4, 0.000250 );
  my_rtds2.Set_RTD_PGA( 3, 4, 64 );
  delay( 3000 );
}


void loop() {
  // Read the temperature and display the results
  float t = my_rtds.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print("1-1:");
  Serial.println( t, 6 );
t = my_rtds.Get_RTD_Temperature_degC( 3, 2 );
  Serial.print("1-2:");
  Serial.println( t, 6 );
  t = my_rtds.Get_RTD_Temperature_degC( 3, 3 );
  Serial.print("1-3:");
  Serial.println( t, 6 );
  t = my_rtds.Get_RTD_Temperature_degC( 3, 4 );
  Serial.print("1-4:");
  Serial.println( t, 6 );
  t = my_rtds2.Get_RTD_Temperature_degC( 3, 1 );
  Serial.print("2-1:");
  Serial.println( t, 6 );
  t = my_rtds2.Get_RTD_Temperature_degC( 3, 2 );
  Serial.print("2-2:");
  Serial.println( t, 6 );
  
  // Add a delay to allow the shield to take a new measurement.
  // Set this delay to 6600 if using 5 samples-per-second
  delay( 1600 );
}


