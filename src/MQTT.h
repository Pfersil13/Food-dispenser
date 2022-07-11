#ifndef MQTT_H
    #define MQTT_H

    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <PubSubClient.h>
    
    
    #define MQTT_VERSION MQTT_VERSION_3_1_1
    
    //MQTT Private stuff here
    #include "Secrets.h"
   


    // MQTT: topics                        
    #define MQTT_FOOD_LEVEL_TOPIC  "home/pet/food/level"
    #define MQTT_FOOD_WEIGHT_TOPIC  "home/pet/food/weight"
    
    #define MQTT_INATAKES_CONFIG_CONFIRMATION  "home/pet/intakes/confirm"
    #define MQTT_INATAKES_CONFIG  "home/pet/intakes/confirm"
    #define MQTT_FEEDING "home/pet/feeding"

     #define MQTT_FEED_NOW "home/pet/feed/now"
     #define MQTT_ADD_INTAKE "home/pet/feed/addIntake"
     #define MQTT_STORE_INTAKE "home/pet/feed/store"
     #define MQTT_ERASE_INTAKE "home/pet/feed/erase"
    //void reconnect();
    boolean reconnect();
    void test_conn();
    void callback(char* p_topic, byte* p_payload, unsigned int p_length);
    void setup_mqtt();
    void floatMsg_out(String TopicToSend, float data);
    void charMsg_out(String TopicToSend, char* data);   
    String merge(String Input, char* line);
    void StringMsg_out(String TopicToSend, String data);
    void intMsg_out(String TopicToSend, int data);
    
#endif


