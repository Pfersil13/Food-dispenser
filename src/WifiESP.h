#ifndef WIFIESP_H
    #define WIFIESP_H

    #include <Arduino.h>
    
    // Wifi: SSID and password
    #define WIFI_SSID  "SSID"  
    #define WIFI_PASSWORD "Password"

   

    void setup_wifi();
    boolean testWiFI();
#endif