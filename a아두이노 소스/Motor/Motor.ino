#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;

void stopIfFault()
{
  if (md.getFault())
  {
    Serial.println("fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual MC33926 Motor Shield");
  md.init();
  
}

void loop()
{
  md.setM1Speed(200);
    stopIfFault();
    if (abs(50)%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
  delay(2);
  
  
 
}
