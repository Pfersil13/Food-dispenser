#include <Arduino.h>
#include "Weight_Stuff.h"
#include "Control.h"
#include "WifiESP.h"
#include "MQTT.h"
#include "Pinout.h"
#include "RTC.h"
#include "ReadFS.h"

//Scale variable stuff
long Tare,TareADC;
float realMass = 100;
bool calState = 0;

//Variables to make a non blocking delay
unsigned long now;
long lastMsg = 0;
int  interval = 2000;

int hour, minute, day;

void setup() {
  // Marcar los pines como salida
  Serial.begin(115200);
  LittleFS.begin();
   
  pinMode(stepPin, OUTPUT);   
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  setup_wifi();         //Call all WiFi Setups functions
  setup_mqtt();         //Call all MQTT Setups functions
  //setup_scale();      //Call all Scale Setups functions
  setUpRTC();           //Call all Internet RTC Setups functions
  //newTareADC();                 //Tare scale
  returnFromFS();
  Serial.println("NextIntake");

  //addIntake(11, 55, 0, 40);
  //addIntake(11, 45, 0, 40);
  //ReadIntakes(); 
  
  //WriteIntakes();
  //ReadIntakes();
}
 
void loop() {
  unsigned long now = millis();   //Return actual run time in ms
  
  test_conn();    //Test MQTT conection  & connect if not
  testWiFI();     //Test Wifi connection & connect if not
  
  //Structure for calling every interval time 
  if (now - lastMsg >= interval) {  
    lastMsg = now;
    test_conn();
    testWiFI();
    getDate(hour, minute, day);
    //RevisarCalendario(hour, minute, day);
    returnIntakes(0);
    //nivelDeposito();
    //double weight = readWeight();
    //floatMsg_out(MQTT_FOOD_WEIGHT_TOPIC,weight); 
    
    
  }
  
  //Calibration stuff. It's form Voltstone code xD
  if(calState == 1){
    newTareADC();
    delay(5000);
    cal(TareADC,realMass);
  }
}