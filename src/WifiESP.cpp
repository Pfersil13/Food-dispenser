
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WifiESP.h"

long lastReconnectAttemptWifi = 0;

//Function for calling wifi at first time
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  for(int i = 0; i  < 100; i++){
    Serial.print(".");
    delay(500);
   if(WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    break;
  }
  }
}

//Function to return actual wifi state & reconnect if needed
//If wifi is not found it will not block code
boolean testWiFI(){
  bool state = 0;
  if(WiFi.status() != WL_CONNECTED){
      long nownow = millis();
      if (nownow - lastReconnectAttemptWifi > 5000) {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        lastReconnectAttemptWifi = nownow;
          for(int i = 0; i  < 100; i++){
            Serial.print(".");
            delay(500);
          if(WiFi.status() == WL_CONNECTED){
            Serial.println("");
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            state = 1;
            break;
          }
      }
  
  }}return state;
  }
 
