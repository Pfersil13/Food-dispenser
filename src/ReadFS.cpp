#include "ReadFS.h"


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
///Function to write ALL arrays into the non volatile memory///
///////////////////////////////////////////////////////////////
void WriteIntakes(){
   if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    File file = LittleFS.open("/Domingo.txt", "w");         //Open and write from start  "Domingo.txt"
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesDomingos[i]);     //Write intakes[i] in mins
        file.print("_");                    //Write a "_" for spliting parameters
        file.println(intakesDomingosWeight[i]); //Write weight[i] in g
      }
    file.close();       //Close file
    
    //Same with all week days ....
   file = LittleFS.open("/Lunes.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){     
        file.print(intakesLunes[i]);
        file.print("_");
        file.println(intakesLunesWeight[i]);
      }
    file.close();
    
    file = LittleFS.open("/Martes.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesMartes[i]);
        file.print("_");
        file.println(intakesMartesWeight[i]);
      }
    file.close();

    file = LittleFS.open("/Miercoles.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesMiercoles[i]);
        file.print("_");
        file.println(intakesMiercolesWeight[i]);
      }
    file.close();

    file = LittleFS.open("/Jueves.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesJueves[i]);
        file.print("_");
        file.println(intakesJuevesWeight[i]);
      }
    file.close();

    file = LittleFS.open("/Viernes.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesViernes[i]);
        file.print("_");
        file.println(intakesViernesWeight[i]);
      }
    file.close();

    file = LittleFS.open("/Sabado.txt", "w");
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    Serial.println("File Write: ");
    for(int i = 0; i< nIntakes; i++){
        file.print(intakesSabados[i]);
        file.print("_");
        file.println(intakesSabadosWeight[i]);
      }
    file.close();
}


/////////////////////////////////////////////////////////////////
///Function to retrun ALL intakes from the non volatile memory/// 
/////////////////////////////////////////////////////////////////
void returnFromFS(){
  if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    
    File file = LittleFS.open("/Domingo.txt", "r");        //Open and write from start  "Domingo.txt"
    if(!file){
        Serial.println("Failed to open file for reading");
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
        intakesDomingos[i] = mins;                  //Store in array
        intakesDomingosWeight[i] = weights;         //Store in array
        i++;
    }
    file.close();
    
    //Repeat....
    file = LittleFS.open("/Lunes.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Lunes");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesLunes[i] = mins; 
        intakesLunesWeight[i] = weights; 
        i++;
    }
    file.close();

    file = LittleFS.open("/Martes.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Martes");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesMartes[i] = mins; 
        intakesMartesWeight[i] = weights; 
        i++;
    }
    file.close();

    file = LittleFS.open("/Miercoles.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Miercoles");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesMiercoles[i] = mins; 
        intakesMiercolesWeight[i] = weights; 
        i++;
    }
    file.close();

    file = LittleFS.open("/Jueves.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Jueves");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesJueves[i] = mins; 
        intakesJuevesWeight[i] = weights; 
        i++;
    }
    file.close();

    file = LittleFS.open("/Viernes.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Viernes");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesViernes[i] = mins; 
        intakesViernesWeight[i] = weights; 
        i++;
    }
    file.close();

    file = LittleFS.open("/Sabado.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Sabado");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
    while(file.available()){
        String val = file.readStringUntil('_');
        String val_2 = file.readStringUntil('\n');
        int mins = atoi(val.c_str());
        int weights = atoi(val_2.c_str());
        Serial.print(mins);
        Serial.print(":");
        Serial.println(weights);
        intakesSabados[i] = mins; 
        intakesSabadosWeight[i] = weights; 
        i++;
    }
    file.close();


    file = LittleFS.open("/Dispensed.txt", "r");
    if(!file){
        Serial.println("Failed to open file for reading Disp");
        return;
    }
    
    Serial.println("File Content:");
    i = 0;
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


