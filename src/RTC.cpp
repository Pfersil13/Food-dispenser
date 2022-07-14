#include "RTC.h"
#include "MQTT.h"
#include <EEPROM.h>
#include <Control.h>
#include "ReadFS.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

//A lot of arrays to store intakes and its weights
int intakes[Days][nIntakes];
int intakesWeight[Days][nIntakes];

//All an array to see if that intake is already taken
bool dispensed[nIntakes] ;


unsigned int previoustime = 0;

int previousDay;
///////////////////////////////////////////////////////////////
//¿Need explanation?
///////////////////////////////////////////////////////////////
void setUpRTC(){
// Initialize a NTPClient to get 
Serial.println();
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
  for(int i = 0; i < nIntakes; i++){  
    if(intakes[day][i] != 0){
      dispensed[i] = 0;
        }else{
      dispensed[i] = 1;
    }}

WriteDispensed();
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void getDate(int &currentHour, int &currentMinute, int &currentSecond , int &currentDay){

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
  
currentSecond = timeClient.getSeconds(); 

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
    for(int i = 0; i < nIntakes; i++){
        StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,String("IN 0"));
        if(dispensed[i] == 0 && intakes[day][i] <=  minsDay){
          dispense(intakesWeight[day][i]);
          //Serial.println(intakesDomingosWeight[i]);
          dispensed[i] = 1;
          WriteDispensed();
          break;
          //intMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,intakesLunes[i]);
        }}
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void addIntake(int hour, int minute, int day, int weight){
    int minsDay = hour*60 + minute;
     Serial.println(minsDay);
     if(day == 7){
      for(int k = 0; k < Days; k++){
        for(int i=0; i < nIntakes; i++ ){
        if(intakes[k][i] == 0){
           intakes[k][i] = minsDay;
           intakesWeight[k][i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
        }}
      }
     }
     else{
     for(int i=0; i < nIntakes; i++ ){
        if(intakes[day][i] == 0){
           intakes[day][i] = minsDay;
           intakesWeight[day][i] = weight;
           dispensed[i] = 0;
           i = nIntakes + 1;
           
        }}
     }
    WriteIntakes();
    }



///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void returnIntakes(int day){
  String Intakes;
  String weights;
  String disp;
  
  for(int i=0; i < nIntakes; i++){
    Intakes +=  String(",") + String(intakes[day][i]);
    weights +=  String(",") + String(intakesWeight[day][i]);
    disp +=  String(",") + String(dispensed[i]); 
    }

StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,Intakes);
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,weights);
StringMsg_out(MQTT_INATAKES_CONFIG_CONFIRMATION,disp);
}


void erase(){
for(int k = 0; k < Days;k++){
    for(int i=0; i < nIntakes; i++ ){
      intakes[k][i] = 0;
      intakesWeight[k][i] = 0;
      dispensed[i] = 1;

  }}}

void RTCNoWifi(int &hours, int &mins, int &secs , int &day){



   
  unsigned int now  = millis();
  if (now - previoustime >= 1000)
  {
    secs++;
    previoustime = now;
  }
   if (secs > 59)
  {
    mins++;
    secs = 0;
  }

  if (mins > 59)
  {
    hours++;
    mins = 0;
  }

  if (hours > 23)
  {
    hours = 0;
    day++;
  }
  if (day > 6){
    day = 0;
  }
  Serial.print(hours);
  Serial.print(":");
  Serial.print(mins);
  Serial.print(":");
  Serial.print(secs);
  Serial.print("   /   ");
  Serial.println(day);
 }
  


//JUST FOR TESTING//
//NOT IMPORTANT//
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
