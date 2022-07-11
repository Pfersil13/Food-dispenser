#ifndef READFS_H
    #define READFS_H

    #include <Arduino.h>
    #include "LittleFS.h"
    #include "RTC.h"

    
    void ReadIntakes();

    //Function to write ALL arrays into the non volatile memory 
    void WriteWiFi(String SSID, String PASS);
    void returnWiFi();
    void WriteIntakes();
    void WriteDispensed();
    //Function to retrun ALL intakes from the non volatile memory 
    void returnFromFS();
    
    //External  arrays to store intakes and its weights

    extern int intakes[Days][nIntakes];
    extern int intakesWeight[Days][nIntakes];
   
   //External arrays to store dispensed intakes ( 1 -> Already dispense, 0 -> Not dispensed)
    extern bool dispensed[nIntakes];
#endif


