#include <Control.h>
#include "MQTT.h"
#include "Weight_Stuff.h"
#include "Pinout.h"
#include "Light.h"

unsigned long lastPulse = 0;
int pulse = HIGH;

// variables externas del controlador
double Input, Output;

// variables internas del controlador
unsigned long currentTime;
double error;

///////////////////////////////////////////////////////////////
//Non blocking stepper motor control 
///////////////////////////////////////////////////////////////
void motorSpeed(unsigned int interval){
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
  }}


///////////////////////////////////////////////////////////////
//Function to compute PID (Actually P)
///////////////////////////////////////////////////////////////
double computePID(double inp, double Setpoint){     
    double error =  Setpoint - inp;
    double u = u_max - error * Kp;
        if(u < u_min)
            u = u_min;
    return u;
}
///////////////////////////////////////////////////////////////
//Calculate the level (%) of food in ¿deposito?
///////////////////////////////////////////////////////////////
int nivelDeposito(){
    int i;
    int a = 0;
    float mean; // d in Hacksterio explanation
     
    for(i=0; i<n_averages; i++){
      float reading = ping(Trig,Echo); //Call distance function
      //Serial.println(" cm" );
      delay(10);
      a= a+reading;   //Add all n values
      }
    mean = a/i;      //Calcualte mean
    if(mean < min_reading){  
      mean = 0;
    }
  
    float x = mean * 0.97236992039; // cos (13.5 deg) = 0.97236992039
    int porcentaje = 100-((x*100)/(tank_heigth));
    
    if (porcentaje < 0){
      porcentaje = 0;
    }
    intMsg_out(MQTT_FOOD_LEVEL_TOPIC, porcentaje);  //Send int MQTT msg 
    return porcentaje;    //Return value 
  }
///////////////////////////////////////////////////////////////
//Function to measure distance
///////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////
//Function to dispense x quantity of food
///////////////////////////////////////////////////////////////
void dispense(int setPoint){
  digitalWrite(DRV_ENABLE,LOW);

  int k = 0;
  int nivel = nivelDeposito();
  setLeds(nivel);
  newTareADC();
  if(nivel >= MinimumLevel){
  long lastMsg = 0;
  unsigned int  interval = 200;
  intMsg_out(MQTT_FEEDING,setPoint);
  floatMsg_out(MQTT_INATAKES_CONFIG,nivel );
  while(k < nCounts){
  unsigned long now = millis();
  //reconnect();
    if (now - lastMsg >= interval) {
      lastMsg = now;
      Input = readWeight();
      floatMsg_out(MQTT_INATAKES_CONFIG, Input);
      Output = computePID(Input, setPoint);      // calcular el controlador
    
    }
    if(Input < setPoint){
      digitalWrite(stepPin, HIGH);
      motorSpeed(Output);
    }else{
      k++;
    }}
    digitalWrite(DRV_ENABLE,HIGH);
    }}