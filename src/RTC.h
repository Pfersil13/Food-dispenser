
#ifndef RTC_H
    #define RTC_H
        
        #include <Arduino.h>
        #include <WiFiUdp.h>     
   
        #define nIntakes 10 //Defina a maximum number of intakes for day
        #define Days 7      //Number of days on a week xD

        void setUpRTC();    
        void getDate(int &currentHour, int &currentMinute, int &currentSecond , int &currentDay); 

        void addIntake(int hour, int minute, int day, int weight);
        void erase();
        void RevisarCalendario(int hour, int minute, int day);
        void returnIntakes(int day);    
        
        void newDay(int day);
        void setBunchOfIntakes();
        
        void RTCNoWifi(int &hours, int &mins, int &secs, int &day);
        
#endif