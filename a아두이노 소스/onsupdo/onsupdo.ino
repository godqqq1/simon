/**
 * Read a voltage.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

Nanoshield_ADC adc;
int channel = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("16-bit ADC Nanoshield Test - Read voltage (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();
}

void loop()
{
  int i = 0;
  float res1=0;
  float res2=0;
  while(1){
    i ++;
  
  
  if(i > 100){
    
    Serial.print(res1/102);
    Serial.println("%");
    Serial.print(res2/104);
    Serial.println("C");
    break;
  }
  res1 = res1 +(((adc.readVoltage(0))*2.5)/10.0)*100;
  res2 = res2 +(-20+(((adc.readVoltage(1))*2.5)/10.0)*100);
  }
  
}
