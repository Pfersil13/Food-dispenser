#ifndef CON_H
    #define CON_H
#include "Arduino.h"


bool dia(char d, int &ndia){
    int n_dia;

    //Identificar el dia de la semana mediante numeros:
    switch(d){
        case 'L': n_dia=1;
        break;
        case 'M': n_dia=2;
        break;
        case 'X': n_dia=3;
        break;
        case 'J': n_dia=4;
        break;
        case 'V': n_dia=5;
        break;
        case 'S': n_dia=6;
        break;
        case 'D': n_dia=0;
        break;
        case 'T': n_dia=7; //Todos los dias
        break;
        default: return false; //ERROR: no se ha introducido un caracter valido
    }
    Serial.println("Dia correctamente registrado:");
    Serial.println(n_dia);
    ndia = n_dia;
    return true;

}

void peso (String p, int &_p){
    char pc[2];
    strcpy(pc, p.c_str());
    _p = atoi(pc);
    Serial.println("Peso (g):");
    Serial.println(_p);
}
bool hora(String h, int &H_, int &m_){
    //h = HH:mm
    
    char _h[5];
    strcpy(_h, h.c_str());
    
    if(strlen(_h)>5){
        return false;
    } else if (!strchr(_h,':')){
        return false;
    }

    char *H = strtok(_h, ":"); 
    char *m = strtok(NULL, ":");

    //Parametros a escoger:
    int _H = atoi(H);
    int _m = atoi(m);

        Serial.println("Int hora:");
        Serial.println(_H);
        Serial.println(_m);

        Serial.println("Char hora:");
        Serial.println(H);
        Serial.println(m);

    if(_H>23){
        Serial.println("Hora incorrecta.");
        return false;
        if(_m>59){
        Serial.println("Hora y minutos incorrectos.");
        return false;
        }
    } else if(_m>59){
        Serial.println("Minutos incorrectos.");
        return false;
    } else {
    Serial.println("Horas y minutos correctamente registrados:");
    Serial.println(H);
    Serial.println(m);
        H_=_H;
        m_=_m;
        return true;
    }
    
}

#endif
