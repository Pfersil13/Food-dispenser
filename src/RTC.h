
#ifndef RTC_H
    #define RTC_H
        
        #include <Arduino.h>
        #include <NTPClient.h>
        #include <WiFiUdp.h>     
   
        #define nIntakes 4
        #define EEPROM_SIZE 70

        void setUpRTC();
        void getDate();
        void addIntake(int hour, int minute, int day, int weight);
        void RevisarCalendario(int hour, int minute, int day);
        void returnIntakes(int day);
        void storeToEEPROM(int day);
        void returnFromEEPROM();
        void cleanEEPROM(int day);
        
#endif