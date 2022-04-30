#ifndef MQTT_H
    #define MQTT_H

    #include <Arduino.h>
    
    #define MQTT_VERSION MQTT_VERSION_3_1_1
    
    #define MQTT_SERVER_IP "192.168.1.117" 
    #define MQTT_USER  "admin"
    #define MQTT_PASSWORD  "U3Dl03r2CWE9X58TZ1SK"


    // MQTT: topics                        
    #define MQTT_FOOD_LEVEL_TOPIC  "home/pet/food/level"
    #define MQTT_FOOD_WEIGHT_TOPIC  "home/pet/food/weight"
    
    #define MQTT_INATAKES_CONFIG_CONFIRMATION  "home/pet/intakes/confirm"

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


