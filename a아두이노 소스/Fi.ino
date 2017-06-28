
#include <j2thread.h>

#include <PID_v1.h>
#include <SoftwareSerial.h>
#include "DualMC33926MotorShield.h"
#include <Nanoshield_ADC.h>
#include <SPI.h>
#include <Math.h>
#define SS1 (1 << 2) //Slave Select 1 PORTB
#define SS1PORT &PORTB   

#define SS2 (1 << 1) //Slave Select 2 PORTB
#define SS2PORT &PORTB

#define SS3 (1 << 0) //Slave Select 3 PORTB
#define SS3PORT &PORTB

#define SS4 (1 << 7) //Slave Select 4 PORTD
#define SS4PORT &PORTD

const int ss1 = 10;
const int ss2 = 9;
const int ss3 = 8;
const int ss4 = 7;
float ft=0;
Nanoshield_ADC adc[4] = { 0x48, 0x49, 0x4A, 0x4B };
int channel = 0;
DualMC33926MotorShield md;

int encoderPin1 = 2;
int encoderPin2 = 3;
//Define Variables we'll be connecting to
double Setpoint1,Setpoint2, Input1, Output1, Input2, Output2;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
float before = 1;
float noww = 1;
//Specify the links and initial tuning parameters
double Kp1=0.5, Ki1=1, Kd1=0.7;   //팬pid 설정값
double Kp2=1.5, Ki2=3, Kd2=2;       //mov pid 설정값
//double Kp2=1.5, Ki2=5, Kd2=3;
//double Kp=0.28, Ki=4, Kd=0;
//double Kp=5, Ki=0, Kd=0;

PID myPID1(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, Kp2, Ki2, Kd2, DIRECT);

//Method to write to the DAC,using  digitalWrite for slave select
double Speed(double den, double pre){
  if(pre <0){
    pre = 0;
}
double q = 359.1 * 0.7 * pow(33.66,2.0) * sqrt((den*0.06242797)*(pre*0.004018647)); // 팬속도 구하는 공식
double v = (q/2.204622)/((den)*(1.15*0.5)); // 최종 속도
return v;
}
void writeMCP492x(uint16_t data,uint8_t slave_select) { // 볼티지 주는 함수이므로 무시
  // Take the top 4 bits of config and the top 4 valid bits (data is actually a 12 bit number) 
  //and OR them together
  uint8_t top_msg = (0x30 & 0xF0) | (0x0F & (data >> 8));

  // Take the bottom octet of data
  uint8_t lower_msg = (data & 0x00FF);

  // Select our DAC, Active LOW
  digitalWrite(slave_select, LOW);

  // Send first 8 bits
  SPI.transfer(top_msg);
  // Send second 8 bits
  SPI.transfer(lower_msg);

  //Deselect DAC
  digitalWrite(slave_select, HIGH);
}


//Method to write to the DAC, using direct port for slave select
void writeMCP492x(uint16_t data,uint8_t ss,volatile uint8_t* slave_port) { // 마찬가지 무시
  // Take the top 4 bits of config and the top 4 valid bits (data is actually a 12 bit number) 
  //and OR them together
  uint8_t top_msg = (0x30 & 0xF0) | (0x0F & (data >> 8));

  // Take the bottom octet of data
  uint8_t lower_msg = (data & 0x00FF);

  // Select our DAC, Active LOW
  *slave_port &= ~ss;

  // Send first 8 bits
  SPI.transfer(top_msg);
  // Send second 8 bits
  SPI.transfer(lower_msg);

  //Deselect DAC
  *slave_port |= ss;
}
bool led1=false;
void setup() {
  pinMode (ss1, OUTPUT);
  pinMode (ss2, OUTPUT);
  pinMode (ss3, OUTPUT);
  pinMode (ss4, OUTPUT);

  // initialize SPI:
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  writeMCP492x(2055, SS1, SS1PORT);
  writeMCP492x(2055, SS2, SS2PORT);
  writeMCP492x(2055, SS3, SS3PORT);
  Serial.begin (9600);
  Input1 = 0.0;
  Input2 = 0.0;
  Setpoint1 = 0;
  Setpoint2 = 0;

  //turn the PID on
  myPID1.SetMode(AUTOMATIC);
  myPID1.SetSampleTime(0.1);
  myPID2.SetMode(AUTOMATIC);
  myPID2.SetSampleTime(0.1);
  for (int i = 0; i < 2; i++) {
    adc[i].begin();
    adc[i].setGain(GAIN_TWO);
}
add_thread(new J2ThreadUnit(&loop1));
add_thread(new J2ThreadUnit(&loop2));
}

int p1 = 2054;
int p2 = 2054;
int p3 = 3300;
int tr=0;

double c1 = 0;
double c2 = 0;
double c3 = 0;
double c4 = 0;
float res3=0;
float res4=0;
float res6=0;
float res7=0;
int i=0;
double dens=1.2;
double bres3 = 0;
double bres4 = 0;
double bspeed = 0;
int co = 0;
int modeee=0;
double vall = 0;
double fanl = 0;

bool loop1(J2ThreadUnit* th)
{
  co ++;
  
  if(Serial.available()){ // 라즈베리파이가 보내주는 목표값들 받아오는 곳.
    co = 0;
    String tmp = Serial.readStringUntil('x');

          //Serial.print("Got some value........");
          //Serial.println(tmp);
    if(tmp.indexOf("valve1:") != -1){
        Setpoint1 = tmp.substring(7).toFloat();
        p3 = 2500;
            //Serial.println(tmp.substring(6));
        modeee = 0;
    }
    else if(tmp.indexOf("valve2:") != -1){
        Setpoint1 = tmp.substring(7).toFloat();
        p3 = 3300;
        modeee = 0;
            //Serial.println(tmp.substring(6));
    }
    else if(tmp.indexOf("fannn1:") != -1){
        Setpoint2 = tmp.substring(7).toFloat();
        p3 = 2500;
        modeee = 0;
            //Serial.println(tmp.substring(6));
    }
    else if(tmp.indexOf("fannn2:") != -1){
        Setpoint2 = tmp.substring(7).toFloat();
        p3 = 3300;
        modeee = 0;
            //Serial.println(tmp.substring(6));
    }
    else if(tmp.indexOf("density1:") != -1){
        dens = tmp.substring(9).toFloat();
        p3 = 2500;
        modeee = 0;
    }
    else if(tmp.indexOf("density2:") != -1){
        dens = tmp.substring(9).toFloat();
        p3 = 3300;
        modeee = 0;
    }
    else if(tmp.indexOf("vall1:") != -1){
        vall = tmp.substring(6).toFloat();
        p3 = 2500;
        modeee = 1;
    }
    else if(tmp.indexOf("vall2:") != -1){
        vall = tmp.substring(6).toFloat();
        p3 = 3300;
        modeee = 1;
    }
    else if(tmp.indexOf("fanl1:") != -1){
        fanl = tmp.substring(6).toFloat();
        p3 = 2500;
        modeee = 1;
    }
    else if(tmp.indexOf("fanl2:") != -1){
        fanl = tmp.substring(6).toFloat();
        p3 = 3300;
        modeee = 1;
    }
    Serial.print("chaap:");
    Serial.print(c1, 6);
    Serial.print(":");
    Serial.print(c2, 6);
    Serial.print(":");
    Serial.print(c3, 6);
    Serial.print(":");
    Serial.print(c4, 6);
    Serial.println(":");
    Serial.print("speed:");
    Serial.println(bspeed);
    Serial.print("WL:");
    Serial.println(Input1);

            //Serial.print("setpoint1: ");Serial.print(Setpoint1); Serial.print(" ");

            //Serial.print("setpoint2: ");Serial.print(Setpoint2); Serial.println(" ");


}
if(co > 24000){ // 대략 20초동안 라즈베리파이가 아무런 값을 안보내면 뎀퍼 닫기
    p3 = 3300;
}






th->sleep_micro(10);
return true; 
}

bool loop2(J2ThreadUnit* th)
{
  float res5=0;
  res3 = adc[0].read4to20mA(0);
  res4 = adc[0].read4to20mA(1);
  res6 = adc[0].read4to20mA(2);
  res7 = adc[0].read4to20mA(3);
  res5 = ((28.5/4.56058)*(adc[1].read4to20mA(0)-3.9351));
  if(res5 <= 0){
    res5 = 0;
}
  //Serial.println(res3,6);
  //Serial.println(res4,6);
  //Serial.println(res7,6);
  //Serial.println(res6,6);
  //Serial.println("------------------");
Input1 = res5+0.30000;

c1 = ((500.0000)/((16.4677)*1.0000))*((res3)-4.0123); // 차압 계산들
c2 = ((500.0000)/((16.6232)*1.0000))*((res4)-3.8568);
c3 = ((500.0000)/((16.264)*1.0000))*((res7)-4.2159)+3;
c4 = ((500.0000)/((16.4885)*1.0000))*((res6)-3.99137);
            //Serial.println(c4,6);

double speedd = Speed(dens,(c1+c2+c3)/3)/3600; // 팬속도 계산
Input2 = speedd;
bspeed = speedd;
myPID1.Compute();
           //Serial.print("Speed:");
            //Serial.print(speedd);
            //Serial.println(" m/s");
           // Serial.println(p2);
           /*if(i == 30){
            i = 0;
           
            double c1 = ((23.0000)/((263-218)*1.0000))*((res3/30.0000)-218.0000);
            double c2 = ((21.0000)/((234-203)*1.0000))*((res4/30.0000)-203.0000)-3.0000;
            //Serial.print("     Avg = ");
            //Serial.print((c1+c2)/2);
            double speedd = Speed(dens,(c1+c2)/2)/3600;
            Input2 = speedd;
            //Serial.print("chaap1:");
            //Serial.print(res3/30);
            //Serial.print("chaap2:");
            //Serial.print(res4/30);
            //Serial.print("Speed:");
            Serial.println(speedd);
            Serial.println(" m/s");
            bres3 = res3;
            bres4 = res4;
            bspeed = speedd;
            res3 = 0;
            res4 = 0;
          //Serial.println(Input2);
         
          }*/
          //Serial.print("setpoint1: ");Serial.print(Setpoint1); Serial.print(" ");
          //Serial.print("WL1: ");Serial.print(Input1); Serial.print("  Output: ");Serial.println(Output1);
          //Serial.print("setpoint2: ");Serial.print(Setpoint2); Serial.print(" ");
          //Serial.print("Speed:");
          //Serial.println(Input2);
myPID2.Compute();
          //p1 = (Output1/255.0)*(2450-2054)+ 2054;n  11
if(modeee == 0){
    p1 = (Output1/255.0)*(2670-2250)+ 2250;
            //p1 = 2670;  // 2540은 10.1 m3/h  2250 : 0%   2380 : 25%/2.5m3/h    2485: 50%/6.5m3/h  2570 75%/ 2670 : 100%
    p2 = (Output2/255.0)*(3000-2057)+2057;  
}
else{
    p1 = (vall/100) * (2670-2250)+ 2250;
    p2 = (fanl/100) * (3000-2057)+2057;
}
          //Serial.println(p1);
          //Serial.println(p2);
          //Serial.println(p3);

          //p2 =2500;
          //writeMCP492x(p1, SS2, SS2PORT);//3680 : 10v 2054 :0v  2600 : 15m3
          writeMCP492x(p3, SS1, SS1PORT);//3680 : 10v 2054 :0v   damper 2450 : full open 3200 : full close
          writeMCP492x(p1, SS2, SS2PORT);//3680 : 10v 2054 :0v
          writeMCP492x(p2, SS3, SS3PORT);//3400 : 10v 2054 :0v 

          th->sleep_milli(10);
          return true; 
      }
