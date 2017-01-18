int mtime = 0; //와이파이모듈 전용 rpm측정기2
int time = 0;
float count = 0;
float count2 = 0.0;
int bef =0;
int flag = 0;
int beftime=0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  if((time % 1) == 0){
    if(flag == 1){
      flag = 0;
      Serial.print("count==");
      Serial.println(count);
      Serial.print("RPM = ");
      //count2 = count/9.8;
      count2 = count/6; //나누기 fan 갯수
      count2 = count2/2.06;
      Serial.print((count2)*120);
      Serial.println(" RPM");
      count = 0;
    }
  }
  if(time != beftime){
    beftime = time;
    flag = 1;
  }
  int level = digitalRead(BUILTIN_LED);
  //Serial.println(level);
    if(level == bef){
      
    }
    else{
      count = count+1;
    }
  delay(1);
  bef = level;
  mtime = mtime + 1;
  if(mtime == 500){
    mtime = 0;
    time = time + 1;
  }
  
}
