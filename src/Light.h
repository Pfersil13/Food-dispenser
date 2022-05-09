#ifndef LIGHT_H
    #define LIGHT_H

    #include <Arduino.h>
    #include <Adafruit_NeoPixel.h>

    #define LEDS 3

    void setupNeopixel();
    void setColor(int led, int redValue, int greenValue, int blueValue);
    void setLeds(int porcenaje);
    
#endif


