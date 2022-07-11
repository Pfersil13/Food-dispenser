#include "html.h"
#ifndef CON_H
    #define CON_H
#include "conversion.hpp"
#endif
#ifndef RTC_H
    #define RTC_H
    #include "ReadFS.h"
#endif

extern AsyncWebServer server;
int ndia,H_,m_;

//Define the parameters of the get forms from html
const char* PARAM_INPUT_SSID = "ssidInput";
const char* PARAM_INPUT_PASS = "pass";
const char* PARAM_INPUT_HORA = "hora_min";
const char* PARAM_INPUT_DIA = "dia";
const char* PARAM_INPUT_PESO = "peso";
String inputMessage_SSID;
String inputParam_SSID;
String inputMessage_PASS;
String inputParam_PASS;

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void serverInit(){
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", page);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;


    
    if (request->hasParam(PARAM_INPUT_SSID) && request->hasParam(PARAM_INPUT_PASS)) {
      inputMessage_SSID = request->getParam(PARAM_INPUT_SSID)->value();
      inputParam_SSID = PARAM_INPUT_SSID;
      inputMessage_PASS= request->getParam(PARAM_INPUT_PASS)->value();
      inputParam_PASS = PARAM_INPUT_PASS;
      Serial.println(inputMessage);
      request->send(200, "text/html", "Parametros wifi correctamente enviados al dispensador ( SSID: " 
                                     + inputParam_SSID + ", CONTRASEÑA: " + inputParam_PASS + ")<br> WIFI:" + inputMessage_SSID +" <br>CONTRASEÑA: "
                                     + inputMessage_PASS + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
      WriteWiFi(inputMessage_SSID, inputMessage_PASS);            
      ConnectWiFi_AP_STA();

    } else if(request->hasParam(PARAM_INPUT_DIA) && request->hasParam(PARAM_INPUT_HORA)){
        String inputMessage_HORA = request->getParam(PARAM_INPUT_HORA)->value();
        String inputParam_HORA = PARAM_INPUT_HORA;
        String inputMessage_DIA= request->getParam(PARAM_INPUT_DIA)->value();
        String inputParam_DIA = PARAM_INPUT_DIA;
        char dia_char;
        strcpy(&dia_char, inputMessage_DIA.c_str());
        if(dia(dia_char, ndia)==true){
          if(hora(inputMessage_HORA, H_, m_)==true){
            request->send(200, "text/html", "Toma registrada correctamente:<br> DIA: " + inputMessage_DIA +" <br>HORA: "
                                     + inputMessage_HORA + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
            test_conn();
            addIntake(H_,m_,ndia,50);
            Serial.println("NE");
            delay(1000);
          } else {
            request->send(200, "text/html", "Toma no registrada correctamente, introduzca otra hora:<br> DIA: " + inputMessage_DIA +" <br>HORA (incorrecta): "
                                     + inputMessage_HORA + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
          }
        } else {
          if(hora(inputMessage_HORA, H_, m_)==true){
          request->send(200, "text/html", "Toma no registrada correctamente, introduzca otro dia:<br> DIA (incorrecto): " + inputMessage_DIA +" <br>HORA: "
                                     + inputMessage_HORA + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
          } else {
          request->send(200, "text/html", "Toma no registrada correctamente, introduzca otro dia y hora:<br> DIA (incorrecto): " + inputMessage_DIA +" <br>HORA (incorrecta): "
                                     + inputMessage_HORA + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
          }

        }

    } else if(request->hasParam(PARAM_INPUT_PESO)){
        String inputMessage_PESO = request->getParam(PARAM_INPUT_PESO)->value();
        String inputParam_PESO = PARAM_INPUT_PESO;

        request->send(200, "text/html", "Toma registrada correctamente:<br> PESO: " + inputMessage_PESO 
                                                + "<br><a href=\"/\">Vuelve a la pagina principal.</a>");
        peso(inputMessage_PESO);

    } else {
      inputMessage = "No message sent";
      inputParam = "none";
      Serial.println(inputMessage);
      request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
    }

  });
  server.onNotFound(notFound);
  server.begin();
  }

