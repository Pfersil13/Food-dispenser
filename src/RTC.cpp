#include "RTC.h"
#include "MQTT.h"
#include <EEPROM.h>
#include <Control.h>

    // Define NTP Client to get time
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org");

    //Week Days
    String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    //Month names
    String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    //A lot of arrays to store intakes and its weights
    int intakesLunes[nIntakes];
    int intakesLunesWeight[nIntakes];
    int intakesMartes[nIntakes];
    int intakesMartesWeight[nIntakes];
    int intakesMiercoles[nIntakes];
    int intakesMiercolesWeight[nIntakes];
    int intakesJueves[nIntakes];
    int intakesJuevesWeight[nIntakes];
    int intakesViernes[nIntakes];
    int intakesViernesWeight[nIntakes];
    int intakesSabados[nIntakes];
    int intakesSabadosWeight[nIntakes];
    int intakesDomingos[nIntakes];
    int intakesDomingosWeight[nIntakes];

    //All an array to see if that intake is already taken
    bool dispensed[nIntakes];

//¿Need explanation?
void setUpRTC(){
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);
  }


void getDate(){

timeClient.update();

time_t epochTime = timeClient.getEpochTime();
Serial.print("Epoch Time: ");
Serial.println(epochTime);
  
String formattedTime = timeClient.getFormattedTime();
Serial.print("Formatted Time: ");
Serial.println(formattedTime);  
//StringMsg_out("Hi", formattedTime);
int currentHour = timeClient.getHours();
  
int currentMinute = timeClient.getMinutes();
  
int currentSecond = timeClient.getSeconds(); 

int weekDay = timeClient.getDay();

//StringMsg_out("Hi", weekDay);
  }


void RevisarCalendario(int hour, int minute, int day){
  int minsDay = hour*60 + minute;
    switch (day){
    case 0:
      for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesDomingos[i] < minsDay){
          dispense(intakesDomingosWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 1:
      //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"Hello :3");
      for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesLunes[i] < minsDay){
          dispense(intakesLunesWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 2:
        for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesMartes[i] < minsDay){
          dispense(intakesMartesWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 3:
        for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesMiercoles[i] < minsDay){
          dispense(intakesMiercolesWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 4:
        for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesJueves[i] < minsDay){
          dispense(intakesJuevesWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 5:
        for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesViernes[i] < minsDay){
          dispense(intakesViernesWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 6:
        for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesSabados[i] < minsDay){
          dispense(intakesSabadosWeight[i]);
          dispensed[i] = 1;
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    default:
    
    break;
    }
}

//Function to add intak, not sure if needed cuz isa is working on this too
void addIntake(int hour, int minute, int day, int weight){
    int minsDay = hour*60 + minute;

    switch (day){
    case 0:
      for(int i=0; i < nIntakes; i++ ){
        if(intakesDomingos[i] == 0){
           intakesDomingos[i] = minsDay;
           intakesDomingosWeight[i] = weight;
           i = nIntakes + 1;
          
        }}
        break;
    case 1:
      //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"Hello :3");
      for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(intakesLunes[i] == 0){
           intakesLunes[i] = minsDay;
           intakesLunesWeight[i] = weight;
           i = nIntakes + 1;
           //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 2:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesMartes[i] == 0){
           intakesMartes[i] = minsDay;
           intakesMartes[i] = weight;
           i = nIntakes + 1;
        }}
        break;
    case 3:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesMiercoles[i] == 0){
           intakesMiercoles[i] = minsDay;
           intakesMiercoles[i] = weight;
           i = nIntakes + 1;
        }}
        break;
    case 4:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesJueves[i] == 0){
           intakesJueves[i] = minsDay;
           intakesJueves[i] = weight;
           i = nIntakes + 1;
        }}
        break;
    case 5:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesViernes[i] == 0){
           intakesViernes[i] = minsDay;
           intakesViernes[i] = weight;
           i = nIntakes + 1;
        }}
        break;
    case 6:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesSabados[i] == 0){
           intakesSabados[i] = minsDay;
           intakesSabados[i] = weight;
           i = nIntakes + 1;
        }}
        break;
    default:
    
    break;
}}

void returnIntakes(int day){
  String intakes;
  String weights;
  switch (day){
    case 0:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesDomingos[i]);
        weights +=  String(",") + String(intakesDomingosWeight[i]);
      }
        break;
    case 1:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesLunes[i]);
        weights +=  String(",") + String(intakesLunesWeight[i]);
      }
        break;
    case 2:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesMartes[i]);
        weights +=  String(",") + String(intakesMartesWeight[i]);
      }
        break;
    case 3:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesMiercoles[i]);
        weights +=  String(",") + String(intakesMiercolesWeight[i]);
      }
        break;
    case 4:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesJueves[i]);
        weights +=  String(",") + String(intakesJuevesWeight[i]);
      }
        break;
    case 5:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesViernes[i]);
        weights +=  String(",") + String(intakesViernesWeight[i]);
      }
        break;
    case 6:
      for(int i = 0; i < nIntakes; i++){
        intakes +=  String(",") + String(intakesSabados[i]);
        weights +=  String(",") + String(intakesSabadosWeight[i]);
      }
        break;
    default:
    
    break;
}
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakes);
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,weights);
}

void storeToEEPROM(int day){
  EEPROM.begin(EEPROM_SIZE);


  switch (day){
    case 0:
      for(int i = day; i< nIntakes; i++){
        EEPROM.put(i, intakesDomingos[i]);
      }
        break;
      case 1:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesLunes[i-day*nIntakes]);
      }
        break;
    case 2:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesMartes[i-day*nIntakes]);
      }
        break;
    case 3:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesMiercoles[i-day*nIntakes]);
      }
        break;
    case 4:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesJueves[i-day*nIntakes]);
      }
        break;
    case 5:
        for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesViernes[i-day*nIntakes]);
      }
        break;
    case 6:
        for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, intakesSabados[i-day*nIntakes]);
      }
        break;
    default:
    
    break;
}
EEPROM.end();
}





void returnFromEEPROM(){
  EEPROM.begin(EEPROM_SIZE);
  for(int i = 0; i< nIntakes; i++){
        EEPROM.get(i, intakesDomingos[i]);
      }
      for(int i = nIntakes; i< 2*nIntakes; i++){
        EEPROM.get(i, intakesLunes[i-nIntakes]);
      }
      for(int i = 2*nIntakes; i< 2*nIntakes + nIntakes; i++){
        EEPROM.get(i, intakesMartes[i-2*nIntakes]);
      }
      for(int i = 3*nIntakes; i<  3*nIntakes + nIntakes; i++){
        EEPROM.get(i, intakesMiercoles[i-3*nIntakes]);
      }
      for(int i = 4*nIntakes; i<  4*nIntakes + nIntakes; i++){
        EEPROM.get(i, intakesJueves[i-4*nIntakes]);
      }
        for(int i = 5*nIntakes; i<  5*nIntakes + nIntakes; i++){
        EEPROM.get(i, intakesViernes[i-5*nIntakes]);
      }
        for(int i = 6*nIntakes; i<  6*nIntakes + nIntakes; i++){
        EEPROM.get(i, intakesSabados[i-6*nIntakes]);
      
      }
    EEPROM.end();      
      }


void cleanEEPROM(int day){
  EEPROM.begin(EEPROM_SIZE);
  int a = 0;

  switch (day){
    case 0:
      for(int i = day; i< nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
      case 1:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    case 2:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    case 3:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    case 4:
      for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    case 5:
        for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    case 6:
        for(int i = day*nIntakes; i< day*nIntakes + nIntakes; i++){
        EEPROM.put(i, a);
      }
        break;
    default:
    
    break;
}
EEPROM.end();
}