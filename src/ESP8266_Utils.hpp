
#ifndef READFS_H
    #define READFS_H
    #include "ReadFS.h"
#endif

extern String S;
extern String P;

IPAddress ip(192,168,1,200);     //Cambiar tercer parametro si da error (ej. 137), quiere decir que no es un router el que manda la señal
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0); 

void InitMDNS()
{
   if (!MDNS.begin("dispensa")) 
   {             
     Serial.println("Error iniciando mDNS");
   }
   Serial.println("mDNS iniciado");
}

void ConnectWiFi_AP_STA()
{ 
   Serial.println("");
   WiFi.mode(WIFI_AP_STA);
   if(!WiFi.softAP(ssid, password))
   {
     Serial.println("Lost AP.");
   } else {
   Serial.println("");
   Serial.print("Iniciado AP:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println("192.168.4.1");
   WiFi.config(ip, gateway, subnet, gateway);
   returnWiFi();
   WiFi.begin(S,P);
   if (WiFi.status() != WL_CONNECTED) 
   { 
      Serial.println("Trying to connect to...");
      Serial.println("Lost connection with wifi");
      delay(1000);
   }
  
   Serial.print("Iniciado STA:\t");
   Serial.println(S);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());

   InitMDNS();

  }
}
