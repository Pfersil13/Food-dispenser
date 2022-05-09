#include "RTC.h"
#include "MQTT.h"
#include <EEPROM.h>
#include <Control.h>
#include "ReadFS.h"

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
bool dispensed[nIntakes] ;


int previousDay;
///////////////////////////////////////////////////////////////
//¿Need explanation?
///////////////////////////////////////////////////////////////
void setUpRTC(){
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);
  timeClient.update();
  previousDay = timeClient.getDay();
  }

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void newDay(int day){
  switch (day){
    case 0:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesDomingos[i] != 0){
      dispensed[i] = 0;
        }else{
      dispensed[i] = 1;
    }}
  break;
    case 1:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesLunes[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    case 2:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesMartes[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    case 3:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesMiercoles[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    case 4:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesJueves[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    case 5:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesViernes[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    case 6:
  for(int i = 0; i < nIntakes; i++){
    
    if(intakesSabados[i] != 0){
      dispensed[i] = 0;
        }
    else{
      dispensed[i] = 1;
    }}
  break;
    default:
    
    break;
}
WriteDispensed();
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void getDate(int &currentHour, int &currentMinute, int &currentDay){

timeClient.update();

//time_t epochTime = timeClient.getEpochTime();
//Serial.print("Epoch Time: ");
//Serial.println(epochTime);
  
String formattedTime = timeClient.getFormattedTime();
Serial.print("Formatted Time: ");
Serial.println(formattedTime);  
//StringMsg_out("Hi", formattedTime);
currentHour = timeClient.getHours();
  
currentMinute = timeClient.getMinutes();
  
//int currentSecond = timeClient.getSeconds(); 

currentDay = timeClient.getDay();

if(currentDay > previousDay){
  newDay(currentDay);
  previousDay = currentDay;
}
//StringMsg_out("Hi", weekDay);
  }

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void RevisarCalendario(int hour, int minute, int day){
  int minsDay = hour*60 + minute;
  StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN"));
  Serial.println(minsDay);
    switch (day){
    case 0:
      for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IN 0"));
        if(dispensed[i] == 0 && intakesDomingos[i] <=  minsDay){
          dispense(intakesDomingosWeight[i]);
          //Serial.println(intakesDomingosWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 1:
      StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("Hello :3"));
      for(int i = 0; i < nIntakes; i++){
        //charMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,"IM IN");
        if(dispensed[i] == 0 && intakesLunes[i] <= minsDay){
          dispense(intakesLunesWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 2:
        for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN"));
        if(dispensed[i] == 0 && intakesMartes[i] <= minsDay){
          dispense(intakesMartesWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 3:
        for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN"));
        if(dispensed[i] == 0 && intakesMiercoles[i] <= minsDay){
          dispense(intakesMiercolesWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 4:
        for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN"));
        if(dispensed[i] == 0 && intakesJueves[i] <= minsDay){
          dispense(intakesJuevesWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 5:
        for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN VIERNES :3"));
        if(dispensed[i] == 0 && intakesViernes[i] <= minsDay){
          StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM INTAKING"));
          intMsg_out(MQTT_INATAKES_CONFIG,intakesViernesWeight[i]);
          dispense(intakesViernesWeight[i]);
          StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM OUTAKING"));
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 6:
        for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IM IN"));
        if(dispensed[i] == 0 && intakesSabados[i] <= minsDay){
          dispense(intakesSabadosWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    default:
    
    break;
    }
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void addIntake(int hour, int minute, int day, int weight){
    int minsDay = hour*60 + minute;
     Serial.println(minsDay);
    switch (day){
    case 0:
      for(int i=0; i < nIntakes; i++ ){
        if(intakesDomingos[i] == 0){
           intakesDomingos[i] = minsDay;
           intakesDomingosWeight[i] = weight;
           dispensed[i] = 0;
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
           dispensed[i] = 0;
           i = nIntakes + 1;
           //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
        break;
    case 2:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesMartes[i] == 0){
           intakesMartes[i] = minsDay;
           intakesMartesWeight[i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
        break;
    case 3:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesMiercoles[i] == 0){
           intakesMiercoles[i] = minsDay;
           intakesMiercolesWeight[i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
        break;
    case 4:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesJueves[i] == 0){
           intakesJueves[i] = minsDay;
           intakesJuevesWeight[i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
        break;
    case 5:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesViernes[i] == 0){
           intakesViernes[i] = minsDay;
           intakesViernesWeight[i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
        break;
    case 6:
        for(int i=0; i < nIntakes; i++ ){
        if(intakesSabados[i] == 0){
           intakesSabados[i] = minsDay;
           intakesSabadosWeight[i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
        break;
    default:
    
    break;
}}


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void returnIntakes(int day){
  String intakes;
  String weights;
  String disp;
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
for(int i = 0; i < nIntakes; i++){
      disp +=  String(",") + String(dispensed[i]); 
      }

StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakes);
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,weights);
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,disp);
}

void setBunchOfIntakes(){

  addIntake(5, 10, 0, 40);
  addIntake(7, 20, 0, 40);
  addIntake(10, 30, 0, 40);
  addIntake(13, 40, 0, 40);
  addIntake(15, 50, 0, 40);
  addIntake(17, 60, 0, 40);
  addIntake(20, 0, 0, 40);
  addIntake(23, 10, 0, 40);
  addIntake(24, 20, 0, 40);
  
  addIntake(5, 10, 1, 40);
  addIntake(7, 20, 1, 40);
  addIntake(10, 30, 1, 40);
  addIntake(13, 40, 1, 40);
  addIntake(15, 50, 1, 40);
  addIntake(17, 60, 1, 40);
  addIntake(20, 0, 1, 40);
  addIntake(23, 10, 1, 40);
  addIntake(24, 20, 1, 40);
  
  addIntake(5, 10, 2, 40);
  addIntake(7, 20, 2, 40);
  addIntake(10, 30,2, 40);
  addIntake(13, 40, 2, 40);
  addIntake(15, 50, 2, 40);
  addIntake(17, 60, 2, 40);
  addIntake(20, 0, 2, 40);
  addIntake(23, 10, 2, 40);
  addIntake(24, 20, 2, 40);
  
  addIntake(5, 10, 3, 40);
  addIntake(7, 20, 3, 40);
  addIntake(10, 30, 3, 40);
  addIntake(13, 40, 3, 40);
  addIntake(15, 50, 3, 40);
  addIntake(17, 60, 3, 40);
  addIntake(20, 0, 3, 40);
  addIntake(23, 10, 3, 40);
  addIntake(24, 20, 3, 40);
  
  addIntake(5, 10, 4, 40);
  addIntake(7, 20, 4, 40);
  addIntake(10, 30, 4, 40);
  addIntake(13, 40, 4, 40);
  addIntake(15, 50, 4, 40);
  addIntake(17, 60, 4, 40);
  addIntake(20, 0, 4, 40);
  addIntake(23, 10, 4, 40);
  addIntake(24, 20, 4, 40);
  
  addIntake(5, 10, 5, 40);
  addIntake(7, 20, 5, 40);
  addIntake(10, 30, 5, 40);
  addIntake(13, 40, 5, 40);
  addIntake(15, 50, 5, 40);
  addIntake(17, 60, 5, 40);
  addIntake(20, 0, 5, 40);
  addIntake(23, 10, 5, 40);
  addIntake(24, 20, 5, 40);
  
  addIntake(5, 10, 6, 40);
  addIntake(7, 20, 6, 40);
  addIntake(10, 30, 6, 40);
  addIntake(13, 40, 6, 40);
  addIntake(15, 50, 6, 40);
  addIntake(17, 60, 6, 40);
  addIntake(20, 0, 6, 40);
  addIntake(23, 10, 6, 40);
  addIntake(24, 20, 6, 40);
  
  WriteIntakes();
}

///////////////////////////////////////////////////////////////
////////////////////////USELESS STUFF//////////////////////////
///////////////////////////////////////////////////////////////
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

