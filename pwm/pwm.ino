
#include <AFMotor.h>
AF_DCMotor motor1(1);
void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1,OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  if(digitalRead(A0)){
    motor1.run(FORWARD);
    motor1.setSpeed(200); 
   digitalWrite(A1,1);
  Serial.println("read : "); 
  }
  else{
   digitalWrite(A1,0); 
   motor1.run(RELEASE);
  Serial.println("no read : ");
  }
  
  delay(100);
  
}
