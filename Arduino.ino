
//input pins
int pump=8;
int fan =9;
int heater=10;
int ldrlight=11;

//relays out pins
int fan_rel=4;
int pump_rel=2;
int heater_rel=3;
int ldrlight_rel=5;

void setup() {
  
//sensors switching
  pinMode(12, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
 
  pinMode(fan_rel,OUTPUT);
  pinMode(pump_rel,OUTPUT);
  pinMode( heater_rel,OUTPUT);
  pinMode(ldrlight_rel,OUTPUT);
  
  pinMode( pump,INPUT);
  pinMode(fan ,INPUT);
  pinMode( heater,INPUT);
  pinMode( ldrlight,INPUT);

}

//int ldrValue;
void loop() {

  if (digitalRead(12)==HIGH){
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  Serial.println(String(digitalRead(12)));
  delay(200);
}
  else{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  Serial.println(String(digitalRead(12)));
  delay(200);
}


  
  //pump condition
 if (digitalRead(pump)==HIGH)
 {
  digitalWrite(pump_rel,LOW);
  }
  else
 {
  digitalWrite(pump_rel,HIGH);
  }

//fan condition
  if(digitalRead(fan)==HIGH)
 { 
  digitalWrite(heater_rel,HIGH);
  digitalWrite(fan_rel,LOW);
  }
  else
 { 
  digitalWrite(fan_rel,HIGH);
  }

  //heater condition
  if(digitalRead(heater)==HIGH)
  {
  digitalWrite(heater_rel,LOW);
  digitalWrite(fan_rel,HIGH);
    }
  else
  {
  digitalWrite(heater_rel,HIGH);
  }

  //light condition
  if(digitalRead(ldrlight)==HIGH)
  {
  digitalWrite(ldrlight_rel,LOW);
  }
  else
  {
  digitalWrite(ldrlight_rel,HIGH);
  }
  
  }
