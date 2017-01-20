/**
 * Read a voltage.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
void setup()
{
  Serial.begin(9600);
}

void loop()
{
    int t = analogRead(A0);
    Serial.println(-125+(t*0.606));
    
}
