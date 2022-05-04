#ifndef READFS_H
    #define READFS_H

    #include <Arduino.h>
    #include "LittleFS.h"
    #include "RTC.h"

    void ReadIntakes();
    void WriteIntakes();
    void returnFromFS();

    //A lot of arrays to store intakes and its weights

    extern int intakesLunes[nIntakes];
    extern int intakesLunesWeight[nIntakes];
    extern int intakesMartes[nIntakes];
    extern int intakesMartesWeight[nIntakes];
    extern int intakesMiercoles[nIntakes];
    extern int intakesMiercolesWeight[nIntakes];
    extern int intakesJueves[nIntakes];
    extern int intakesJuevesWeight[nIntakes];
    extern int intakesViernes[nIntakes];
    extern int intakesViernesWeight[nIntakes];
    extern int intakesSabados[nIntakes];
    extern int intakesSabadosWeight[nIntakes];
    extern int intakesDomingos[nIntakes];
    extern int intakesDomingosWeight[nIntakes];
#endif

