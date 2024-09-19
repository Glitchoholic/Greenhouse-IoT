#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor for normal 16mhz Arduino

DHT dht(DHTPIN, DHTTYPE);

// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>
//**********************upidots functions
#include "Ubidots.h"

//**********************
// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "Glitch"
#define REMOTEXY_WIFI_PASSWORD "25802580"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "599460bdbeb35613b24987ecdbda20e8"
#define REMOTEXY_ACCESS_PASSWORD "12345"
//***********************upidots sittings
const char* DEVICE_TYPE = "ubidots_1";     // Edit here your device type label
const char* UBIDOTS_TOKEN = "BBFF-LM3N7Q6a4AAFXP2PfSQxqW3wjuBbKN";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Glitch";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "25802580";      // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP); //create instance for http sending

// ***************************http sending function
void send_data_to_upidots(int temp_upi, int  hum_upi,  int moisture_upi,int light_ubi) {

  ubidots.add("temperature", temp_upi);  // Change for your variable name
  ubidots.add("humedity", hum_upi);
  ubidots.add("moisture", moisture_upi);
  ubidots.add("light", light_ubi);
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
  if (bufferSent) {
    // Do something if values were sent properly
   // Serial.println("Values sent by the device");
  }
  }
//***************************
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 415 bytes
  { 255,8,0,28,0,152,1,16,30,5,131,0,13,5,36,5,1,2,31,77,
  111,110,105,116,111,114,32,38,32,67,111,110,116,114,111,108,0,129,0,4,
  14,27,4,0,32,67,117,114,114,101,110,116,32,118,97,108,117,101,115,0,
  129,0,37,24,10,3,0,24,76,105,109,105,116,32,58,32,0,129,0,6,
  30,10,3,0,24,72,117,109,32,58,32,0,129,0,37,30,10,3,0,24,
  76,105,109,105,116,32,58,32,0,129,0,6,37,11,3,0,24,77,111,105,
  115,116,32,58,32,0,129,0,37,37,8,3,0,24,76,105,109,105,116,58,
  0,129,0,6,44,10,3,0,24,76,105,103,104,116,32,58,32,0,129,0,
  37,44,10,3,0,24,76,105,109,105,116,32,58,32,0,67,4,18,23,8,
  4,0,8,31,6,7,20,49,23,7,4,0,24,2,2,67,4,18,29,8,
  4,0,24,31,6,7,20,49,29,7,4,0,24,2,2,67,4,18,36,8,
  4,0,24,31,6,7,20,49,36,7,4,0,24,2,2,67,4,18,43,8,
  4,0,24,31,6,7,20,49,43,7,4,0,24,2,2,129,0,6,73,9,
  4,0,24,70,97,110,58,32,0,129,0,34,73,12,4,0,24,80,117,109,
  112,58,0,129,0,6,84,12,4,0,24,76,105,103,104,116,58,32,0,129,
  0,33,84,15,4,0,24,72,101,97,116,101,114,58,32,0,129,0,6,24,
  9,3,0,24,84,101,109,112,58,0,129,0,38,14,18,4,0,32,76,105,
  109,105,116,115,32,115,101,116,0,131,0,13,60,35,5,2,2,31,65,99,
  116,117,97,116,111,114,115,32,115,116,97,116,101,115,0,70,16,20,71,6,
  6,0,26,121,0,70,16,51,71,6,6,0,26,121,0,70,16,20,82,6,
  6,0,26,121,0,70,16,51,82,6,6,0,26,121,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int16_t set_temp_lim;  // 32767.. +32767 
  int16_t set_limit_hum;  // 32767.. +32767 
  int16_t set_limit_moisture;  // 32767.. +32767 
  int16_t set_limit_light;  // 32767.. +32767 

    // output variables
  char temp_val[6];  // string UTF8 end zero 
  char hum_val[6];  // string UTF8 end zero 
  char moistire_val[6];  // string UTF8 end zero 
  char light_val[6];  // string UTF8 end zero 
  uint8_t fan_led; // led state 0 .. 1 
  uint8_t pump_led; // led state 0 .. 1 
  uint8_t light_led; // led state 0 .. 1 
  uint8_t heater_led; // led state 0 .. 1 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

//remoteXY sensors

 int temp_value;
  int hum_value;
  int moistire_value;
  int ldr_value;

//soil
 
int soilValue = 0;  
int soil_limit = 0; 

//ldr


int ldrValue ;
int ldr_limit=0;

//temp and hum
float tempValue, humValue;
float temp_limit=0;
float hum_limit=0;

//actuators output pins
int pump=14;
int fan =12;
int heater=13;
int ldrlight=15;




void setup() {
  
  //remoteXY & ubidots
  RemoteXY_Init (); 
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDeviceType(DEVICE_TYPE);

  Serial.begin(9600);

  pinMode(10, OUTPUT);
 //water pump
  pinMode(pump, OUTPUT);
 //temp fan
  pinMode(fan, OUTPUT);
  //temp heater
  pinMode(heater, OUTPUT);
 //ldr light
  pinMode(ldrlight, OUTPUT);
 
  dht.begin();
  Wire.begin(2,0);
  lcd.begin();
  lcd.backlight();
}



void loop() {

   RemoteXY_Handler ();

  //read humidity
   humValue = dht.readHumidity();
   
  // Read temperature as Celsius
   tempValue = dht.readTemperature();

   //soil & ldr read
    
    digitalWrite(10, HIGH);
    ldrValue= analogRead(A0);
    delay(500);
    digitalWrite(10, LOW);
    soilValue= analogRead(A0);
    delay(500);
    
   //ldr recieve read
   /*Serial.begin(9600);
   while (Serial.available() > 0) {
    // read the incoming byte:
    ldrValue = Serial.read();
    Serial.end();
    break;
    }*/
 /* int serialRec=(Serial.readStringUntil('E')).toInt();
    if(serialRec>100)
  ldrValue = serialRec;*/ 
 

  temp_value=tempValue;
  hum_value=humValue;
  moistire_value=soilValue;
  ldr_value=ldrValue;
  
  //*******************send current value to remoteXY
  dtostrf(temp_value,0,1,RemoteXY.temp_val);
  dtostrf(hum_value,0,1,RemoteXY.hum_val);
  dtostrf(moistire_value,0,1,RemoteXY.moistire_val);
  dtostrf(ldr_value,0,1,RemoteXY.light_val);

//*******************send current value to upidots
  if(millis()%1000==0){
  send_data_to_upidots(temp_value,hum_value,moistire_value,ldr_value);
  }
  

//get limits from remoteXY
temp_limit=RemoteXY.set_temp_lim;
hum_limit= RemoteXY.set_limit_hum;
soil_limit=RemoteXY.set_limit_moisture;
ldr_limit=RemoteXY.set_limit_light;

//tempreture condition
  if (tempValue>temp_limit)
  {
    digitalWrite(fan, HIGH);
    RemoteXY.fan_led=1;
    digitalWrite(heater, LOW);
    RemoteXY.heater_led=0;
  }
  else
  {
    digitalWrite(fan, LOW);
    RemoteXY.fan_led=0;
    digitalWrite(heater, HIGH);
    RemoteXY.heater_led=1;
  }

/*humidity condition
   if (humValue>hum_limit) {
  digitalWrite(fan, HIGH);
   RemoteXY.fan_led=1;
  }*/

  
//moisture condition
  if (soilValue>soil_limit) {
  digitalWrite(pump, HIGH); 
  RemoteXY.pump_led=1;
  
  }
  else {
  digitalWrite(pump , LOW);
  RemoteXY.pump_led=0;
  }

//light condition
  if (ldrValue<ldr_limit) {
  digitalWrite(ldrlight, HIGH); 
    RemoteXY.light_led=1;
  }
  else {
  digitalWrite(ldrlight, LOW); 
   RemoteXY.light_led=0;
  }


  
  //lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(tempValue) + "   M:" + String(soilValue));
  lcd.setCursor(0, 1);
  lcd.print("H:" + String(humValue) + "   L:" + String(ldrValue));
  


}
