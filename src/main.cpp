#include <Arduino.h>
#include "Weight_Stuff.h"
#include "Control.h"
#include "WifiESP.h"
#include "MQTT.h"
#include "Pinout.h"
#include "RTC.h"
#include "ReadFS.h"
#include "Light.h"


//Scale variable stuff
long Tare,TareADC;
float realMass = 100;

//Variables to make a non blocking delay
unsigned long now;
long lastMsg = 0;
unsigned int  interval =5000;

int hour, minute, day;

void setup() {
  //Configure serial & little FS
  Serial.begin(115200);
  LittleFS.begin();

  //Confiugre OUTPUT & INPUTS
  pinMode(DRV_ENABLE,OUTPUT);
  pinMode(stepPin, OUTPUT);   
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
  //Pull high to disable stepper
  digitalWrite(DRV_ENABLE,HIGH);

  //IoT & others config stuff
  
  setup_wifi();         //Call all WiFi Setups functions
  setup_mqtt();         //Call all MQTT Setups functions
  setup_scale();      //Call all Scale Setups functions
  setUpRTC();           //Call all Internet RTC Setups functions
  setupNeopixel();    //Setup LEDS :3

  
  newTareADC();                 //Tare scale
  returnFromFS();     //Return Intakes form SPIFFS
  
  //setBunchOfIntakes();

  setLeds(nivelDeposito());   //Set leds indicator 
}
 
void loop() {
  unsigned long now = millis();   //Return actual run time in ms
  
  test_conn();    //Test MQTT conection  & connect if not
  testWiFI();     //Test Wifi connection & connect if not

  //Structure for calling every interval time 
  if (now - lastMsg >= interval) {  
    returnIntakes(day);

    lastMsg = now;
    test_conn();
    testWiFI();
    getDate(hour, minute, day);  
    RevisarCalendario(hour, minute, day);
    StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION, String("IM IN"));
    returnIntakes(0);
    setLeds(nivelDeposito());
    double weight = readWeight();
    floatMsg_out(MQTT_FOOD_WEIGHT_TOPIC,weight); 
  }}