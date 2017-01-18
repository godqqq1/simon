int mtime = 0;
int time = 0;
double count = 0;
double count2 = 0.0;
int bef =0;
int flag = 0;
int beftime=0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  if((time % 3) == 0){
    if(flag == 1){
      flag = 0;
      Serial.print("count==");
      Serial.println(count);
      Serial.print("RPM = ");
      count2 = count/5;
      Serial.print((count2)*20);
      Serial.println(" RPM");
      count = 0;
    }
  }
  if(time != beftime){
    beftime = time;
    flag = 1;
  }
  int level = digitalRead(9);
  Serial.println(level);
    if(level == bef){
      
    }
    else{
      count = count+1;
    }
  delay(1);
  bef = level;
  mtime = mtime + 1;
  if(mtime == 1000){
    mtime = 0;
    time = time + 1;
  }
  
}
