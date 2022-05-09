#include <Weight_Stuff.h>
#include <HX711.h>
#include <EEPROM.h>
#include "MQTT.h"
#include "Pinout.h"


HX711 scale;
float store[samples+5];               //Create a vector of size = samples + 5 
float PreMean,Mean;
double cal_factor = -416.12; //-416.12
char weight[10];

bool Sended = 1;
int address = 0;
int jk = 0;


///////////////////////////////////////////////////////////////
//Void for setting up scale
///////////////////////////////////////////////////////////////
void setup_scale(){
    //Init EEPROM
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);     //Inicialize EEPROM
  scale.power_up();   //Powering up scale
  delay(100);
  scale.set_gain(128);      //Select ADC gain
  /*EEPROM.get(address, cal_factor);  //Read EEPROM
  delay(500);
  EEPROM.get(address+1, Tare);  
  delay(500);
  EEPROM.get(address+2, TareADC);  
  delay(500);    
  Serial.print("Cal Factor: ");
  Serial.print(cal_factor);
  Serial.print(" Tare: ");
  Serial.println(Tare);
  Serial.print("TareADC: ");
  Serial.println(TareADC);*/
  if(cal_factor == 0)
    cal_factor = 1;
  scale.set_scale(cal_factor); 
  scale.power_up();  
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void newTare(){
 if (scale.wait_ready_timeout(400)) {
      float TareToStore = scale.get_units(30);    //Weight 30 times in (kg) and calculate the mean    
      EEPROM.put(address + 1, TareToStore);     //Store the value in EEPROM
      Serial.print("Tare");
      Serial.println(TareToStore);
      Tare = TareToStore;
      //return Tare;
     
    } else {
      Serial.println("Something went wrong");
  }
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void newTareADC(){
if (scale.wait_ready_timeout(1000)) {
    long TareToStore = scale.read_average(20);       //Weight 30 times (ADC) and calculate the mean    
    //EEPROM.put(address + 2, TareToStore);     //Store the value in EEPROM
    //Serial.print("TareADC");
    //Serial.println(TareToStore);
    TareADC = TareToStore;
    floatMsg_out("Hi", TareToStore);
} else {
    Serial.println("Something went wrong");
    charMsg_out("Hi", "ELSE");
  }
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void cal(double TareADC, float realMass) {
  if (scale.wait_ready_timeout(100)) {
    double reading = scale.read_average(20);      //Weight 20 times (ADC) and calculate the mean
    Serial.println(reading);
    reading = reading - TareADC;                  //Calculate Net Weight (ADC)
    Serial.println(reading);
    cal_factor = reading/realMass;         //Calculate Cal Factor
    scale.set_scale(cal_factor);                  
    calState = 0;
    EEPROM.put(address, cal_factor);              //Store Cal Factor
    Serial.print("Cal Factor:");
    Serial.println(cal_factor);

   }else{
     Serial.println("NOP");
   }
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
double readWeight(){
    long reading =  scale.read();   //Read weight (ADC) 
    //int reading = scale.get_value();
    //int median = medianFilter.AddValue(reading);        //Add values to filter and extract the result 
    long netValue = reading - TareADC;
    double netValueGrams = netValue/cal_factor;
    //Serial.println(reading);
    //Serial.println(netValue);
    return netValueGrams;
    
}