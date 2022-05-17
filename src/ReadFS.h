#ifndef READFS_H
    #define READFS_H

    #include <Arduino.h>
    #include "LittleFS.h"
    #include "RTC.h"

    
    void ReadIntakes();

    //Function to write ALL arrays into the non volatile memory 
    void WriteIntakes();
    void WriteDispensed();
    //Function to retrun ALL intakes from the non volatile memory 
    void returnFromFS();
    
    //A lot of external  arrays to store intakes and its weights

    extern int intakes[Days][nIntakes];
    extern int intakesWeight[Days][nIntakes];
   
    extern bool dispensed[nIntakes];
#endif


