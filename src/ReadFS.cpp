#include "ReadFS.h"

String weekDaysSPIFFS[7]={"/Domingo.txt", "/Lunes.txt", "/Martes.txt", "/Miercoles.txt", "/Jueves.txt", "/Viernes.txt", "/Sabado.txt"};

void ReadIntakes(){
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    File file = LittleFS.open("/Domingo.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Content:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();

}

///////////////////////////////////////////////////////////////
///      Function to save SSID and PASSWORD from Wifi       ///
///////////////////////////////////////////////////////////////

void WriteWiFi(String SSID, String PASS){
   if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    
    
    File file = LittleFS.open("/Wifi_parameters.txt", "w");        
    if(!file){
        Serial.print("Failed to open file for reading ");
        Serial.println("/Wifi_parameters.txt");
        return;
    }
    
    Serial.println("File Write: ");
    file.print(SSID);     
    file.print("_");                    //Write a "_" for spliting parameters
    file.print(PASS); 
    file.print("_");
    file.close();       //Close file
}
///////////////////////////////////////////////////////////////
///   Function to return SSID and PASSWORD from WiFi saved  ///
///////////////////////////////////////////////////////////////
String S, P;
void returnWiFi(){
  if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }


    File file = LittleFS.open("/Wifi_parameters.txt", "r");     
    if(!file){
        Serial.print("Failed to open file for reading ");
        Serial.println("/Wifi_parameters.txt");
        return;
    }
    
    Serial.println("File Content:");
    while(file.available()){
        String val = file.readStringUntil('_');     //Read until splitter "_"
        String val_2 = file.readStringUntil('_');  //Read until "\n"
        S = val;
        P = val_2; 
        Serial.print(S);
        Serial.print(":");
        Serial.println(P);
    }
    file.close();
    
    
}



///////////////////////////////////////////////////////////////
///Function to write ALL arrays into the non volatile memory///
///////////////////////////////////////////////////////////////
void WriteIntakes(){
   if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    for(int k = 0; k < Days; k++){
    
    File file = LittleFS.open(weekDaysSPIFFS[k], "w");         //Open and write from start  "Domingo.txt"
    if(!file){
        Serial.print("Failed to open file for reading ");
        Serial.println(weekDaysSPIFFS[k]);
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakes[k][i]);     //Write intakes[day][i] in mins
        file.print("_");                    //Write a "_" for spliting parameters
        file.println(intakesWeight[k][i]); //Write weight [day][i] in g
      }
    file.close();       //Close file
}}
    


/////////////////////////////////////////////////////////////////
///Function to retrun ALL intakes from the non volatile memory/// 
/////////////////////////////////////////////////////////////////
void returnFromFS(){
  if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    for(int k = 0; k < Days; k++){

    File file = LittleFS.open(weekDaysSPIFFS[k], "r");        //Open and write from start  "Domingo.txt"
    if(!file){
        Serial.print("Failed to open file for reading ");
        Serial.println(weekDaysSPIFFS[k]);
        return;
    }
    
    Serial.println("File Content:");
    int i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');     //Read until splitter "_"
        String val_2 = file.readStringUntil('\n');  //Read until "\n"
        int mins = atoi(val.c_str());               //Convert String to int
        int weights = atoi(val_2.c_str());           //Convert String to int
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakes[k][i] = mins;                  //Store in array
        intakesWeight[k][i] = weights;         //Store in array
        i++;
    }
    file.close();
    }

    File file = LittleFS.open("/Dispensed.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Disp");
        return;
    }
    
    Serial.println("File Content:");
    int i = 0;
    while(file.available()){
        String val = file.readStringUntil('\n');
        bool state = atoi(val.c_str());
        Serial.print(state);
        dispensed[i] = state; 
        i++;
    }
    file.close();
    
}

void WriteDispensed(){
   if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    File file = LittleFS.open("/Dispensed.txt", "w");         //Open and write from start  "Dispensed.txt"
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.println(dispensed[i]);     //Write intakes[i] in mins
        
      }
    file.close();       //Close file
    
}




