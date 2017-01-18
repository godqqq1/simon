void setup() {
Serial.begin(9600);
Serial.println("Hello python.");
pinMode(9, OUTPUT);
}

void loop() {
  //if( Serial.available() ){
    //if(strcmp((char)Serial.read(),'012')==0){
     // digitalWrite(9, 1);
   // }
   String t = Serial.readString();
   int idx = t.indexOf("012",0);
    if(idx != -1){
        char temp[3];
        String pp = t.substring(5,7);
        pp.toCharArray(temp,3);
        int d = atoi(temp);
        digitalWrite(9, d);
        Serial.println(d);
    }
    else{
      idx = t.indexOf("013",0);
     if(idx != -1){
      
        digitalWrite(9, 0);
    }
     }
}
