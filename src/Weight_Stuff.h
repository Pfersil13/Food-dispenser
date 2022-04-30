#ifndef WEIGHT_STUFF_H
    #define WEIGHT_STUFF_H
        
        #include <Arduino.h>
        #define EEPROM_SIZE 12      
   

        #define MAX_WEIGHT 3000

        //Max an minimus Hysteresis 
        #define HIGH_TRIG 500       
        #define LOW_TRIG 100

        
        #define maxDiff 2.5     //Max difference (g) between samples
        #define samples 15      //Number of samples
   
        #define deltaTare 50    //Range of +-deltaTare for Taring
        
        extern bool calState;
        extern long Tare;
        extern long TareADC;
        extern float dataMqtt;
        extern bool mqtt;
        extern float netValueGrams;
        void newTare();
        void cal(double TareADC, float realMass);
        double readWeight();
        void stable();
        void mean();
        void newTareADC();
        void setup_scale();
        void sendBag(String TopicToSend, char* data);
        
#endif