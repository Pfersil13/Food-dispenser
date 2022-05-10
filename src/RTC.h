
#ifndef RTC_H
    #define RTC_H
        
        #include <Arduino.h>
        #include <NTPClient.h>
        #include <WiFiUdp.h>     
   
        #define nIntakes 10
        #define Days 7

        void setUpRTC();
        void getDate(int &currentHour, int &currentMinute, int &currentDay); 
        void addIntake(int hour, int minute, int day, int weight);
        void RevisarCalendario(int hour, int minute, int day);
        void returnIntakes(int day);    
        
        void newDay(int day);

        void setBunchOfIntakes();
        
#endif