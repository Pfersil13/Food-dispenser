#include "MQTT.h"
#include "Control.h"
#include <stdlib.h>
#include "RTC.h"
#include "ReadFS.h"
WiFiClient espClient;
PubSubClient client(espClient);

long lastReconnectAttempt = 0;

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////     
void setup_mqtt() {
client.setServer(MQTT_SERVER_IP, 1883); //Conect to MQTT server 
client.setCallback(callback);   //Declare a function to call when MQTT messages arrive
  
}

///////////////////////////////////////////////////////////////
//Function to reconnect MQTT
///////////////////////////////////////////////////////////////
boolean reconnect() {
  Serial.println("Hi");
  if (!client.connected()) {
    Serial.println("INFO: Attempting MQTT connection...");
    // Attempt to connect
    String clientId;
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) { //MQTT_USER, MQTT_PASSWORD
      Serial.println("INFO: connected");
      // Once connected, publish an announcement...
      // ... and resubscribe


      client.subscribe(MQTT_FEED_NOW);
      client.subscribe(MQTT_ADD_INTAKE);
      client.subscribe(MQTT_ERASE_INTAKE);
      client.subscribe(MQTT_STORE_INTAKE);
    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
    }
  }
  return client.connected();
 }
 /*void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client",MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}*/

//Non blocking function to test & reconnect MQTT
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void test_conn(){
  if (!client.connected()) {
     long nownow = millis();
     if (nownow - lastReconnectAttempt > 5000) {
       lastReconnectAttempt = nownow;
       // Attempt to reconnect
       if (reconnect()) {
        lastReconnectAttempt = 0;
       }}}else{
     client.loop();
       }
}

///////////////////////////////////////////////////////////////
//Callback function, already talked about this
///////////////////////////////////////////////////////////////
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String payload;
  
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    payload += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(payload == "on"){
      Serial.println("on");

    }
    else if(payload == "off"){
      Serial.println("off");
    }
  }
  if (String(topic) == MQTT_FEED_NOW) {
    int x = payload.toInt();
    dispense(x);
  }
  if (String(topic) == MQTT_ADD_INTAKE) {
    int k = 0;
    String hour,min,day, weight;
    for (unsigned int i = 0; i < length; i++) {
      if((char)message[i] == '_'){
        k++;
      }else{
    switch (k)
    {
    case 0:
      hour += (char)message[i];
      break;
    case 1:
      min += (char)message[i];
      break;
    case 2:
      day += (char)message[i];
      break;
    case 3:
      weight += (char)message[i];
      break;
    default:
      break;
    }
      
  }}
    int hourInt = hour.toInt();
    int minInt = min.toInt();
    int dayInt = day.toInt();
    int weightInt = weight.toInt();

    intMsg_out("Hola",hourInt);
    intMsg_out("Hola",minInt);
    intMsg_out("Hola",dayInt);
    intMsg_out("Hola",weightInt);
    addIntake(hourInt,minInt,dayInt,weightInt);
     
  }
  if (String(topic) == MQTT_ERASE_INTAKE){
    erase();
    WriteIntakes();
  }
  if (String(topic) == MQTT_STORE_INTAKE) {
     WriteIntakes();
  }
}




///////////////////////////////////////////////////////////////
// A lot of functions to send diferent types of variables over MQTT
///////////////////////////////////////////////////////////////

void floatMsg_out(String TopicToSend, float data){
char value[10];
char merged[100];
dtostrf(data, 8, 4, value); //Float to Char
String mergedTopic = TopicToSend;
mergedTopic.toCharArray(merged,mergedTopic.length()+1);
client.publish(merged, value);
Serial.println(value);

}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void intMsg_out(String TopicToSend, int data){
char value[10];
char merged[100];
itoa(data,value,10); //int to Char
String mergedTopic = TopicToSend;
mergedTopic.toCharArray(merged,mergedTopic.length()+1);
client.publish(merged, value);
Serial.println(value);

}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void charMsg_out(String TopicToSend, char* data){
  char merged[100];
  String mergedTopic = TopicToSend;
  mergedTopic.toCharArray(merged,mergedTopic.length()+1);
  client.publish(merged, data);
}
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void StringMsg_out(String TopicToSend, String data){
  char merged[100];
  char dataChar[100];
  String mergedTopic = TopicToSend;
  data.toCharArray(dataChar,data.length()+1);
  mergedTopic.toCharArray(merged,mergedTopic.length()+1);
  client.publish(merged, dataChar);
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
String merge(String Input, char* line){
  String mergedTopic = String(line) +  "/" + Input;
  Serial.println(mergedTopic);
  return mergedTopic;
}