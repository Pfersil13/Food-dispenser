#include <Arduino.h>
#include "Weight_Stuff.h"
#include "Control.h"
#include "WifiESP.h"
#include "MQTT.h"
#include "Pinout.h"
#include "RTC.h"

//Scale variable stuff
long Tare,TareADC;
float realMass = 100;
bool calState = 0;

//Variables to make a non blocking delay
unsigned long now;
long lastMsg = 0;
int  interval = 1000;

void setup() {
  // Marcar los pines como salida
  Serial.begin(115200);

  pinMode(stepPin, OUTPUT);   
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  setup_wifi();         //Call all WiFi Setups functions
  setup_mqtt();         //Call all MQTT Setups functions
  //setup_scale();      //Call all Scale Setups functions
  setUpRTC();           //Call all Internet RTC Setups functions
  
  charMsg_out("Hi/Hi", "Taring"); //Send char MQTT msg
  //newTareADC();                 //Tare scale
  charMsg_out("Hi", "Tared");     //Send char MQTT msg

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
    getDate();
    //nivelDeposito();
    //double weight = readWeight();
    //floatMsg_out(MQTT_FOOD_WEIGHT_TOPIC,weight); 
    addIntake(1, 0, 1, 40);
    addIntake(1, 30, 1, 40);
    addIntake(1, 0, 1, 40);
    returnIntakes(1);
    
  }
  
  //Calibration stuff. It's form Voltstone code xD
  if(calState == 1){
    newTareADC();
    delay(5000);
    cal(TareADC,realMass);
  }
}