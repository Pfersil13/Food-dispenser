#include <Arduino.h>

#include <ESP8266Wifi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <string.h>
#include <AsyncElegantOTA.h>

#include "Weight_Stuff.h"
#include "Control.h"
#include "MQTT.h"
#include "Pinout.h"
#include "RTC.h"
#include "ReadFS.h"
#include "Light.h"


#include "configAP.h"  // Sustituir con datos de vuestra red
#include "ESP8266_Utils.hpp"
#include "conversion.hpp"
#include "asyncServer.hpp"

//Server variable
AsyncWebServer server(80);

//Scale variable stuff
long Tare,TareADC;
float realMass = 100;

//Variables to make a non blocking delay
unsigned long now;
long lastMsg = 0;
unsigned int  interval =60000;

int hour, minute, second, day;

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
  
  ConnectWiFi_AP_STA(); //Call Wifi functions
  setup_mqtt();         //Call all MQTT Setups functions
  setUpRTC();
  setup_scale();      //Call all Scale Setups functions
  setupNeopixel();    //Setup LEDS :3

  
  newTareADC();                 //Tare scale
  returnFromFS();     //Return Intakes form SPIFFS
  
  //setBunchOfIntakes();

  setLeds(nivelDeposito());   //Set leds indicator 
  serverInit(); //Init Web Serverv

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop() {
  unsigned long now = millis();   //Return actual run time in ms

  //Serial.println("En el loop");
  test_conn();    //Test MQTT conection  & connect 

  if (WiFi.status() != WL_CONNECTED){
    RTCNoWifi(hour, minute , second , day);
  }
  //Structure for calling every interval time 
  if (now - lastMsg >= interval) {  
    returnIntakes(day);

    Serial.println("Hi_Ok");
    lastMsg = now;
    test_conn();
    getDate(hour, minute, second, day);  
    RevisarCalendario(hour, minute, day);
    StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION, String("IM IN"));
    returnIntakes(day);
    setLeds(nivelDeposito());
    double weight = readWeight();
    floatMsg_out(MQTT_FOOD_WEIGHT_TOPIC,weight); 
  }}