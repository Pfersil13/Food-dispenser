#ifndef CONTROL_H
    #define CONTROL_H
        
        #include <Arduino.h>

        #define u_min 100
        #define u_max 500
        
        #define n_averages 10
        #define max_reading 15
        #define min_reading 5
        
        #define Kp 25
        #define nCounts 10

        #define MinimumLevel 0

        extern const int dirPin;
        extern const int stepPin;
        extern const int Trig;
        extern const int Echo;

        int ping(int TriggerPin, int EchoPin);
        int nivelDeposito();
        void motorSpeed(unsigned int interval);
        double computePID(double inp, double Setpoint);  
        void dispense(int setPoint);     
#endif