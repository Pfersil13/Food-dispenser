#include <Control.h>
#include "MQTT.h"
#include "Weight_Stuff.h"
#include "Pinout.h"

unsigned long lastPulse = 0;
int pulse = HIGH;

// variables externas del controlador
double Input, Output;

// variables internas del controlador
unsigned long currentTime;
double error;


//Non blocking stepper motor control 
void motorSpeed(int interval){
    unsigned long now = micros();
  if (now - lastPulse >= interval && pulse == LOW) {
    digitalWrite(stepPin, HIGH);
    lastPulse = now;
    pulse = HIGH;
  }
  if (now - lastPulse >= interval && pulse == HIGH) {
    digitalWrite(stepPin, LOW);
    lastPulse = now;
    pulse = LOW;
  }
  
}

//Function to compute PID (Actually P)
double computePID(double inp, double Setpoint){     
    double error =  Setpoint - inp;
    double u = u_max - error * Kp;
        if(u < u_min)
            u = u_min;
    return u;
}

//Calculate the level (%) of food in ¿deposito?
int nivelDeposito(){
    int i;
    int a = 0;
    float media;
     
    for(i=0; i<n_averages; i++){
      float reading = ping(Trig,Echo); //Call distance function
      //Serial.println(" cm" );
      delay(10);
      a= a+reading;   //Add all n values
      }
    media = a/i;      //Calcualte mean
    if(media < min_reading){  
      media = min_reading;
    }
  
    int porcentaje = 100-(((media-min_reading)*100)/(max_reading-min_reading));
    
    if (porcentaje < 0){
      porcentaje = 0;
    }
    intMsg_out(MQTT_FOOD_LEVEL_TOPIC, porcentaje);  //Send int MQTT msg 
    return porcentaje;    //Return value 
  }

  //Function to measure distance
  int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //Cleaning Trigger pin
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //Generate trigger of 10 us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //Measure time between pulses in us
   
   distanceCm = duration * 10 / 292/ 2;   //Convert distances to CM. (Wouldnt be better mm?)
   return distanceCm;     //Return value
}


//Function to dispense x quantity of food
void dispense(int setPoint){
  int k = 0;
  int nivel = nivelDeposito();

  if(nivel >= MinimumLevel){
  long lastMsg = 0;
  int  interval = 200;

  while(k < nCounts){
  unsigned long now = millis();
  reconnect();
    if (now - lastMsg >= interval) {
      lastMsg = now;
      int aka = ping(Trig,Echo);
      double a =  aka;
      floatMsg_out("Hi", a);
      Input = readWeight();
      //floatMsg_out("Hi", Input);
      Output = computePID(Input, setPoint);      // calcular el controlador
    
}
  if(Input < setPoint){
     digitalWrite(stepPin, HIGH);
  motorSpeed(Output);
  }}
  }else{
    //beep

  }
  }